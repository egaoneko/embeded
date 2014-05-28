/*
 * X-HYPER270-TKU IEB Rev
 * DC Motor Device Driver
 * 2006-08-16  <kjlee@hybus.net>
 */

#include <linux/fs.h>
#include <linux/interrupt.h>

#include <asm/arch/pxa-regs.h>
#include <asm/io.h>

#define _IOCTL_LEFT_FORWARD		1
#define _IOCTL_LEFT_REVERSE		2
#define _IOCTL_LEFT_STOP		3

#define _IOCTL_RIGHT_FORWORD		4
#define _IOCTL_RIGHT_REVERSE		5
#define _IOCTL_RIGHT_STOP		6

#define DC_MOTOR_CS			(0x13A00000)
#define DC_MAJOR			237
#define DC_NAME				"dc_motor"

#define DC_MOTOR   (*((volatile unsigned char *)(mem_base)))

#define MOTOR_SetBit(x) { dc_motor_port |= (1<<x); DC_MOTOR = dc_motor_port; }
#define MOTOR_ClearBit(x) { dc_motor_port &= ~(1<<x); DC_MOTOR = dc_motor_port; }

static void *mem_base;
static unsigned short dc_motor_port;
int motor_mask = 0, mask = 0;

static void motor_init(void)
{
	MOTOR_SetBit(0)   // clk low
        MOTOR_SetBit(1)   // enable low
        MOTOR_SetBit(2)   // cw/ccw low
        MOTOR_SetBit(3)   // reset low
        MOTOR_SetBit(4)   // reset low
        MOTOR_SetBit(5)   // reset low
}

static void dc_motor_op(void)
{
	// LEFT Motor
	if ( motor_mask == 0 )
	{			    
		if(mask == 1 )			// Forward
		{
			MOTOR_ClearBit(1);    
	    		MOTOR_SetBit(0);     
	    		MOTOR_SetBit(4);     
		}
		else if (mask == 2)		// Reverse
		{
			MOTOR_ClearBit(0);    
	    		MOTOR_SetBit(1);  
	    		MOTOR_SetBit(4);     
		}
		else				// Stop
		{
	        	MOTOR_ClearBit(0); 
	    		MOTOR_ClearBit(1);    
			MOTOR_ClearBit(4);	// Reset low
		}
	}
	else
	// RIGHT Motor
	{
		if(mask == 1 )			// Forward
		{		  
	    		MOTOR_ClearBit(3);    
	    		MOTOR_SetBit(2);     
	    		MOTOR_SetBit(5);     
		}
		else if (mask == 2)		// Reverse
		{
			MOTOR_ClearBit(2);    
	    		MOTOR_SetBit(3);  
	    		MOTOR_SetBit(5);     
		}
		else				// Stop
		{
		       	MOTOR_ClearBit(3); 
	    		MOTOR_ClearBit(2);    
        		MOTOR_ClearBit(5);	// Reset low
		}
	}
}

static int dc_motor_open(struct inode *inode, struct file *filp)
{
	motor_init();	
	//MOD_INC_USE_COUNT;
        return 0;
}

static int dc_motor_release(struct inode *inode, struct file *filp)
{
        MOTOR_ClearBit(0)   // clk low
        MOTOR_ClearBit(1)   // enable low
        MOTOR_ClearBit(2)   // cw/ccw low
        MOTOR_ClearBit(3)   // reset low
        MOTOR_ClearBit(4)   // reset low
        MOTOR_ClearBit(5)   // reset low

        //MOD_DEC_USE_COUNT;
        return 0;        
}                         


static ssize_t dc_motor_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
        return 0;
}

static ssize_t dc_motor_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos )
{
        return 0;
}

static int dc_motor_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{ 
		case _IOCTL_LEFT_FORWARD :
		{
			 motor_mask = 0;
			 mask = 1;
			 dc_motor_op();
			 break;
		}
		case _IOCTL_LEFT_REVERSE :
		{
			 motor_mask = 0;
			 mask = 2;
			 dc_motor_op();
			 break;
		}
		case _IOCTL_LEFT_STOP :
		{
			 motor_mask = 0;
			 mask = 0;
			 dc_motor_op();
			 break;
		}
		case _IOCTL_RIGHT_FORWORD :
		{
			 motor_mask = 1;
			 mask = 1;
			 dc_motor_op();
			 break;
		}
		case _IOCTL_RIGHT_REVERSE :
		{
			 motor_mask = 1;
			 mask = 2;
			 dc_motor_op();
			 break;
		}
		case _IOCTL_RIGHT_STOP :
		{
			 motor_mask = 1;
			 mask = 0;
			 dc_motor_op();
			 break;
		}
		default:
			 return 0;
	}
	return 0;
}

static struct file_operations motor_fops = {
	read	 :	dc_motor_read,
	write	 :	dc_motor_write,
	ioctl 	 :	dc_motor_ioctl,
	open	 :	dc_motor_open,
	release  :	dc_motor_release,
};

static int __init dc_motor_init(void)
{
	int result;
	unsigned long mem_addr, mem_len;

	result = register_chrdev(DC_MAJOR, DC_NAME, &motor_fops);
    	
	if(result < 0) {
		printk(KERN_WARNING "Can't get major \n");
		return result;
	}
	
	mem_addr = DC_MOTOR_CS;
	mem_len  = 0x1000;
	mem_base = ioremap_nocache(mem_addr, mem_len);
	if(!mem_base) {
		printk("Error mappig dc_motor memory\n");
		return -EBUSY;
	}
	
	printk("X-Hyper 270TKU %s MAJOR %d\n", DC_NAME, DC_MAJOR);
	return 0;
}

static void __exit dc_motor_exit(void)
{
        unregister_chrdev(DC_MAJOR, DC_NAME);
	printk("MAJOR %d, %s is ungeristed\n", DC_MAJOR, DC_NAME);
	iounmap(mem_base);
}

module_init(dc_motor_init);
module_exit(dc_motor_exit);

