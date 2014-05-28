/*
 * X-HYPER270-TKU IEB Rev
 * DIP SW Control Program
 * 2006-08-21  <kjlee@hybus.net>
 */

#include <stdio.h>
#include <fcntl.h>

static char dipDev[] = "/dev/dip";
static char ledDev[] = "/dev/led";
static int  dipFd = (-1);
static int  ledFd = (-1);

int main()
{
	unsigned char data, buf, ch;

	if((dipFd = open(dipDev, O_RDONLY )) < 0)
	{	
                fprintf(stderr, "Cannot open DIP SW Device (%d)", dipDev);
                exit(-1);
        }

	ledFd = open(ledDev, O_RDWR);
        if (ledFd < 0){
                fprintf(stderr, "Cannot open LED Device (%d)", ledDev);
                exit(2);
        }


	printf("\n");
	printf("---------------------\n");
	printf("    DIP SW to BLED   \n");
	printf("    s -> Get Data    \n");
	printf("    q -> Quit	     \n");
	printf("---------------------\n");

	while(1)
	{
		ch = getc(stdin);
		getc(stdin);

		if(ch == 'q')
			break;

		if(ch == 's')
		{
			read(dipFd, &data, sizeof(data));
			buf = ~data;
			write(ledFd, &buf, sizeof(data));
		}
		else
			printf("Unknown command...\n");
	}		

	printf("Exit Program\n");
	close(dipFd);
	close(ledFd);
	return 0;

}

