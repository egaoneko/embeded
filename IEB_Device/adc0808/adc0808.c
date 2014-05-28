/*
 * X-HYPER270-TKU IEB Rev
 * ADC0808 Chip Driver
 * 2006-08-23  <kjlee@hybus.net> Version 1.0
 * 2006-10-18 Modified by kjlee  Version 1.1
 */

#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

#include <asm/hardware.h>
#include <asm/arch-pxa/pxa-regs.h>
#include <asm/io.h>

#define ADC_MAJOR       	241
#define ADC_NAME  		"adc0808"
#define IEB_ADC_ADDR   		(0x13D00000)
#define IEB_ADC_OE      	(0x13E00000)
#define IEB_DAC_ADDR    	(0x13F00000)

#define IRQ_INT16		IRQ_GPIO(16)

#define OSTIMER_IRQ             IRQ_OST1

#define Sec_Clk                 3686400
#define Usec_Clk                (Sec_Clk/10000)  

#define OSTIMER_ON              OIER |= OIER_E1; OSSR = OSSR_M1
#define OSTIMER_OFF             OIER &= ~OIER_E1; OSSR = OSSR_M1

#define ADC_CTL     		(*((volatile unsigned char *)(mem_base0)))
#define DAC_CTL                 (*((volatile unsigned char *)(mem_base1)))
#define ADC_OE                  (*((volatile unsigned char *)(mem_base2)))

#define ADC_CTL_SETBIT(x) 	{adc_port |= (1<<x); ADC_CTL = adc_port;}
#define ADC_CTL_CLEARBIT(x) 	{adc_port &= ~(1<<x); ADC_CTL = adc_port;}

#define BIT(x)			(1 << x)

#define CLK			0
#define ALE			4
#define START			6
#define RDEN			5

#define	ADC_VR			0x3
#define ADC_LS			0x2
#define ADC_LOOP		0x1

#define CONVT			500

static void *mem_base0, *mem_base1, *mem_base2;
volatile unsigned char adc_port;
//int flag = 0;
int lock = 0;
int ch_num = 0;
unsigned char adc_value = 0;
int cnt = 0;

DECLARE_WAIT_QUEUE_HEAD(adc_queue);

//static struct timer_list adc_timer;
//static void adc_timer_function(unsigned long);
//static void init_add_adc_timer(void);
//static void remove_adc_timer(void);

static void adc_channel_set(int);

static void adc_int_pin_init(void)
{
/*	
	GAFR0_U &= ~((1 << 0) | (1 << 1));
	GPDR0 &= ~BIT(16);
	GRER0 = BIT(16);
*/
        pxa_gpio_mode(16 | GPIO_IN);
	GRER(16) |= GPIO_bit(16);
}

static void adc_ctl_init(int chn)
{
	adc_channel_set(chn);
	udelay(1);
	ADC_CTL_SETBIT(ALE);
	udelay(1);
	ADC_CTL_SETBIT(START);
	udelay(1);
	ADC_CTL_CLEARBIT(ALE);
	udelay(1);
	ADC_CTL_CLEARBIT(START);
}

static void adc_clock(void)
{
        ADC_CTL_CLEARBIT(CLK); // clk low
        udelay(2);
        ADC_CTL_SETBIT(CLK);   // clk high
	udelay(2);
}

static irqreturn_t ADCCLK_InterruptHandler(int irq, void *dev_id, struct pt_regs *regs)
{
        OSTIMER_OFF;
        adc_clock();

	OSTIMER_ON;
	OSMR1 = OSCR + Usec_Clk;
        return IRQ_HANDLED;
}

// Software Timer
/*
static void adc_timer_function(unsigned long ptr)
{
	if(flag)
        {
                ADC_CTL_CLEARBIT(CLK); // clk low
        	flag = 0;
	}
        else
        {
                ADC_CTL_SETBIT(CLK);   // clk high
		flag = 1;
        }
	init_add_adc_timer();
}

static void init_add_adc_timer(void)
{
	init_timer(&adc_timer);
	adc_timer.function =&adc_timer_function;
	adc_timer.expires = jiffies + 1;
	add_timer(&adc_timer);
}

static void remove_adc_timer(void)
{
	del_timer(&adc_timer);
}
*/
static void adc_channel_set(int chn)
{
	switch(chn)
	{
		case 0 : ADC_CTL_CLEARBIT(3); 
			 ADC_CTL_CLEARBIT(2); 
			 ADC_CTL_CLEARBIT(1); 
			 break;
        	case 1 : ADC_CTL_CLEARBIT(3); 
			 ADC_CTL_CLEARBIT(2); 
			 ADC_CTL_SETBIT(1); 
			 break;
        	case 2 : ADC_CTL_CLEARBIT(3); 
			 ADC_CTL_SETBIT(2); 
			 ADC_CTL_CLEARBIT(1); 
			 break;
        	case 3 : ADC_CTL_CLEARBIT(3); 
			 ADC_CTL_SETBIT(2); 
			 ADC_CTL_SETBIT(1); 
			 break;
	        case 4 : ADC_CTL_SETBIT(3); 
			 ADC_CTL_CLEARBIT(2); 
			 ADC_CTL_CLEARBIT(1); 
			 break;
	        case 5 : ADC_CTL_SETBIT(3); 
			 ADC_CTL_CLEARBIT(2); 
			 ADC_CTL_SETBIT(1); 
			 break;
	        case 6 : ADC_CTL_SETBIT(3); 
			 ADC_CTL_SETBIT(2); 
			 ADC_CTL_CLEARBIT(1);
			 break;
	        case 7 : ADC_CTL_SETBIT(3); 
			 ADC_CTL_SETBIT(2); 
			 ADC_CTL_CLEARBIT(1); 
			 break;
	        default: ADC_CTL_CLEARBIT(3); 
			 ADC_CTL_CLEARBIT(2); 
			 ADC_CTL_CLEARBIT(1); 
			 break;
	}
	return;
}

static void adc_read_enable(void)
{
	ADC_CTL_SETBIT(RDEN);
}

static void adc_read_disable(void)
{
	ADC_CTL_CLEARBIT(RDEN);
}

static void adc_read_data(void)
{
	udelay(150);
	adc_read_enable();
	adc_value = ADC_OE;
        adc_read_disable();
}

static irqreturn_t ADC_InterruptHandler(int irq, void *dev_id, struct pt_regs *regs)
{
	if(!lock)
	{
		adc_read_data();
		adc_ctl_init(ch_num);
	}
	wake_up_interruptible(&adc_queue);
	return IRQ_HANDLED;
}

static unsigned char bit_change(unsigned char ddata)
{
	int i;
	unsigned char buf = 0;

	for(i=7; i>=0; i--)
		buf |= (ddata & BIT(7-i) ? 1 : 0) << i;

	return buf;
}

static int adc_open(struct inode *inode, struct file *filp)
{
	cnt = 0;
	adc_int_pin_init();
	OSTIMER_ON;
	OSMR1 = OSCR + Usec_Clk;
//	init_add_adc_timer();
	return 0;
}

static int adc_release(struct inode *inode, struct file *filp)
{
	OSTIMER_OFF;
//	remove_adc_timer();
	return 0;        
}                         

static ssize_t adc_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	mdelay(10);
	if(cnt == CONVT)
	{
		cnt = 0;
		lock = 1;
		interruptible_sleep_on(&adc_queue);
	}
	else
		cnt++;

	copy_to_user(buf, &adc_value, sizeof(adc_value));
	return 0;
}

static ssize_t adc_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static int adc_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	lock = 0;
	switch(cmd)
	{ 
		case ADC_LOOP :
		{
			DAC_CTL = bit_change((unsigned char)arg);
			udelay(1);
			ch_num = 2;
			break;
		}
		case ADC_LS :
		{
			ch_num = 1;
			break;
	 	}
		case ADC_VR :
		{
			ch_num = 0;
			break;
	 	}
		default:
			break;
	}
       
	adc_ctl_init(ch_num);
	return 0;
}

static struct file_operations adc_fops = {
	read	:	adc_read,
	write	:	adc_write,
	ioctl	:	adc_ioctl,
	open	:	adc_open,
	release	:	adc_release,
};

static int __init adc_init(void)
{
	int result;
	unsigned long mem_addr0, mem_addr1, mem_addr2, mem_len;

	result = register_chrdev(ADC_MAJOR, ADC_NAME, &adc_fops);
	if(result < 0){
		printk(KERN_WARNING "Can't get major \n");
		return result;
	}

	OSTIMER_OFF;

	if((request_irq(OSTIMER_IRQ, &ADCCLK_InterruptHandler, SA_INTERRUPT, "ADC_CLK_OST", NULL)))
        {
                printk("Failed to regist OSTIMER_IRQ\n");
                return -1;
        }

    	if((request_irq(IRQ_INT16, ADC_InterruptHandler, SA_INTERRUPT, "ADC_GP16_INT", NULL)))
   	{
       		printk("Failed to regist IRQ_INT16\n");
        	return -1;
    	}

	set_irq_type(IRQ_INT16, IRQT_RISING);


	mem_addr0 = IEB_ADC_ADDR;
	mem_addr1 = IEB_DAC_ADDR;
	mem_addr2 = IEB_ADC_OE;
	mem_len = 0x10000;
	
	mem_base0 = ioremap_nocache (mem_addr0, mem_len);
	if(!mem_base0){
		printk("Error mapping ADC_CS...\n");
		return -EBUSY;
	}

	mem_base1 = ioremap_nocache (mem_addr1, mem_len);
        if(!mem_base1){
                printk("Error mapping DAC_CS...\n");
                return -EBUSY;
        }

	mem_base2 = ioremap_nocache (mem_addr2, mem_len);
        if(!mem_base2){
                printk("Error mapping ADC_OE...\n");
                return -EBUSY;
        }

	printk("X-Hyper 270TKU %s MAJOR %d, IRQ %d %d\n", ADC_NAME, ADC_MAJOR, OSTIMER_IRQ, IRQ_INT16);
	return 0;
}

static void __exit adc_exit(void)
{
	int result;
	free_irq(IRQ_INT16, NULL);
	free_irq(OSTIMER_IRQ, NULL);
	
	result = unregister_chrdev(ADC_MAJOR, ADC_NAME);
	if(result < 0){
		printk(KERN_WARNING "Can't unregist device MAJOR %d, %d, %d\n", ADC_MAJOR, IRQ_INT16, OSTIMER_IRQ);
        }

	iounmap(mem_base0);
	iounmap(mem_base1);
	iounmap(mem_base2);

	printk("MAJOR %d, %s is unregisted\n", ADC_MAJOR, ADC_NAME);
	return;
}

module_init(adc_init);
module_exit(adc_exit);

