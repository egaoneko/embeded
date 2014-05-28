/*
 * XHYPER255_TKU3
 * lcd test.c
 * 2004-07-01   <newboder@hybus.net>
 * 
 */

#include    <stdio.h>
#include    <fcntl.h>

static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);

#define     MAXCHR  32

main(int ac, char *av[])
{
    int n;
    char        buf[MAXCHR];

    lcdFd = open( lcdDev, O_RDWR);
    if (lcdFd < 0) {
        fprintf(stderr, "cannot open LCD (%d)", lcdFd);
        exit(2);
    }

	ioctl(lcdFd, 0, 0);
//	sleep(1);
	
    memset(buf, 0, sizeof(buf));
    if (ac > 1) {
        n = strlen(av[1]);

        if (n > MAXCHR)
            n = MAXCHR; //plus the newline
		memcpy(buf, av[1], n);
    }
	
	write(lcdFd, buf, MAXCHR);

}

/* EOF */
