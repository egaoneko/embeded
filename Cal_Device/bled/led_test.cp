/*
 * X-HYPER270-TKU IEB Board Rev
 * BUS LED Control Program
 * 2006-08-16   <kjlee@hybus.net>
 */

#include <stdio.h>
#include <fcntl.h>

#define led_dev	"/dev/led"

#define UP	0x31
#define DOWN	0x32
#define ALL 	0x33
#define EXIT	0x30

char print_menu(void){

	char key;
	
	printf("\n");
	printf("******** BLED Menu ********\n");
	printf("*1. LED UP    Shift       *\n");
	printf("*2. LED DOWN  Shift       *\n");
	printf("*3. ALL                   *\n");
	printf("*0. EXIT    	          *\n");
	printf("***************************\n");
	printf("\n");
	
	printf("Select the number in menu :");
	key =  getc(stdin);
	getc(stdin);
	return key;
}
	
void led_down_shift(int *dev){
		
	unsigned char data, data2;
	int led_device, count;

        for ( count = 0; count <16 ; count++){       
		data2 = (~(data >> 7)) & 0x01;
                data  = (data << 1 ) | data2;
		usleep(50000);
		write (*dev, &data, sizeof(unsigned char));
        }
}

void led_up_shift(int *dev){

	unsigned char data, data2;
       	int led_device, count;

	for( count =0 ; count < 16 ; count++) {
                data2 = (~(data << 7)) & 0x80;
                data  = (data >> 1 ) | data2;
		usleep(50000);
		write (*dev, &data, sizeof(unsigned char));
        }
}

void led_all( int *dev){
	unsigned char data;
	int led_device, count;

	for( count =0 ; count <16; count ++) {
		if( count % 2){
			data = 0xff;
			write(*dev, &data, sizeof(unsigned char));
		}
		else{ 	
			data = 0x00;
			write(*dev, &data, sizeof(unsigned char));
		}
		usleep(100000);
	}
}


int main(){

	char key;
	int dev;
	
	dev = open(led_dev, O_RDWR);
	if (dev < 0){
		fprintf(stderr, "Cannot open LED Device (%d)", dev);
		exit(2);
	}
	led_up_shift(&dev);
	led_all(&dev);
	led_down_shift(&dev);	

	while((key = print_menu()) != EXIT){
		if(key == UP)	
			led_up_shift( &dev);
		else if (key== DOWN)	
			led_down_shift(&dev);
		else if (key == ALL)	
			led_all(&dev);
		else
			printf("Unknow command...n");
	}
	printf("EXIT Program \n");
	close(dev);
	return 0;
}


