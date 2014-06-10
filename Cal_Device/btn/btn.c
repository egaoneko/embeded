/* =================================================
 * Program ID : btn.c
 * Author     : SUM Project
 * Create Date: 2014-06-09
 * Compile Row: make - Reference Makefile
 * Description: GPIO Button control module program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include <linux/config.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/string.h>
#include <linux/interrupt.h>

#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/arch/pxa-regs.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/mach/irq.h>

#include <asm/mach-types.h>
#include <asm/arch/pxa-regs.h>

#define IRQ_BTN1        IRQ_GPIO(35)   //FF-RTS
#define IRQ_BTN2        IRQ_GPIO(41)   //FF-DTR
#define IRQ_BTN3        IRQ_GPIO(36)   //FF-RI
#define IRQ_BTN4        IRQ_GPIO(37)   //FF-DSR

#define BTN_MAJOR 	241
#define BTN_NAME     	"btn"

#define GPIO_BTN_READ	0x1000

#define DUMMY_DELAY 	mdelay(2)

char btn_buf;
DECLARE_WAIT_QUEUE_HEAD(btn_queue);

int btn_open(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0;
}

int btn_release(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0;
}                         

ssize_t btn_write(struct file *filp, const char *buf, size_t length, loff_t *f_pos)
{
	return 0;
}

ssize_t btn_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	interruptible_sleep_on ( &btn_queue );

	copy_to_user( buf, &btn_buf, sizeof(btn_buf));
	return 0;
}

int btn_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
//	int data = 0;
	int ret = 0;

	/*You can add any ioctl command*/
	switch (cmd) {
		case GPIO_BTN_READ:
			copy_to_user((void *)arg, &btn_buf,sizeof(btn_buf));
			btn_buf = 0;					
			return 0;
		default:
			return -EINVAL;
	}
	return ret;
}

static irqreturn_t btn_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	if(GPLR1 & GPIO_bit(35))	btn_buf = 1;
	else if(GPLR1 & GPIO_bit(41))	btn_buf = 2;
	else if(GPLR1 & GPIO_bit(36))	btn_buf = 3;
	else if(GPLR1 & GPIO_bit(37))	btn_buf = 4;
	else				btn_buf = 0;

	wake_up_interruptible(&btn_queue);
	return IRQ_HANDLED;
}

struct file_operations btn_fops = {
	open:       btn_open,
	read:       btn_read,		    
	write:      btn_write,
	ioctl:      btn_ioctl,
	release:    btn_release,
};

static int __init btn_init(void)
{
	int result, ret;

	result = register_chrdev(BTN_MAJOR, BTN_NAME, &btn_fops);

	set_irq_type(IRQ_BTN1, IRQT_RISING);
	set_irq_type(IRQ_BTN2, IRQT_RISING);
	set_irq_type(IRQ_BTN3, IRQT_RISING);
	set_irq_type(IRQ_BTN4, IRQT_RISING);

	if ((ret = request_irq(IRQ_BTN1, btn_interrupt, SA_INTERRUPT, "GPIO35_BTN1", NULL))) {
		printk("failed to register IRQ BTN1\n");
		return ret;
	}

	if ((ret = request_irq(IRQ_BTN2, btn_interrupt, SA_INTERRUPT, "GPIO40_BTN2", NULL))) {
		printk("failed to register IRQ BTN2\n");
		return ret;
	}

	if ((ret = request_irq(IRQ_BTN3, btn_interrupt, SA_INTERRUPT, "GPIO36_BTN3", NULL))) {
		printk("failed to register IRQ BTN3\n");
		return ret;
	}

	if ((ret = request_irq(IRQ_BTN4, btn_interrupt, SA_INTERRUPT, "GPIO37_BTN4", NULL))) {
		printk("failed to register IRQ BTN4\n");
		return ret;
	}

	printk("%s MAJOR %d\n", BTN_NAME, BTN_MAJOR);

	return 0;
}

static void __exit btn_exit(void)
{
	disable_irq(IRQ_BTN1);
	free_irq(IRQ_BTN1, NULL);

	disable_irq(IRQ_BTN2);
	free_irq(IRQ_BTN2, NULL);

	disable_irq(IRQ_BTN3);
	free_irq(IRQ_BTN3, NULL);

	disable_irq(IRQ_BTN4);
	free_irq(IRQ_BTN4, NULL);

	unregister_chrdev( BTN_MAJOR, BTN_NAME);
}

module_init(btn_init);
module_exit(btn_exit);

/* EOF */
