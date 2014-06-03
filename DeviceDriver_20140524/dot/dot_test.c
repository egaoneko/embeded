/* =================================================
 * Program ID : dot_test.c
 * Author     : Gwibong, LEE
 * Create Date: 2014-05-24
 * Compile Row: make - Reference Makefile
 * Description: DOT 8bit Device test program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include    <stdio.h>
#include    <fcntl.h>

#define dot_dev 	"/dev/dot"
#define DOT_COL		5
unsigned char dot_col[5] = {0};

unsigned char asc_to_dot(int asc)
{
	switch(asc) {
		case 0 :
			dot_col[0] = 0x7F;
			dot_col[1] = 0x41;
			dot_col[2] = 0x41;
			dot_col[3] = 0x41;
			dot_col[4] = 0x7F;
			break;
		case 1 :
			dot_col[0] = 0x00;
			dot_col[1] = 0x00;
			dot_col[2] = 0x7F;
			dot_col[3] = 0x00;
			dot_col[4] = 0x00;
			break;
		case 2 :
			dot_col[0] = 0x4F;
			dot_col[1] = 0x49;
			dot_col[2] = 0x49;
			dot_col[3] = 0x49;
			dot_col[4] = 0x79;
			break;
		case 3 :
			dot_col[0] = 0x49;
			dot_col[1] = 0x49;
			dot_col[2] = 0x49;
			dot_col[3] = 0x49;
			dot_col[4] = 0x7F;
			break;
		case 4 :
			dot_col[0] = 0x78;
			dot_col[1] = 0x08;
			dot_col[2] = 0x7F;
			dot_col[3] = 0x08;
			dot_col[4] = 0x08;
			break;
		case 5 :
			dot_col[0] = 0x79;
			dot_col[1] = 0x49;
			dot_col[2] = 0x49;
			dot_col[3] = 0x49;
			dot_col[4] = 0x4F;
			break;
		case 6 :
			dot_col[0] = 0x7F;
			dot_col[1] = 0x49;
			dot_col[2] = 0x49;
			dot_col[3] = 0x49;
			dot_col[4] = 0x4F;
			break;
		case 7 :
			dot_col[0] = 0x40;
			dot_col[1] = 0x40;
			dot_col[2] = 0x40;
			dot_col[3] = 0x40;
			dot_col[4] = 0x7F;
			break;
		case 8 :
			dot_col[0] = 0x7F;
			dot_col[1] = 0x49;
			dot_col[2] = 0x49;
			dot_col[3] = 0x49;
			dot_col[4] = 0x7F;
			break;
		case 9 :
			dot_col[0] = 0x78;
			dot_col[1] = 0x48;
			dot_col[2] = 0x48;
			dot_col[3] = 0x48;
			dot_col[4] = 0x7F;
			break;
		defualt : break;
	}
}

int main()
{
	int dev, count;

	dev = open(dot_dev, O_RDWR );
	if ( dev < 0 ) {
		fprintf(stderr, "cannot open DOT (%d)", dev);
		exit(2);
	}

	memset(dot_col, 0, sizeof(dot_col));

	for (count =0 ; count <= 9; count++) {
		asc_to_dot(count);
		printf( " dot col data %x %x %x %x %X \n",dot_col[0],  dot_col[1], dot_col[2], dot_col[3], dot_col[4]);
		write(dev, dot_col, DOT_COL);
		sleep(1);
	}

	return 0;
}

/* EOF */
