/*
 * X-HYPER270-TKU IEB Rev
 * Character LCD Device Driver
 * 2006-08-16  <kjlee@hybus.net>
 */

#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/module.h>	

#include <asm/io.h>

#define CLCD_MAJOR      238
#define CLCD_NAME       "clcd"

#define CLCD_WR_ADD_CS	(0x13B00000)
#define CLCD_RS_ADD_CS	(0x13B80000)

#define CLCD_WR_CS	(*((volatile unsigned char *)(mem_base_wr)))
#define CLCD_RS_CS	(*((volatile unsigned char *)(mem_base_rs)))
	 
static void *mem_base_wr, *mem_base_rs;
static unsigned long mem_addr_wr, mem_addr_rs, mem_len;

static void lcd_clear(void)
{
	CLCD_WR_CS = 0x01;
	mdelay(100);	
	return;
}

static void lcd_init(void)
{
	CLCD_WR_CS = 0x38; 
	mdelay(100);
	CLCD_WR_CS = 0x38;
	mdelay(100);
	CLCD_WR_CS = 0x38;
	mdelay(100);
	CLCD_WR_CS = 0x0e; 
	mdelay(100);
	CLCD_WR_CS = 0x02; 
  	mdelay(100);
	CLCD_WR_CS = 0x01; 
	mdelay(100);
}

static void string_out(char *str)
{
	char *s;
	int i=0;
	printk("clcd.o: %s\n",str);
	lcd_init();

	for (s=str; *s; s++){
		CLCD_RS_CS = *s; 

		if(i == 15) { 
			udelay(100);
			CLCD_WR_CS = 0x28; 
			//CLCD_WR_CS = 0xC0; 
		}

		udelay(100);
		i++;
	}
}

static void string_out_up(char *str)
{
	//char *s;
	int i=0;
	printk("clcd.o: %s\n",str);
	lcd_init();

	CLCD_WR_CS = 0x80; 

	while(*str != '\0') {
		
		/*
		if(i == 15) { 
			udelay(100);
			CLCD_WR_CS = 0x28; 
			//CLCD_WR_CS = 0xC0; 
		}
		*/
		CLCD_RS_CS = *str; 
		udelay(100);
		i++;
		str++;
	}
}

static void string_out_dn(char *str)
{
	char *s;
	int i=0;
	printk("clcd.o: %s\n",str);
	lcd_init();

	CLCD_WR_CS = 0xC0; 

	for (s=str; *s; s++){
		CLCD_RS_CS = *s; 

		/*
		if(i == 15) { 
			udelay(100);
			CLCD_WR_CS = 0x28; 
			//CLCD_WR_CS = 0xC0; 
		}
		*/
		
		//udelay(100);
		i++;
	}
}

static int clcd_open (struct inode *inode, struct file *filp)
{
	return 0;          
}

static int clcd_release (struct inode *inode, struct file *filp)
{
	lcd_clear();
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
	lcd_clear();		
	memset(data, 0 , 32);
	copy_from_user(data, buf, count);

	string_out_dn(data);

	/*
	if (flag==0) {
		string_out_up(data);
	}
	else if (flag==1) {
		string_out_dn(data);
	}
	else {	
		string_out(data);
	}*/

	return 0;
}

	
static struct file_operations clcd_fops = {
    write	:	clcd_write,
    ioctl	:	clcd_ioctl,
    open	:	clcd_open,
    release	:	clcd_release,
};

static int clcd_init(void)
{
    int res;
    res = register_chrdev(CLCD_MAJOR, CLCD_NAME, &clcd_fops);
    if (res < 0) {
        printk(KERN_WARNING "Can't get major\n");
        return res;
    }

    	printk("X-Hyper 270TKU %s MAJOR %d\n", CLCD_NAME, CLCD_MAJOR);
	
	mem_addr_wr = CLCD_WR_ADD_CS;
	mem_addr_rs = CLCD_RS_ADD_CS;
        mem_len = 0x1000;
        
        mem_base_wr = ioremap_nocache ( mem_addr_wr, mem_len);
        if( !mem_base_wr){
                printk("Error mapping clcd_wr memory");
                return -EBUSY;
        }
	
	mem_base_rs = ioremap_nocache ( mem_addr_rs, mem_len);
        if( !mem_base_rs){
                printk("Error mapping clcd_rs memory");
                return -EBUSY;
        }
	string_out("http://hybus.netEducation Board");

    return 0;
}

static void clcd_exit(void)
{
	lcd_clear();
	unregister_chrdev(CLCD_MAJOR, CLCD_NAME);
	printk("MAJOR %d, %s is unregisted\n", CLCD_MAJOR, CLCD_NAME);
	iounmap(mem_base_wr);
	iounmap(mem_base_rs);

}
MODULE_LICENSE("Dual BSD/GPL");
module_init(clcd_init);
module_exit(clcd_exit);

