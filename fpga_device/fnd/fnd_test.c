/*
 * XHYPER255_TKU3
 * fnd test.c
 * 2004-07-01   <newboder@hybus.net>
 *
 * ]# ./fnd_test 12345678 
 */

#include	<stdio.h>
#include	<fcntl.h>

#define fnd_dev	"/dev/fnd"

#define		MAXFND	8

/*
 *	bit# pos
 *
 *	  --0--
 *	5|     |1
 *	  --6--
 *	4|     |2
 *	  --3--  o7
 */
unsigned char asc_to_fnd(int n){
	unsigned char c;

		switch (n) {
			/* 여러가지 문자를 추가할수 있다 */
			case  0: c = 0x3f; break;
			case  1: c = 0x06; break;
			case  2: c = 0x5b; break;
			case  3: c = 0x4f; break;
			case  4: c = 0x66; break;
			case  5: c = 0x6d; break;
			case  6: c = 0x7d; break;
			case  7: c = 0x07; break;
			case  8: c = 0x7f; break;
			case  9: c = 0x67; break;
			default: c = 0x00; break;
		}
	return c;
}

main(int ac, char *av[])
{
	int dev, i, n, count;
	char temp;
	unsigned long fndValue1 = 0, fndValue2 = 0, fndValue3 = 0, fndValue4 = 0, fndValue5 = 0, fndValue6 = 0, fndValue7 = 0, fndValue8 = 0;
	int fndValue[MAXFND] = {0};
	
	//char s[MAXFND] = {0, 0, 0, 0, 0, 0, 0, 0};
	//char t[MAXFND] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
	char s[MAXFND] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char t[MAXFND] = {1, 2, 3, 4, 5, 6, 7, 8, 0, 0};
	unsigned char buf[MAXFND+1];

        dev = open("/dev/fnd", O_WRONLY);
        if(dev < 0)
	{
        	printf("Application : FND driver open fails!\n");
                return -1;
        }

	printf("\n");
	printf("     [7Segment Display]    \n");
        printf("---------------------------\n");
        printf("     Input the SegCode!    \n");
	printf("     MAX = 8		   \n");
        printf("     q -> Quit             \n");
        printf("---------------------------\n");

	while(1)
	{
		memset(s, 0, MAXFND+2);
		memset(buf, 0, sizeof(buf));

		fgets(s, MAXFND+2, stdin);
		s[MAXFND+1]=0;
		s[MAXFND+2]=0;

		for(i=0; i < MAXFND; i++)
		{
			if(s[i] < 0x30 || s[i] > 0x39)
			{
				if(s[i] != 0x71)
					s[i] = 0xF;
			}
		}
		
		if(s[0] == 'q' || s[1] == 'q' || s[2] == 'q' || s[3] == 'q' || s[4] == 'q' || s[5] == 'q' || s[6] == 'q' || s[7] == 'q')
			break;
		
		
		for(i=0; i< MAXFND; i++)
		{
			fndValue[i] = s[i]-'0';
		}

		for(i=0; i< MAXFND; i++)
		{
			buf[i]= asc_to_fnd(fndValue[i]);
		}
		write(dev, buf,MAXFND);
		

		/*
		for (n = 0 ; n <= 4; n++)
		{
			for( count = 0 ; count < MAXFND-2; count++){
			buf[count]= asc_to_fnd(n);
			}
			write(dev, buf,MAXFND);
			usleep(500000);
		}
		*/
		
	
	}
}
/*	EOF	*/
