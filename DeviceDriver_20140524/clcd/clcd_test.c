/* =================================================
 * Program ID : clcd_test.c
 * Author     : Gwibong, LEE
 * Create Date: 2014-05-24
 * Compile Row: make - Reference Makefile
 * Description: Character LCD control Program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include    <stdio.h>
#include    <fcntl.h>

static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

#define     MAXCHR  32

main(int argc, char *argv[])
{
	int n;
	char buf[MAXCHR];

	lcdFd = open( lcdDev, O_RDWR);
	if (lcdFd < 0) {
		fprintf(stderr, "cannot open LCD (%d)", lcdFd);
		exit(2);
	}

//	ioctl(lcdFd, 1, 0);
//	sleep(1);

	memset(buf, 0, sizeof(buf));
	if (argc > 1) {
		n = strlen(argv[1]);
		if (n > MAXCHR)
			n = MAXCHR; //plus the newline
		memcpy(buf, argv[1], n);
	}

	write(lcdFd, buf, MAXCHR);
}

/* EOF */
