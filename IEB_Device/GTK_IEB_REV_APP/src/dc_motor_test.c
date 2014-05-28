#include "dc_motor_test.h"
#include <sys/types.h>
#include <sys/stat.h>

#include "callbacks.h"
#include "led_test.h"
#include "support.h"
#include "interface.h"
#include <gnome.h>

#define dc_motor_dev "/dev/dc_motor"

#define _IOCTL_LEFT_FORWARD     1    
#define _IOCTL_LEFT_REVERSE     2
#define _IOCTL_LEFT_STOP        3

#define _IOCTL_RIGHT_FORWARD    4
#define _IOCTL_RIGHT_REVERSE    5
#define _IOCTL_RIGHT_STOP       6

static unsigned short flag = 0;
int dev;
void dc_motor_init(){
	dev = open(dc_motor_dev, O_RDWR);
        if (dev < 0){
                fprintf(stderr, "cannot open /dev/dc_motor Device (%d)", dev);
                exit(2);
        }
}

void dc_forward(){
	if(flag == 1)
		ioctl(dev, _IOCTL_LEFT_FORWARD , flag);
	else if(flag == 2)
		ioctl(dev, _IOCTL_RIGHT_FORWARD, flag);
	else
	{
		ioctl(dev, _IOCTL_LEFT_FORWARD , flag);
		ioctl(dev, _IOCTL_RIGHT_FORWARD , flag);
	}
}

void dc_reverse(){
	if(flag == 1)
		ioctl(dev, _IOCTL_LEFT_REVERSE, flag);
	else if(flag == 2)
		ioctl(dev, _IOCTL_RIGHT_REVERSE, flag);
	else
	{
		flag = 3;
		ioctl(dev, _IOCTL_LEFT_REVERSE, flag);
		ioctl(dev, _IOCTL_RIGHT_REVERSE, flag);
	}
}

void dc_left_turn(){
	ioctl(dev, _IOCTL_RIGHT_STOP ,flag);
	if(flag == 3)
		ioctl(dev, _IOCTL_LEFT_REVERSE, flag);
	else
	{
		flag = 1;
		ioctl(dev, _IOCTL_LEFT_FORWARD, flag);
	}
}

void dc_right_turn(){
	ioctl(dev, _IOCTL_LEFT_STOP, flag);
	if(flag == 3)
		ioctl(dev, _IOCTL_RIGHT_REVERSE, flag);
	else
	{
		flag = 2;
		ioctl(dev, _IOCTL_RIGHT_FORWARD, flag);
	}
}

void dc_stop(){
	flag = 0;
 	ioctl(dev, _IOCTL_RIGHT_STOP, flag);
	ioctl(dev, _IOCTL_LEFT_STOP ,flag);
}

