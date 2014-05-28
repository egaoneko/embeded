/****************************************************************
270TKU FPGA 8bit LED DEVICE TEST



****************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/ioport.h>

#include <asm/hardware.h>
#include <asm/delay.h>
#include <asm/arch/pxa-regs.h>
#include <asm/io.h>

#define LED_DEVMAJOR	239
#define LED_DEVNAME	"led"
#define LED_PHYS	0x12400000


static void  *mem_base;
unsigned long mem_addr, mem_len;

static int led_shift(void){
	unsigned char data, data2;
	data = 0x01;
	while(1)
	{
	
		data2 = (~(data >> 7)) & 0x01;
		data  = (data << 1 ) | data2;
		mdelay(1000);
		
		(*((volatile unsigned char *)(mem_base))) = data;		
	}
}

static int led_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg){

	
	return 0;
}

static int led_open(struct inode *minode, struct file *mfile){
	
	return 0;
	
}

static int led_release(struct inode *minode, struct file *mfile){

	return 0;

}

static ssize_t led_write (struct file *file, const char *buf, size_t count, loff_t *f_pos){
	
	unsigned char led_data;

	get_user(led_data, (unsigned char *)buf);
//	copy_from_user(led_data, (unsigned char*)buf, count);
	
	(*((volatile unsigned char *)(mem_base))) = led_data;		
	return 0;
}

static ssize_t led_read (struct file *file, const char *buf, size_t count, loff_t *f_pos){
	return 0;
}

static struct file_operations led_fops = {
	.read		= 	led_read,
	.write		= 	led_write,
	.open		=	led_open,
	.release	=	led_release,
	.ioctl		= 	led_ioctl,
};

static int __init led_init(void){

	int res;

	res=register_chrdev(LED_DEVMAJOR, LED_DEVNAME, &led_fops);
	if(res < 0)
	{
		printk(KERN_ERR " leds : failed to register device.\n"); 
		return res;
	}
	
	mem_addr =  LED_PHYS;
	mem_len	 =  0x1000;
	mem_base = ioremap_nocache ( mem_addr, mem_len);
	if( !mem_base) {
		printk("Error mapping OHCI memery\n");
		release_mem_region(mem_addr, mem_len);
		return -EBUSY;
	}
	//led_shift();
 	printk("X-Hyper 270TKU %s MAJOR %d\n", LED_DEVNAME, LED_DEVMAJOR);	
	return 0;		 

}

static void __exit led_exit(void){
	unregister_chrdev(LED_DEVMAJOR, LED_DEVNAME);
	printk(" %s unregisterd. \n",LED_DEVNAME);	
	iounmap(mem_base);
	
}

module_init(led_init);
module_exit(led_exit);
