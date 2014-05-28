#include <sys/types.h>
#include <sys/stat.h>

#include "callbacks.h"
#include "led_test.h"
#include "support.h"
#include "interface.h"
#include <gnome.h>

#define led_dev "/dev/led"
//#define LED_SET(data)   { led_data |= data ; write(dev, &led_data, sizeof(unsigned char));}
//#define LED_CLEAR(data) { led_data &= ~(data) ; write(dev, &led_data,sizeof(unsigned char));
static int dev;
static unsigned char data, led_data;
static int check_led1, check_led2, check_led3, check_led4, check_led5, check_led6, check_led7, check_led8;

void led_init(){

	dev = open(led_dev, O_RDWR);
        if (dev < 0){
                fprintf(stderr, "cannot open LED Device (%d)", dev);
                exit(2);
        }
	check_led1 = check_led2 = check_led3 = check_led4 = check_led5 = check_led6 = check_led7 = check_led8 =0;
	led_data = 0xff;
	write(dev, &led_data, sizeof(unsigned char));	

}

void led1_tog(){
        if (! check_led1)
        {
		data = 0x01;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led1 = 1; 
	}
        else    { 
		data = 0x01;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led1 = 0; 
	}
}
void led2_tog(){
        if (! check_led2)
        {
		data = 0x02;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led2 = 1; 
	}
        else    { 
		data = 0x02;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led2 = 0; 
	}
}

void led3_tog(){
        if (! check_led3)
        {
		data = 0x04;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led3 = 1; 
	}
        else    { 
		data = 0x04;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led3 = 0; 
	}
}
void led4_tog(){
        if (! check_led4)
        {
		data = 0x08;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led4 = 1; 
	}
        else    { 
		data = 0x08;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led4 = 0; 
	}
}

void led5_tog(){
        if (! check_led5)
        {
		data = 0x10;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led5 = 1; 
	}
        else    { 
		data = 0x10;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led5 = 0; 
	}
}


void led6_tog(){
        if (! check_led6)
        {
		data = 0x20;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led6 = 1; 
	}
        else    { 
		data = 0x20;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led6 = 0; 
	}
}

void led7_tog(){
        if (! check_led7)
        {
		data = 0x40;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led7 = 1; 
	}
        else    { 
		data = 0x40;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led7 = 0; 
	}
}


void led8_tog(){
        if (! check_led8)
        {
		data = 0x80;
		led_data  &= ~(data); 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led8 = 1; 
	}
        else    { 
		data = 0x80;
		led_data  |= data; 
		write(dev, &led_data, sizeof(unsigned char));	
 		check_led8 = 0; 
	}
}




