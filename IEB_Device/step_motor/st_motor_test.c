/*
 * X-HYPER270-TKU IEB Board Rev
 * STEPPING Motor Control Program
 * 2006-08-17   <kjlee@hybus.net>
 */

#include    <stdio.h>
#include    <fcntl.h>

#define MOTOR_Forward       0x1
#define MOTOR_Reverse       0x2
#define MOTOR_SpeedUp       0x3
#define MOTOR_SpeedDown     0x4
#define MOTOR_STOP          0x5

#define stmotor_dev	"/dev/st_motor"

int main_menu(void){
	char key;
	printf("\n\n");
	printf("********* ST MOTOR MENU ********\n");
	printf("* 1. MOTOR Forward	       *\n");
	printf("* 2. MOTOR Reverse             *\n");
	printf("* 3. MOTOR Speed Up            *\n");
	printf("* 4. MOTOR Speed Down          *\n");
	printf("* 5. MOTOR STOP                *\n");
	printf("* 0. Exit Program              *\n");
	printf("********************************\n");
	printf("\n\n");

	printf("Select the command number : ");
	key = getc(stdin);
	getc(stdin);
	return key;
}

main(int ac, char *av[]){
	char key;
	int dev;

	dev = open(stmotor_dev, O_RDWR );
    	if(dev < 0){
        fprintf(stderr, "Cannot open ST_MOTOR (%d)", dev);
        exit(2);
    	}

	while((key = main_menu()) != 0x30){
		switch(key){
			case 0x31: printf("MOTOR Forward \n");
				   ioctl(dev, MOTOR_Forward, 0);
				   break;
			case 0x32: printf("MOTOR Reverse \n");
				   ioctl(dev, MOTOR_Reverse, 0);
				   break;
			case 0x33: printf("MOTOR Speed Up \n");
				   ioctl(dev, MOTOR_SpeedUp, 0);
				   break;
			case 0x34: printf("MOTOR Speed Down \n");
				   ioctl(dev, MOTOR_SpeedDown, 0);
				   break;
			case 0x35: printf("MOTOR Stop \n");
				   ioctl(dev, MOTOR_STOP, 0);
  				   break;
			default:   printf("Unknow command... \n");
				   break;
        	} 
	}
	printf("Exit Program\n");
	ioctl(dev, MOTOR_STOP, 0);
	close(dev);
}
      
