/* =================================================
 * Program ID : dot.c
 * Author     : Gwibong, LEE
 * Create Date: 2014-05-24
 * Compile Row: make - Reference Makefile
 * Description: FPGA 8bit DOT control Module Program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/delay.h>

#include <asm/hardware.h>
#include <asm/delay.h>
#include <asm/arch/pxa-regs.h>
#include <asm/io.h>

#define DOT_DEVMAJOR	232
#define DOT_DEVNAME	"dot"
#define DOT_RESET	4
#define FPGA_DOT_COL_1		(0x11800000)
#define FPGA_DOT_COL_2		(0x11900000)
#define FPGA_DOT_COL_3		(0x11A00000)
#define FPGA_DOT_COL_4		(0x11B00000)
#define FPGA_DOT_COL_5		(0x11C00000)

static void *mem_dot_col1, *mem_dot_col2, *mem_dot_col3, *mem_dot_col4, *mem_dot_col5;

#define DOT_COL_1		(*((volatile unsigned char *)(mem_dot_col1)))
#define DOT_COL_2		(*((volatile unsigned char *)(mem_dot_col2)))
#define DOT_COL_3		(*((volatile unsigned char *)(mem_dot_col3)))
#define DOT_COL_4		(*((volatile unsigned char *)(mem_dot_col4)))
#define DOT_COL_5		(*((volatile unsigned char *)(mem_dot_col5)))

static int dot_reset(void)
{
	GPCR(DOT_RESET) |= GPIO_bit(DOT_RESET);
	GPSR(DOT_RESET) |= GPIO_bit(DOT_RESET);
/* ----------------------------------------
	DOT_COL_1	= 0x00;
	DOT_COL_2	= 0x00;
	DOT_COL_3	= 0x00;
	DOT_COL_4	= 0x00;
	DOT_COL_5	= 0x00;
   ---------------------------------------- */

	return 0;
}
static int dot_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg)
{
	return 0;
}

static int dot_open(struct inode *minode, struct file *mfile)
{
	dot_reset();
	return 0;
}

static int dot_release(struct inode *minode, struct file *mfile)
{
	return 0;
}

static ssize_t dot_write (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	unsigned char dot_data[5]={0};
	int col_number;
	
//	get_user(dot_data, (unsigned char *)buf);
	copy_from_user(dot_data, buf, count);
	for ( col_number =0 ; col_number < 6 ; col_number++) {
		switch( col_number) {
			case 1 : DOT_COL_1 = dot_data[0]; break;
			case 2 : DOT_COL_2 = dot_data[1]; break;
			case 3 : DOT_COL_3 = dot_data[2]; break;
			case 4 : DOT_COL_4 = dot_data[3]; break;
			case 5 : DOT_COL_5 = dot_data[4]; break;
		}
	}

	return 0;
}


static struct file_operations dot_fops = {
	.write		= 	dot_write,
	.open		=	dot_open,
	.release	=	dot_release,
	.ioctl		= 	dot_ioctl,
};

static int __init dot_init(void){
	int res;
	unsigned long mem_addr_col1, mem_addr_col2, mem_addr_col3, mem_addr_col4, mem_addr_col5;
	unsigned long mem_len;

	res=register_chrdev(DOT_DEVMAJOR, DOT_DEVNAME, &dot_fops);
	if(res < 0) {
		printk(KERN_ERR " dots : failed to register device.\n"); 
		return res;
	}
	
	mem_addr_col1 =  FPGA_DOT_COL_1;
	mem_addr_col2 =  FPGA_DOT_COL_2;
	mem_addr_col3 =  FPGA_DOT_COL_3;
	mem_addr_col4 =  FPGA_DOT_COL_4;
	mem_addr_col5 =  FPGA_DOT_COL_5;
        mem_len  =  0x1000;

        mem_dot_col1 = ioremap_nocache (mem_addr_col1, mem_len);
        if( !mem_dot_col1) {
                printk("Error mapping col1 memery");
                return -EBUSY;
        }
        mem_dot_col2 = ioremap_nocache (mem_addr_col2, mem_len);
        if( !mem_dot_col2) {
                printk("Error mapping col2 memery");
                return -EBUSY;
        }

        mem_dot_col3 = ioremap_nocache (mem_addr_col3, mem_len);
        if( !mem_dot_col3) {
                printk("Error mapping col3 memery");
                return -EBUSY;
        }

        mem_dot_col4 = ioremap_nocache (mem_addr_col4, mem_len);
        if( !mem_dot_col4) {
                printk("Error mapping col4 memery");
                return -EBUSY;
        }

        mem_dot_col5 = ioremap_nocache (mem_addr_col5, mem_len);
        if( !mem_dot_col5) {
                printk("Error mapping col5 memery");
                return -EBUSY;
        }

	printk("X-Hyper 270TKU %s MAJOR %d\n", DOT_DEVNAME, DOT_DEVMAJOR);

	return 0;		 
}

static void __exit dot_exit(void)
{
	unregister_chrdev(DOT_DEVMAJOR, DOT_DEVNAME);
	iounmap(mem_dot_col1);
	iounmap(mem_dot_col2);
	iounmap(mem_dot_col3);
	iounmap(mem_dot_col4);
	iounmap(mem_dot_col5);
	printk(" %s unregisterd. \n",DOT_DEVNAME);	
}

module_init(dot_init);
module_exit(dot_exit);


