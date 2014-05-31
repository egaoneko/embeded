/*
 * X-HYPER270-TKU IEB Rev
 * Character LCD Control Program
 * 2006-08-16  <kjlee@hybus.net>
 */

#include    <stdio.h>
#include    <fcntl.h>

static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

#define     MAXCHR  32

int main()
{
	int n;
	char str[MAXCHR];
	char buf[MAXCHR];
	lcdFd = open(lcdDev, O_RDWR);
	if (lcdFd < 0){
		fprintf(stderr, "Cannot open CLCD (%d)", lcdFd);
		exit(2);
	}

	printf("\n");
	printf("     [Character LCD TEST]     \n");
	printf("------------------------------\n");
	printf("     Input string! (MAX = 32) \n");
	printf("     [Ctrl + C] -> Quit	      \n");
	printf("------------------------------\n");
	
	while(1)
	{
		memset(str, 0, sizeof(str));
        	memset(buf, 0, sizeof(buf));
		fgets(str, MAXCHR, stdin);

		if(str[0] == 'q' && str[1] == 'u' && str[2] == 'i' && str[3] == 't')
			break;
	
		n = strlen(str);
	        if (n > MAXCHR)
        	    n = MAXCHR;
        	str[n-1]='\0';
		memcpy(buf, str, n);
		//write(lcdFd, buf, MAXCHR, 0);
		write(lcdFd, buf, MAXCHR);
	}
	printf("Exit Program\n");
	close(lcdFd);
	return 0;
}

