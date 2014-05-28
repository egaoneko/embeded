/*
 * X-HYPER270-TKU IEB Rev
 * GPIO_LED TEST Program
 * 2006-08-24  <kjlee@hybus.net>
 */

#include <stdio.h>
#include <fcntl.h>

static char gpio_testDev[] = "/dev/gpio_led";

#define GPIO_KEY_READ       0x1
#define GPIO_LED1_ON_OFF    0x2
#define GPIO_LED2_ON_OFF    0x3

int ON	= 0;
int OFF	= 1;

int main()
{
	int dev;
	char  buf;

	if((dev = open(gpio_testDev, O_RDWR )) < 0){ 
        	perror("open faile /dev/gpio_led\n");
	        exit(-1);
	}
	
	printf("\n");
	printf("-------------------------\n");
	printf("   GPIO SW to LED TEST	 \n");
	printf("-------------------------\n");
	
	while(1){
		read(dev , &buf, sizeof(buf));	// Key READ
		printf("KEY %d PUSH \n",buf);
		switch(buf)
		{
			case 1:	
				{ 
					ioctl(dev, GPIO_LED1_ON_OFF, &ON);
					ioctl(dev, GPIO_LED2_ON_OFF, &OFF);
					printf("LED1 ON\n");
					break;
				}
			case 2:	
				{ 
					ioctl(dev, GPIO_LED1_ON_OFF, &OFF);
					ioctl(dev, GPIO_LED2_ON_OFF, &ON);
					printf("LED2 ON\n");
					break;
				}
			case 3:
				{
					ioctl(dev, GPIO_LED1_ON_OFF, &ON);
                                        ioctl(dev, GPIO_LED2_ON_OFF, &ON);
					printf("LED1, LED2 ON\n");
					break;
				}
			case 4:
				{
					ioctl(dev, GPIO_LED1_ON_OFF, &OFF);
                                        ioctl(dev, GPIO_LED2_ON_OFF, &OFF);
					printf("LED1, LED2 OFF\n");
					break;
				}
			default:
				{
					printf("No Operation\n");
					break;
				}
		}
	}
	return 0;
}

