/*
 * XHYPER270B
 * btn test.c
 * 2005-10-10   <newboder@hybus.net>	: create
 * 2006-04-21   <toeen@hybus.net>		: modify
 * 
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

	while(1){
		read( btn_fd, &buf, sizeof(buf));	// BTN READ
		printf("GPIO BTN %x PUSH \n",buf);
		switch(buf)
		{
			default: break;
		}
	}
	return 0;
}
