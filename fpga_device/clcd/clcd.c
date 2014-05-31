/*
 * XHYPER255_TKU3 -  char lcd
 * lcd.c
 * 2004-07-01   <newboder@hybus.net>
 * 
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>

#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/bitops.h>
#include <asm/hardware.h>
#include <asm/arch/pxa-regs.h>
#include <asm/io.h>

#define CLCD_MAJOR      238
#define CLCD_NAME       "clcd"

/* 
  FPGA
  0x17800000 // CS5 : FPGA_CLCD_WR#i
  0x17840000 // CS5 : FPGA_CLCD_RS
  FND_D[0:7] : X_D[0:7] 
*/
#define FPGA_CLCD_WR_ADD	(0x12300000)
#define FPGA_CLCD_RS_ADD	(0x12380000)
	 
//#define CLCD_CMD_ADDR 	(*((volatile unsigned char *)((void *)mem_base_wr))) 
//#define CLCD_DATA_ADDR 	(*((volatile unsigned char *)((void *)mem_base_rs))) 

static void *mem_base_wr, *mem_base_rs;
static unsigned long mem_addr_wr, mem_addr_rs, mem_len;


static void lcd_init(void)
{
	*((volatile unsigned char *)(mem_base_wr)) = 0x38; 
	mdelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x38; 
	mdelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x38; 
	mdelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x0e; 
	mdelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x02; 
  	mdelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x01; 
	mdelay(100);
}

static void string_out(char *str)
{
	char *s;
	int i=0;

	printk("clcd.o: %s\n", str);

	lcd_init();

	for (s=str; *s; s++){
	*((volatile unsigned char *)(mem_base_rs)) = *s; 
		if(i == 15) { 
			udelay(100);
			*((volatile unsigned char *)(mem_base_wr)) = 0xC0; 
		}

		udelay(100);
		i++;
	}
}

static void string_out_up(char *str)
{
	char *s;
	int i=0;
	printk("clcd.o: %s\n",str);
	//lcd_init();

	udelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0x80; 
	udelay(100);

	for (s=str; *s; s++){
		*((volatile unsigned char *)(mem_base_rs)) = *s; 
		udelay(100);
		i++;
	}
}

static void string_out_dn(char *str)
{
	char *s;
	int i=0;
	printk("clcd.o: %s\n",str);
	//lcd_init();

	udelay(100);
	*((volatile unsigned char *)(mem_base_wr)) = 0xC0; 
	udelay(100);

	for (s=str; *s; s++){
		*((volatile unsigned char *)(mem_base_rs)) = *s; 
		udelay(100);
		i++;
	}
}

static int clcd_open (struct inode *inode, struct file *filp)
{
    return 0;          /* success */
}

static int clcd_release (struct inode *inode, struct file *filp)
{
    return 0;
}

static int clcd_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case 1:
			{
 				string_out("http://hybus.netEducation Board");
				break;
			}
		default:
			return 0;
	}
	return 0;
}

static ssize_t clcd_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    char data[32];

    memset(data, 0 , 32);
    copy_from_user(data, buf, count);

    lcd_init();
    string_out(data);


    return 0;
}

static ssize_t clcd_writeup (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    char data[16];

    memset(data, 0 , 16);
    copy_from_user(data, buf, count);

    lcd_init();
    string_out_up(data);


    return 0;
}

static ssize_t clcd_writedn (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    char data[16];

    memset(data, 0 , 16);
    copy_from_user(data, buf, count);

    lcd_init();
    string_out_dn(data);


    return 0;
}

	
static struct file_operations clcd_fops = {
    .write	=	clcd_write,
    .writeup	=	clcd_writeup,
    .writedn	=	clcd_writedn,
    .ioctl	=	clcd_ioctl,
    .open	=	clcd_open,
    .release	=	clcd_release,
};

static int clcd_init(void)
{
    int res;
    res = register_chrdev(CLCD_MAJOR, CLCD_NAME, &clcd_fops);
    if (res < 0) {
        printk(KERN_WARNING " can't get major \n");
        return res;
    }

    	printk("X-Hyper 270TKU %s MAJOR %d\n", CLCD_NAME, CLCD_MAJOR);
	
	mem_addr_wr =  FPGA_CLCD_WR_ADD;
	mem_addr_rs =  FPGA_CLCD_RS_ADD;
        mem_len  =  0x1000;
        
        mem_base_wr = ioremap_nocache ( mem_addr_wr, mem_len);
        if( !mem_base_wr) {
                printk("Error mapping clcd_wr memery");
                return -EBUSY;
        }
	
	mem_base_rs = ioremap_nocache ( mem_addr_rs, mem_len);
        if( !mem_base_rs) {
                printk("Error mapping clcd_rs memery");
                return -EBUSY;
        }
	string_out("http://hybus.netEducation Board");

    return 0;
}

static void clcd_exit(void)
{
	unregister_chrdev(CLCD_MAJOR, CLCD_NAME);
	iounmap(mem_base_wr);
	iounmap(mem_base_rs);

}

module_init(clcd_init);
module_exit(clcd_exit);

/* EOF */
