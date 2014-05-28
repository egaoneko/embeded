/*
 * X-HYPER270-TKU IEB Board Rev
 * DC Motor Control Program
 * 2006-08-16   <kjlee@hybus.net>
 */

#include <stdio.h>
#include <fcntl.h>

#define _IOCTL_LEFT_FORWARD     1    
#define _IOCTL_LEFT_REVERSE     2
#define _IOCTL_LEFT_STOP        3

#define _IOCTL_RIGHT_FORWORD    4
#define _IOCTL_RIGHT_REVERSE    5
#define _IOCTL_RIGHT_STOP       6

int main_menu(void);
static unsigned short flag;
int main()
{
	int fd;
	int key;

	fd = open("/dev/dc_motor", O_RDWR );

	if (fd <0)
	{
		perror("/dev/dc_motor");
		exit(-1);
	}
	else 
	    printf("MOTOR is detected\n");

	while((key = main_menu()) != 0x30)
	{
		switch(key)
		{
			case 0x31:
				ioctl(fd, 1, flag);
				break;
		        case 0x32:
				ioctl(fd, 2, flag);
                		break;
		        case 0x33:
				ioctl(fd, 3, flag);
				break;
		        case 0x34:
				ioctl(fd, 4, flag);
                		break;
		        case 0x35:
				ioctl(fd, 5, flag);
		                break;
		        case 0x36:
				ioctl(fd, 6, flag);
                		break;
			default:
				printf("Unknow command\n");
		}  

	}
	printf("Exit Program\n");
	close(fd);
}

int main_menu(void)
{
        char key;
        printf("\n\n");
        printf("******** MOTOR MENU ********\n");
        printf("* 1. MOTOR LEFT Forward    *\n");
        printf("* 2. MOTOR LEFT Reverse    *\n");
        printf("* 3. MOTOR LEFT Stop       *\n");
        printf("* 4. MOTOR RIGHT Forward   *\n");
        printf("* 5. MOTOR RIGHT Reverse   *\n");
        printf("* 6. MOTOR RIGHT Stop      *\n");
        printf("* 0. Exit Program          *\n");
        printf("****************************\n");
        printf("\n\n");

	printf("Select the command number : ");
	key = getc(stdin);
	getc(stdin);
	return key;
}

