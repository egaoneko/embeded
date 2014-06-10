/* =================================================
 * Program ID : dot_test.c
 * Author     : SUM Project
 * Create Date: 2014-06-09
 * Compile Row: make - Reference Makefile
 * Description: Dot control test program
 *            : with XHYPER270-TKU
 * =================================================
 */
#include    <stdio.h>
#include    <fcntl.h>

#define dot_dev 	"/dev/dot"
#define DOT_COL		5
unsigned char dot_col[5] = {0};


unsigned char asc_to_dot(int asc){
		switch( asc){/* depenging on the value of asc, print the mapping character to dot matrix*/
			case 0 :  dot_col[0] = 0x7F; dot_col[1] = 0x41; dot_col[2] = 0x41; dot_col[3] = 0x41; dot_col[4] = 0x7F; break;
			case 1 :  dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x7F; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
			case 2 :  dot_col[0] = 0x4F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x79; break;
			case 3 :  dot_col[0] = 0x49; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x7F; break;
			case 4 :  dot_col[0] = 0x78; dot_col[1] = 0x08; dot_col[2] = 0x08; dot_col[3] = 0x7F; dot_col[4] = 0x08; break;
			case 5 :  dot_col[0] = 0x79; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x4F; break;
			case 6 :  dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x4F; break;
			case 7 :  dot_col[0] = 0x40; dot_col[1] = 0x40; dot_col[2] = 0x40; dot_col[3] = 0x40; dot_col[4] = 0x7F; break;
			case 8 :  dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x7F; break;
			case 9 :  dot_col[0] = 0x78; dot_col[1] = 0x48; dot_col[2] = 0x48; dot_col[3] = 0x48; dot_col[4] = 0x7F; break;
			case 10 : dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x08; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
			case 11 : dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x3E; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
			case 12 : dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x08; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
			case 13 : dot_col[0] = 0x22; dot_col[1] = 0x14; dot_col[2] = 0x08; dot_col[3] = 0x14; dot_col[4] = 0x22; break;
			case 14 : dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x2A; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
			case 15 : dot_col[0] = 0x7F; dot_col[1] = 0x48; dot_col[2] = 0x48; dot_col[3] = 0x48; dot_col[4] = 0x40; break;
	
			defualt : break;
	}	
}

int main()
{
	int dev, count;
	unsigned long dotValue = 0;
	char ch;
	
	dev = open(dot_dev, O_RDWR );
   	if(dev < 0){
       		fprintf(stderr, "cannot open DOT (%d)", dev);
        	exit(2);
    	}

	printf("\n");
	printf("-------------------------------\n");
	printf("Input the value (Range : 0 ~ 9)\n");
	printf("q -> Quit		       \n");
	printf("-------------------------------\n");

	while(1)
	{
		memset(dot_col, 0, sizeof(dot_col));
		ch = getc(stdin);
		getc(stdin);

		if(ch == 'q')
			break;
		/*
		else if(ch < 0x30 || ch > 0x39)
			printf("Unknown value...\n");
		*/
		printf("%c\n",ch);
		switch(ch) { /* append the extra characters*/
			case '.' :
				ch=0x3A;
				break;
			case '+' :
				ch=0x3B;
				break;
			case '-' :
				ch=0x3C;
				break;
			case '*' :
				ch=0x3D;
				break;	
			case '/' :
				ch=0x3E;
				break;	
			case 'F' :
				ch=0x3F;
				break;
		}
		printf("%d\n",ch-'0');	
		asc_to_dot(ch-'0');/*remove the end symbol from a character*/
		write(dev, dot_col, DOT_COL);
		
	}
	printf("Exit Program\n");	
	
	return 0;
}

/* EOF */
