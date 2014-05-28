#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <string.h>

#include "motor.h"

#define _IOCTL_LEFT_FORWARD     1    
#define _IOCTL_LEFT_REVERSE     2
#define _IOCTL_LEFT_STOP        3

#define _IOCTL_RIGHT_FORWORD    4
#define _IOCTL_RIGHT_REVERSE    5
#define _IOCTL_RIGHT_STOP       6



static unsigned short flag;

  int main()
  {
    int fd;
    int key;

    fd = open("/dev/dc_motor", O_RDWR );

    if (fd <0) {perror("/dev/dc_motor"); exit(-1); }
    else 
	    printf("MOTOR detected \n");

    while((key = main_menu()) != 0){
	switch(key){
	   case 1:
		ioctl(fd, 1, flag);
		break;
           case 2:
		ioctl(fd, 2, flag);
                break;
           case 3:
		ioctl(fd, 3, flag);
		break;
           case 4:
		ioctl(fd, 4, flag);
                break;
           case 5:
		ioctl(fd, 5, flag);
                break;
           case 6:
		ioctl(fd, 6, flag);
                break;
           case 7:
		ioctl(fd, 7, flag);
                break;
           case 8:
		ioctl(fd, 8, flag);
                break;
           case 9:
		ioctl(fd, 9, flag);
		break;
           case 0:
                printf("\n\t\t\t Exit Program \n");
		break;
	    default: printf ("unknow command\n");
		break;
        }  // end of switch

  }        // end of while
}

int main_menu(void)
{
        int key;
        printf("\n\n");
        printf("********** MOTOR menu **********\n");
        printf("* 1.     MOTOR LEFT Forward    *\n");
        printf("* 2.     MOTOR LEFT Reverse    *\n");
        printf("* 3.     MOTOR LEFT Stop       *\n");
        printf("* 4.     MOTOR RIGHT Forward   *\n");
        printf("* 5.     MOTOR RIGHT Reverse   *\n");
        printf("* 6.     MOTOR RIGHT Stop      *\n");
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
