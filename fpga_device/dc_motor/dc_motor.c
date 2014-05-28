/*#include <linux/config.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/signal.h>
#include <linux/sched.h>     
#include <linux/major.h>
#include <linux/string.h>
#include <linux/fcntl.h>   
#include <linux/ptrace.h>
#include <linux/ioport.h>  
#include <linux/init.h>
#include <linux/delay.h>   
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/time.h>

#include <asm/system.h>     
#include <asm/io.h>           
#include <asm/irq.h>        
#include <asm/uaccess.h>  
#include <asm/hardware.h>   
#include <asm/arch/pxa-regs.h>
#include <asm/mach/time.h>
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

#include <asm/hardware.h>
#include <asm/delay.h>
#include <asm/arch/pxa-regs.h>
#include <asm/irq.h>
#include <asm/mach/time.h>
#include <asm/io.h>
#include "motor.h"

#define _IOCTL_LEFT_FORWARD		1
#define _IOCTL_LEFT_REVERSE		2
#define _IOCTL_LEFT_STOP		3

#define _IOCTL_RIGHT_FORWORD		4
#define _IOCTL_RIGHT_REVERSE		5
#define _IOCTL_RIGHT_STOP		6

#define _IOCTL_SPEED_UP			7
#define _IOCTL_SPEED_DOWN		8

#define DEVMAJOR			237
#define DEVNAME				"dc_motor"

int motor_speed = 500;
static unsigned short dc_motor_port;

static void DC_MOTOR_Init(void)
{
      /*  MOTOR_ClearBit(0)   // clk low
        MOTOR_ClearBit(1)   // enable low
        MOTOR_ClearBit(2)   // cw/ccw low
        MOTOR_ClearBit(3)   // reset low
        MOTOR_ClearBit(4)   // reset low
        MOTOR_ClearBit(5)   // reset low
	*/
	 MOTOR_SetBit(0)   // clk low
        MOTOR_SetBit(1)   // enable low
        MOTOR_SetBit(2)   // cw/ccw low
        MOTOR_SetBit(3)   // reset low
        MOTOR_SetBit(4)   // reset low
        MOTOR_SetBit(5)   // reset low
}

int mask = 0;
int clock = 0;
int motor_mask = 0 ;
static void Dc_Moter_Clock(void)
{
		if ( motor_mask == 0 ){			    // LEFT Motor
				if(mask == 1 ){		    // forward
	    		    		MOTOR_ClearBit(1);    
	    		    		MOTOR_SetBit(0);     
	    		   		MOTOR_SetBit(4);     
				} else if (mask == 2){	    // reverse
		    	    		MOTOR_ClearBit(0);    
	    		    		MOTOR_SetBit(1);  
	    		    		MOTOR_SetBit(4);     
				} else {
			        	MOTOR_ClearBit(0);  // stop 
			    		MOTOR_ClearBit(1);    
        				MOTOR_ClearBit(4)   // reset low
				}
		} else {				   // RIGHT Motor
				if(mask == 1 ){		   // forward
	    		    		MOTOR_ClearBit(3);    
	    		    		MOTOR_SetBit(2);     
	    		    		MOTOR_SetBit(5);     
				} else if (mask == 2){	   // reverse
		    	    		MOTOR_ClearBit(2);    
	    		    		MOTOR_SetBit(3);  
	    		    		MOTOR_SetBit(5);     
				} else {
			        	MOTOR_ClearBit(3);  // stop 
	    		    		MOTOR_ClearBit(2);    
        				MOTOR_ClearBit(5)   // reset low
				}
		}
}

static void DC_MOTOR_ReSetting(int motor_speed)
{
        OSTIMER_ON;             
        OSMR1 = OSCR + Usec_Clk * motor_speed;
}

static irqreturn_t DC_MOTOR_InterruptHandler(int irq, void *dev_id, struct pt_regs *regs)
{
        OSTIMER_OFF;
        Dc_Moter_Clock();
        DC_MOTOR_ReSetting(motor_speed);
	return IRQ_HANDLED;
}

static int data_motor_open(struct inode *inode, struct file *filp)
{
        int retval;
		
		retval = request_irq( OSTIMER_IRQ, &DC_MOTOR_InterruptHandler, SA_INTERRUPT, "OST", NULL); 
        	// 인터럽트넘버 , 인터럽트 핸들러 함수 , 인터럽트 플래그 , 인터럽트 네임, 등을 등록 
		if(retval < 0)
        		printk( KERN_ERR "%s: Request for IRQ %d failed\n", __FUNCTION__, OSTIMER_IRQ );
		else
			printk( " %s Request for %d IRQ Success\n", __FUNCTION__, OSTIMER_IRQ ); 	
	//	MOD_INC_USE_COUNT;
        return 0;
}

static int data_motor_release(struct inode *inode, struct file *filp)
{
        OSTIMER_OFF;
       // disable_irq(OSTIMER_IRQ);                                        
        free_irq(OSTIMER_IRQ, NULL);

        MOTOR_ClearBit(0)   // clk low
        MOTOR_ClearBit(1)   // enable low
        MOTOR_ClearBit(2)   // cw/ccw low
        MOTOR_ClearBit(3)   // reset low
        MOTOR_ClearBit(4)   // reset low
        MOTOR_ClearBit(5)   // reset low

       // MOD_DEC_USE_COUNT;
        return 0;        
}                         


static ssize_t data_motor_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
        return 0;
}

static ssize_t data_motor_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos )
{
        return 0;
}

static int data_motor_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch (cmd) { 
		case _IOCTL_LEFT_FORWARD : {
			 OSTIMER_OFF;
			 motor_mask = 0;
			 mask = 1;
			 Dc_Moter_Clock();
			// enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz
			 break;
			}
		case _IOCTL_LEFT_REVERSE : {
			 OSTIMER_OFF;
			 motor_mask = 0;
			 mask = 2;
			 Dc_Moter_Clock();
			// enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz

			 break;
			}

		case _IOCTL_LEFT_STOP : {
			 OSTIMER_OFF;
			 motor_mask = 0;
			 mask = 0;
			 Dc_Moter_Clock();
			// enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz

			 break;
			}

		case _IOCTL_RIGHT_FORWORD : {
			 OSTIMER_OFF;
			 motor_mask = 1;
			 mask = 1;
			 Dc_Moter_Clock();
			 //enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz
			 break;
			}
		case _IOCTL_RIGHT_REVERSE : {
			 OSTIMER_OFF;
			 motor_mask = 1;
			 mask = 2;
			 Dc_Moter_Clock();
			 //enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz

			 break;
			}

		case _IOCTL_RIGHT_STOP : {
			 OSTIMER_OFF;
			 motor_mask = 1;
			 mask = 0;
			 Dc_Moter_Clock();
			// enable_irq(OSTIMER_IRQ);
			 DC_MOTOR_ReSetting(motor_speed);  // 100us (default clk) = 10Hz

			 break;
			}


		default:
			 return 0;
		}
		return 0;
}

static struct file_operations motor_fops = {
	.read	 =	data_motor_read,
	.write	 =	data_motor_write,
	.ioctl 	 =	data_motor_ioctl,
	.open	 =	data_motor_open,
	.release =	data_motor_release,
};

static int data_motor_init(void)
{
	int result;
	unsigned long mem_addr, mem_len;

	result = register_chrdev(DEVMAJOR, DEVNAME, &motor_fops);
    	
	if (result < 0) {
		printk(KERN_WARNING " can't get major \n");
		return result;
	}
	
	mem_addr = _EDU_CS3;
	mem_len  = 0x1000;
	mem_base = ioremap_nocache( mem_addr, mem_len);
	if(!mem_base) {
		printk(" Error mappig dc_motor memory\n");
		return -EBUSY;
	}
	
	DC_MOTOR_Init();	
	printk("X-Hyper 270TKU %s MAJOR %d\n", DEVNAME, DEVMAJOR);
	return 0;
}

static void data_motor_exit(void)
{
        unregister_chrdev(DEVMAJOR, DEVNAME);
	iounmap(mem_base);
}

module_init(data_motor_init);
module_exit(data_motor_exit);

