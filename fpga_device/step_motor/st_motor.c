/*
 * XHYPER255_TKU3 -  step motor
 * motor.c	OST1
 * 2004-07-01   <newboder@hybus.net>
 * 
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/rtc.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <asm/system.h>

#include <asm/hardware.h>
#include <asm/delay.h>
#include <asm/arch/pxa-regs.h>
#include <asm/irq.h>
#include <asm/mach/time.h>
#include <asm/io.h>

#define ST_MOTOR_MAJOR       	236
#define ST_MOTOR_NAME  		"st_motor"
#define FPGA_ST_MOTOR_CS	(0x12100000)

#define OSTIMER_IRQ        	IRQ_OST1

#define Sec_Clk            	3686400
#define Usec_Clk            	(Sec_Clk/100000)   // 100uSec

#define OSTIMER_ON		OIER |= OIER_E1; OSSR = OSSR_M1 
#define OSTIMER_OFF 		OIER &= ~OIER_E1; OSSR = OSSR_M1 

//static void *mem_base;
#define ST_MOTOR     		(*((volatile unsigned char *)(mem_base))) 
#define ST_MOTOR_SetBit(x) 	{  motor_port |=  (1<<x); ST_MOTOR = motor_port; }
#define ST_MOTOR_ClearBit(x) 	{  motor_port &= ~(1<<x); ST_MOTOR = motor_port; }

#define Forward			1 
#define Reverse			0

#define MOTOR_Forward    	0x1
#define MOTOR_Reverse    	0x2
#define MOTOR_SpeedUp   	0x3
#define MOTOR_SpeedDown 	0x4
#define MOTOR_STOP       	0x5

/*
 * FPGA 
 * address 0x17400000
 * CLK			D0
 * ENABLE		D1
 * CW_CCW		D2
 * RESET		D3
*/
#define CLK			3
#define ENABLE			2
#define CW_CCW			1
#define RESET			0


static void *mem_base;
static int motor_speed = 1000;
volatile unsigned char motor_port;

static void MOTOR_Init(void)
{
	ST_MOTOR_ClearBit(CLK);   // clk low
	ST_MOTOR_ClearBit(ENABLE);   // enable low
	ST_MOTOR_ClearBit(CW_CCW);   // cw/ccw low
	ST_MOTOR_ClearBit(RESET);   // reset low

	ST_MOTOR_ClearBit(RESET);   // reset low
	udelay(2);
	ST_MOTOR_SetBit(RESET);     // reset high
	ST_MOTOR_SetBit(ENABLE);     // enable high
}

static void Motor_Direction(int dir)
{
	if(dir == 1) {
		ST_MOTOR_SetBit(CW_CCW);     // cw/ccw high
	}
	else {
		ST_MOTOR_ClearBit(CW_CCW);   // cw/ccw low
	}
}

static void Motor_Stop(void)
{
    ST_MOTOR_ClearBit(CLK);   // clk low
    ST_MOTOR_ClearBit(ENABLE);   // enable low
    ST_MOTOR_ClearBit(CW_CCW);   // cw/ccw low
    ST_MOTOR_ClearBit(RESET);   // reset low

    OSTIMER_OFF;
    //disable_irq(OSTIMER_IRQ);
}

static void Motor_Clock(void)
{
	ST_MOTOR_ClearBit(CLK);     // clk low            
	udelay(1);
	ST_MOTOR_SetBit(CLK);       // clk high
}

static void MOTOR_ReSetting(int speed)
{
	OSTIMER_ON;             
	OSMR1 = OSCR + Usec_Clk*speed;
}

static irqreturn_t MOTOR_InterruptHandler(int irq, void *dev_id, struct pt_regs *regs)
{
	OSTIMER_OFF;
	Motor_Clock();
	MOTOR_ReSetting(motor_speed);
	return IRQ_HANDLED;
}

static int st_motor_open(struct inode *inode, struct file *filp)
{
//	MOD_INC_USE_COUNT;
	return 0;
}

static int st_motor_release(struct inode *inode, struct file *filp)
{
//	MOD_DEC_USE_COUNT;
	return 0;        
}                         

static ssize_t st_motor_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

static ssize_t st_motor_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos )
{
	return 0;
}

static int st_motor_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch (cmd) { 
		case MOTOR_Forward : {
					 OSTIMER_OFF;
					 MOTOR_Init();	
					 Motor_Direction( Forward );
					// enable_irq(OSTIMER_IRQ);
					 MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz
					 break;
				 }
		case MOTOR_Reverse : {
					 OSTIMER_OFF;
					 MOTOR_Init();
					 Motor_Direction( Reverse );
					 //enable_irq(OSTIMER_IRQ);
					 MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz
					 break;
	 			 }
		case MOTOR_SpeedUp : {
		 			 if(motor_speed > 150){
						 motor_speed -= 50;	// Speed Up
						 printk("speed up %d\n", motor_speed);
		 			 }
					 break;
	 			 }
		case MOTOR_SpeedDown : {
					 motor_speed += 50;	// Speed Down
					 break;
	 			 }
		case MOTOR_STOP : {
					 Motor_Stop();
					 break;
	 			 }
		default:
				 return 0;
	}
	return 0;
}

static struct file_operations st_motor_fops = {
	read	:	st_motor_read,
	write	:	st_motor_write,
	ioctl	:	st_motor_ioctl,
	open	:	st_motor_open,
	release	:	st_motor_release,
};

static int st_motor_init(void)
{
	int result;
	unsigned long mem_addr, mem_len;

	result = register_chrdev(ST_MOTOR_MAJOR, ST_MOTOR_NAME, &st_motor_fops);
	if (result < 0) {
		printk(KERN_WARNING " can't get major \n");
		return result;
	}

    	if ((request_irq(OSTIMER_IRQ, MOTOR_InterruptHandler, SA_INTERRUPT, "SMOTOR_OST", NULL)))
   	 {
       		printk("failed to register IRQ\n");
        	return -1;
    	}
	
	mem_addr = FPGA_ST_MOTOR_CS;
	mem_len = 0x10000;
	
	mem_base = ioremap_nocache (mem_addr, mem_len);
	if (!mem_base){
		printk (" Error mapping st_motor ..\n");
		return -EBUSY;
	}

	printk("X-Hyper 270TKU %s MAJOR %d IRQ %d\n", ST_MOTOR_NAME, ST_MOTOR_MAJOR, OSTIMER_IRQ);
	OSTIMER_OFF;
//	enable_irq(OSTIMER_IRQ);
	return 0;
}

static void st_motor_exit(void)
{
    	OSTIMER_OFF;
//  	  disable_irq(OSTIMER_IRQ);
 	free_irq(OSTIMER_IRQ, NULL);
	unregister_chrdev(ST_MOTOR_MAJOR, ST_MOTOR_NAME);
	iounmap(mem_base);
}

module_init(st_motor_init);
module_exit(st_motor_exit);

/* EOF */
