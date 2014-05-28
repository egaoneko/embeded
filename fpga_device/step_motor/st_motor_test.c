/*
 * XHYPER255_TKU3
 * step motor test.c
 * 2004-07-01   <newboder@hybus.net>
 * 
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
	int key;
	printf("\n\n");
	printf("********** MOTOR menu **********\n");
	printf("* 1.     MOTOR Forward         *\n");
	printf("* 2.     MOTOR Reverse         *\n");
	printf("* 3.     MOTOR Speed Up        *\n");
	printf("* 4.     MOTOR Speed Down      *\n");
	printf("* 5.     MOTOR STOP            *\n");
	printf("* 6.                           *\n");
	printf("* 7.                           *\n");
	printf("* 8.                           *\n");
	printf("* 9.                           *\n");
	printf("* 0.     Exit Program          *\n");
	printf("********************************\n");
	printf("\n\n");

	printf("select the command number : ");
	scanf("%d",&key);
	return key;
}

main(int ac, char *av[]){
	int key, dev;

	dev = open(stmotor_dev, O_RDWR );
    	if ( dev < 0) {
        fprintf(stderr, "cannot open ST_MOTOR (%d)", dev);
        exit(2);
    }

	while((key = main_menu()) != 0){
		switch(key){
			case 1: printf("\t MOTOR Forward \n");
				   ioctl(dev, MOTOR_Forward, 0);
				   break;
			case 2: printf("\t MOTOR Reverse \n");
				   ioctl(dev, MOTOR_Reverse, 0);
				   break;
			case 3: printf("\t MOTOR Speed Up \n");
				   ioctl(dev, MOTOR_SpeedUp, 0);
				   break;
			case 4: printf("\t MOTOR Speed Down \n");
				   ioctl(dev, MOTOR_SpeedDown, 0);
				   break;
			case 5: printf("\t MOTOR Stop \n");
				   ioctl(dev, MOTOR_STOP, 0);
					  break;
			default:  printf("\t Unknow command... \n");
					  break;
        } 
  	}   
	ioctl(dev,5,0);  
}      

/* EOF */
