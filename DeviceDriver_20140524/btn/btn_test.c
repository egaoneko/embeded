/* =================================================
 * Program ID : btn_test.c
 * Author     : Gwibong, LEE
 * Create Date: 2014-05-24
 * Compile Row: make - Reference Makefile
 * Description: GPIO Button test program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include <stdio.h>
#include <fcntl.h>

static char btn_dev[] = "/dev/BTN";
static int  btn_fd = (-1);

#define GPIO_BTN_READ       0x1000

int main()
{
	char  buf;

	if(( btn_fd = open( btn_dev, O_RDWR )) < 0){ 
		printf("Failed to open %s\n", btn_dev);
		exit(-1);
	}

	while(1) {
		read( btn_fd, &buf, sizeof(buf));	// BTN READ
		printf("GPIO BTN %x PUSH \n",buf);
		switch(buf) {
			default: break;
		}
	}
	return 0;
}
