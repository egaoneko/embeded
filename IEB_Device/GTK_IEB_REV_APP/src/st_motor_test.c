#include "st_motor_test.h"
#include <sys/types.h>
#include <sys/stat.h>

#include "callbacks.h"
#include "led_test.h"
#include "support.h"
#include "interface.h"
#include <gnome.h>

#define stmotor_dev "/dev/st_motor"
#define MOTOR_Forward       0x1
#define MOTOR_Reverse       0x2
#define MOTOR_SpeedUp       0x3
#define MOTOR_SpeedDown     0x4
#define MOTOR_STOP          0x5

static int dev;

void st_motor_init(){

	dev = open(stmotor_dev, O_RDWR);
	if (dev < 0){
                fprintf(stderr, "cannot open Step Motor Device (%d)", dev);
                exit(2);
        }

}

void st_forward(){
	ioctl(dev, MOTOR_Forward, 0);
}

void st_reverse(){
	ioctl(dev, MOTOR_Reverse, 0);
}

void speed_up(){
	ioctl(dev, MOTOR_SpeedUp, 0);
}

void speed_down(){
	ioctl(dev, MOTOR_SpeedDown, 0);
}

void st_stop(){
	ioctl(dev, MOTOR_STOP, 0);
}


