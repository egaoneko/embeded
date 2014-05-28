/*	
 * X-Hyper270-TKU IEB Rev
 * DIP SW Device Driver
 * 2006-08-21	<kjlee@hybus.net>
 */

#include <linux/poll.h>
#include <linux/ioport.h>
#include <asm/io.h>

#define DIP_MAJOR	240
#define DIP_NAME	"dip"
#define DIP_ADDR	(0x13000000)
#define DIP_CS		(*((volatile unsigned char *)(mem_base)));

static void  *mem_base;
unsigned long mem_addr, mem_len;
unsigned char dip_data;

static int dip_clear(void){
	dip_data = 0x00;
	return 0;
}

static int dip_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg){
	return 0;
}

static int dip_open(struct inode *minode, struct file *mfile){
	dip_clear();
	return 0;
}

static int dip_release(struct inode *minode, struct file *mfile){
	dip_clear();
	return 0;
}

static ssize_t dip_read (struct file *filp, char *buf, size_t count, loff_t *f_pos){
	dip_data = DIP_CS;
	copy_to_user(buf, &dip_data, sizeof(dip_data));
	return 0;
}


static ssize_t dip_write (struct file *file, const char *buf, size_t count, loff_t *f_pos){
	return 0;
}

static struct file_operations dip_fops = {
	read	:	dip_read,
	write	: 	dip_write,
	open	:	dip_open,
	release	:	dip_release,
	ioctl	:	dip_ioctl,
};

static int __init dip_init(void){

	int res;

	res = register_chrdev(DIP_MAJOR, DIP_NAME, &dip_fops);
	if(res < 0)
	{
		printk(KERN_ERR "DIP SW : Failed to regist device.\n"); 
		return res;
	}
	
	mem_addr =  DIP_ADDR;
	mem_len	 =  0x1000;
	mem_base = ioremap_nocache(mem_addr, mem_len);
	if(!mem_base) {
		printk("Error mapping DIP_SW memory\n");
		release_mem_region(mem_addr, mem_len);
		return -EBUSY;
	}
 	printk("X-Hyper 270TKU %s MAJOR %d\n", DIP_NAME, DIP_MAJOR);	
	return 0;		 

}

static void __exit dip_exit(void){
	dip_clear();
	unregister_chrdev(DIP_MAJOR, DIP_NAME);
	printk("MAJOR %d, %s is unregisted\n", DIP_MAJOR, DIP_NAME);
	iounmap(mem_base);
	
}

module_init(dip_init);
module_exit(dip_exit);

