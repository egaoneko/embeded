/*
 * X-HYPER270-TKU IEB Rev
 * GPIO_LED Device Driver
 * 2006-08-24  <kjlee@hybus.net>
 */

#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/interrupt.h>

#include <asm/hardware.h>
#include <asm/arch-pxa/pxa-regs.h>

#define IRQ_KEY1        IRQ_GPIO(36)
#define IRQ_KEY2        IRQ_GPIO(37)
#define IRQ_KEY3	IRQ_GPIO(35)
#define IRQ_KEY4	IRQ_GPIO(41)

#define GPIO_LED1        GPIO_bit(4)
#define GPIO_LED2        GPIO_bit(3)

#define GPIO_LED_MAJOR 	242
#define GPIO_LED_NAME     	"gpio_led"

#define GPIO_KEY_READ		0x1
#define GPIO_LED1_ON_OFF	0x2
#define GPIO_LED2_ON_OFF	0x3

#define DUMMY_DELAY 		mdelay(183)
static int led_usage = 0;

char key_buf;
DECLARE_WAIT_QUEUE_HEAD(key_queue);

static void gpio_led_pin_set(void)
{
	// GPLED1, GPLED2 Setting
        GAFR0_L &= ~((1<<6)|(1<<7) | (1<<8)|(1<<9));  //GPIO3, GPIO4
        GPDR0   |= (GPIO_LED1 | GPIO_LED2);           //Output Pin
        GPSR0    = (GPIO_LED1 | GPIO_LED2);
        GPCR0    = (GPIO_LED1 | GPIO_LED2);

        GFER1   |= (GPIO_bit(35) | GPIO_bit(36) | GPIO_bit(37) | GPIO_bit(41));	
}

static void gpio_led_clear(void)
{
	GPSR0 = (GPIO_bit(3) | GPIO_bit(4));  // LED Inital Clear
}


static int gpio_led_open(struct inode *inode, struct file *filp)
{
	gpio_led_clear();
	if(led_usage != 0) return -EBUSY;
	led_usage = 1;
	return 0;
}

static int gpio_led_release(struct inode *inode, struct file *filp)
{
	led_usage = 0;
	gpio_led_clear();
	return 0;
}                         

ssize_t gpio_led_write(struct file *filp, const char *buf, size_t length, loff_t *f_pos)
{
	return 0;
}

ssize_t gpio_led_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	interruptible_sleep_on (&key_queue);

	if(key_buf == 1){
		DUMMY_DELAY;
		if((GPLR1 & GPIO_bit(36))) 
			key_buf = 1;
	}
	else if(key_buf == 2){
		DUMMY_DELAY;
	        if((GPLR1 & GPIO_bit(37)))
	      		key_buf = 2;
	}
	else if(key_buf == 3){
		DUMMY_DELAY;
		if((GPLR1 & GPIO_bit(35)))
                        key_buf = 3;
	}
	else if(key_buf == 4){
                DUMMY_DELAY;
                if((GPLR1 & GPIO_bit(41)))
                        key_buf = 4;
	}
	else
		printk("Internal Error\n");

	copy_to_user(buf, &key_buf, sizeof(key_buf));
	return 0;
}

int gpio_led_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int data = 0;
	int ret = 0;

	/*You can add any ioctl command*/
	switch(cmd)
	{
        	case GPIO_KEY_READ:
                	copy_to_user((void *)arg, &key_buf, sizeof(key_buf));
			key_buf = 0;					
                	return 0;
		case GPIO_LED1_ON_OFF:
			copy_from_user(&data, (void *)arg, sizeof(data));
			if(data == 1)
				GPSR0 = GPIO_LED1;	//GPIO 3 SET	LED OFF
			else
				GPCR0 = GPIO_LED1;	//GPIO 3 CLEAR	LED ON
			return 0;
		case GPIO_LED2_ON_OFF:
			copy_from_user(&data, (void *)arg, sizeof(data));
			if(data == 1)
				GPSR0 = GPIO_LED2;	//GPIO 4 SET	LED OFF
			else
				GPCR0 = GPIO_LED2;	//GPIO 4 CLEAR	LED ON
			return 0;
		default:
                	return -EINVAL;
	}
	return ret;
}

static irqreturn_t KEY1_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	key_buf = 1;

 	wake_up_interruptible(&key_queue);
	return IRQ_HANDLED;
}

static irqreturn_t KEY2_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	key_buf = 2;

	wake_up_interruptible(&key_queue);
        return IRQ_HANDLED;

}

static irqreturn_t KEY3_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
        key_buf = 3;

        wake_up_interruptible(&key_queue);
        return IRQ_HANDLED;

}

static irqreturn_t KEY4_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
        key_buf = 4;

        wake_up_interruptible(&key_queue);
        return IRQ_HANDLED;

}

static struct file_operations gpio_led_fops = {
	open	:	gpio_led_open,
	read	:	gpio_led_read,		    
	write	:	gpio_led_write,
	ioctl	:	gpio_led_ioctl,
	release	:	gpio_led_release,
};

static int __init gpio_led_init(void)
{
  	int result, ret;

 	result = register_chrdev(GPIO_LED_MAJOR, GPIO_LED_NAME, &gpio_led_fops);

	if ((ret = request_irq(IRQ_KEY1, &KEY1_interrupt, SA_INTERRUPT, "GPIO36_KEY1", NULL)))
	{
        	printk("Failed to register IRQ KEY1\n");
        	return ret;
	}

	if ((ret = request_irq(IRQ_KEY2, &KEY2_interrupt, SA_INTERRUPT, "GPIO37_KEY2", NULL)))
	{
        	printk("Failed to register IRQ KEY2\n");
        	return ret;
	}

	if ((ret = request_irq(IRQ_KEY3, &KEY3_interrupt, SA_INTERRUPT, "GPIO35_KEY3", NULL)))
        {
                printk("Failed to register IRQ KEY3\n");
                return ret;
        }

	if ((ret = request_irq(IRQ_KEY4, &KEY4_interrupt, SA_INTERRUPT, "GPIO41_KEY4", NULL)))
        {
                printk("Failed to register IRQ KEY4\n");
                return ret;
        }
	
	set_irq_type(IRQ_KEY1, IRQT_FALLING);					// 2.6 Kernel	
//      set_GPIO_IRQ_edge(IRQ_TO_GPIO_2_80(IRQ_KEY1), GPIO_FALLING_EDGE);	// 2.4 Kernel
	set_irq_type(IRQ_KEY2, IRQT_FALLING);					
//      set_GPIO_IRQ_edge(IRQ_TO_GPIO_2_80(IRQ_KEY2), GPIO_FALLING_EDGE);	
	set_irq_type(IRQ_KEY3, IRQT_FALLING);					
//      set_GPIO_IRQ_edge(IRQ_TO_GPIO_2_80(IRQ_KEY3), GPIO_FALLING_EDGE);	
	set_irq_type(IRQ_KEY4, IRQT_FALLING);   				
//      set_GPIO_IRQ_edge(IRQ_TO_GPIO_2_80(IRQ_KEY4), GPIO_FALLING_EDGE);	

	gpio_led_pin_set();

 	printk("X-Hyper 270TKU %s MAJOR %d, IRQ %d %d %d %d\n", GPIO_LED_NAME, GPIO_LED_MAJOR, IRQ_KEY1, IRQ_KEY2, IRQ_KEY3, IRQ_KEY4);
	return 0;
}

static void __exit gpio_led_exit(void)
{
//	disable_irq(IRQ_KEY1);		// 2.4 Kernel
	free_irq(IRQ_KEY1, NULL);	// 2.6 Kernel
//	disable_irq(IRQ_KEY2);		
	free_irq(IRQ_KEY2, NULL);
//      disable_irq(IRQ_KEY3);  
        free_irq(IRQ_KEY3, NULL);
//      disable_irq(IRQ_KEY4);  
        free_irq(IRQ_KEY4, NULL);

	gpio_led_clear();
	unregister_chrdev(GPIO_LED_MAJOR, GPIO_LED_NAME);
	printk("Release %s Module MAJOR %d\n", GPIO_LED_NAME, GPIO_LED_MAJOR);
}

module_init(gpio_led_init);
module_exit(gpio_led_exit);

