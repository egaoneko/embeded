/* =================================================
 * Program ID : led.c
 * Author     : SUM Project
 * Create Date: 2014-06-09
 * Compile Row: make - Reference Makefile
 * Description: FPGA 8bit LED test program
 *            : with XHYPER270-TKU
 * =================================================
 */
#include <linux/poll.h>
#include <linux/ioport.h>
#include <asm/io.h>

#define LED_DEVMAJOR	239
#define LED_DEVNAME	"led"
#define LED_PHYS	(0x13C00000)
#define LED_CS		(*((volatile unsigned char *)(mem_base)))	

static void  *mem_base;
unsigned long mem_addr, mem_len;

/* clear LED */
static int led_clear(void){
	LED_CS = 0xFF;
	return 0;
}

static int led_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg){
	return 0;
}

static int led_open(struct inode *minode, struct file *mfile){
	led_clear();
	return 0;
	
}

static int led_release(struct inode *minode, struct file *mfile){
	led_clear();
	return 0;

}

static ssize_t led_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	return 0;
}


static ssize_t led_write(struct file *file, const char *buf, size_t count, loff_t *f_pos){
	unsigned char led_data;

	get_user(led_data, (unsigned char *)buf);		/* read Memory */
	LED_CS = led_data;								/* Turn on the led */						
	return 0;
}

static struct file_operations led_fops = {
	read	:	led_read,
	write	: 	led_write,
	open	:	led_open,
	release	:	led_release,
	ioctl	:	led_ioctl,
};

static int __init led_init(void){
	int res;

	res = register_chrdev(LED_DEVMAJOR, LED_DEVNAME, &led_fops);
	if(res < 0)
	{
		printk(KERN_ERR "LEDs : Failed to regist device.\n"); 
		return res;
	}
	
	mem_addr =  LED_PHYS;
	mem_len	 =  0x1000;
	mem_base = ioremap_nocache(mem_addr, mem_len);
	if(!mem_base) {
		printk("Error mapping BLED memory\n");
		release_mem_region(mem_addr, mem_len);
		return -EBUSY;
	}
 	printk("X-Hyper 270TKU %s MAJOR %d\n", LED_DEVNAME, LED_DEVMAJOR);	
	return 0;		 
}

static void __exit led_exit(void){
	led_clear();
	unregister_chrdev(LED_DEVMAJOR, LED_DEVNAME);
	printk("MAJOR %d, %s is unregisted\n", LED_DEVMAJOR, LED_DEVNAME);	
	iounmap(mem_base);
	return;
}

module_init(led_init);
module_exit(led_exit);

