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

#define _IOCTL_RIGHT_FORWORD    4
#define _IOCTL_RIGHT_REVERSE    5
#define _IOCTL_RIGHT_STOP       6

static unsigned short flag;
int dev;
void dc_motor_init(){
	dev = open(dc_motor_dev, O_RDWR);
        if (dev < 0){
                fprintf(stderr, "cannot open /dev/dc_motor Device (%d)", dev);
                exit(2);
        }
}

void dc_forward(){
	ioctl(dev, _IOCTL_LEFT_FORWARD ,flag);
	ioctl(dev, _IOCTL_RIGHT_FORWORD ,flag);
}

void dc_reverse(){
	ioctl(dev, _IOCTL_LEFT_REVERSE, flag);
	ioctl(dev, _IOCTL_RIGHT_REVERSE, flag);
}

void dc_left_turn(){
	ioctl(dev, _IOCTL_LEFT_STOP ,flag);
	ioctl(dev, _IOCTL_RIGHT_FORWORD, flag);
}

void dc_right_turn(){
	ioctl(dev,_IOCTL_RIGHT_STOP, flag);
	ioctl(dev, _IOCTL_LEFT_FORWARD, flag);
}

void dc_stop(){

 	ioctl(dev,_IOCTL_RIGHT_STOP, flag);
	ioctl(dev, _IOCTL_LEFT_STOP ,flag);
}

