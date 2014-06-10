/* =================================================
 * Program ID : clcd.c
 * Author     : SUM Project
 * Create Date: 2014-06-09
 * Compile Row: make - Reference Makefile
 * Description: CLCD control test program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include    <stdio.h>
#include    <fcntl.h>

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
	        if (n > MAXCHR) /* Don't make the length of a string over buffer size*/
        	    n = MAXCHR;
        	str[n-1]='\0'; /* insert the end token of string*/ 
		memcpy(buf, str, n);
		
		printf("%s\n", buf);
		write(lcdFd, buf, MAXCHR);
	}
	printf("Exit Program\n");
	close(lcdFd);
	return 0;

}

/* EOF */
