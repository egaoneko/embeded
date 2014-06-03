/* =================================================
 * Program ID : key_test.c
 * Author     : Gwibong, LEE
 * Create Date: 2014-05-24
 * Compile Row: make - Reference Makefile
 * Description: Key Buton control test program
 *            : with XHYPER270-TKU
 * =================================================
 */

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <string.h>
#include <asm/ioctls.h>

#define  KEY_NUM01    1
#define  KEY_NUM02    2
#define  KEY_NUM03    3
#define  KEY_NUM04    4
#define  KEY_NUM05    5
#define  KEY_NUM06    6
#define  KEY_NUM07    7
#define  KEY_NUM08    8
#define  KEY_NUM09    9
#define  KEY_NUM10   10
#define  KEY_NUM11   11
#define  KEY_NUM12   12
#define  KEY_NUM13   13
#define  KEY_NUM14   14
#define  KEY_NUM15   15
#define  KEY_NUM16   16

#define dbg(x...)    printf(x) 

static char keyDev[] = "/dev/key";
static int  keyFd = (-1);

unsigned char key_get(int tmo)
{
	unsigned char b;

	if (tmo) { 
		if (tmo < 0)
			tmo = ~tmo * 1000;
		else
			tmo *= 1000000;
		while (tmo > 0) {
			usleep(10000);
			ioctl(keyFd, FIONREAD, &b);
			if (b) return(b);
			tmo -= 10000;
		}
		return(-1); /* timeout */
	}
	else {
		read(keyFd, &b, sizeof(b));
		return(b);
	}
}

int main()
{
	unsigned char c;

	if((keyFd = open( keyDev, O_RDONLY )) < 0){         // KEY open
		perror("open faile /dev/key");
		exit(-1);
	}

	while(1){
		c = key_get(10);
		switch (c) {
			case KEY_NUM01:  dbg("KEY_NUM01\n"); break;
			case KEY_NUM02:  dbg("KEY_NUM02\n"); break;
			case KEY_NUM03:  dbg("KEY_NUM03\n"); break;
			case KEY_NUM04:  dbg("KEY_NUM04\n"); break;
			case KEY_NUM05:  dbg("KEY_NUM05\n"); break;
			case KEY_NUM06:  dbg("KEY_NUM06\n"); break;
			case KEY_NUM07:  dbg("KEY_NUM07\n"); break;
			case KEY_NUM08:  dbg("KEY_NUM08\n"); break;
			case KEY_NUM09:  dbg("KEY_NUM09\n"); break;
			case KEY_NUM10:  dbg("KEY_NUM10\n"); break;
			case KEY_NUM11:  dbg("KEY_NUM11\n"); break;
			case KEY_NUM12:  dbg("KEY_NUM12\n"); break;
			case KEY_NUM13:  dbg("KEY_NUM13\n"); break;
			case KEY_NUM14:  dbg("KEY_NUM14\n"); break;
			case KEY_NUM15:  dbg("KEY_NUM15\n"); break;
			case KEY_NUM16:  dbg("KEY_NUM16\n"); break;
			default: /* timeout */ break;
		}
	}
	return 0;
}

/* EOF */
