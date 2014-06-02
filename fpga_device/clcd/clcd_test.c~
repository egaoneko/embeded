/*
 * XHYPER255_TKU3
 * lcd test.c
 * 2004-07-01   <newboder@hybus.net>
 * 
 */

#include    <stdio.h>
#include    <fcntl.h>

ssize_t writeup (struct file *filp, const char *buf, size_t count){};
ssize_t writedn (struct file *filp, const char *buf, size_t count){};

static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

#define     MAXCHR  32

main(int ac, char *av[])
{
	int n;
	char str[MAXCHR];
	char buf[MAXCHR];
	char str2[MAXCHR]="0123456789      0123456789      ";
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
		
		printf("%s\n", buf);
		write(lcdFd, buf, MAXCHR);
		write(lcdFd, str2, MAXCHR);
	}
	printf("Exit Program\n");
	close(lcdFd);
	return 0;

}

/* EOF */
