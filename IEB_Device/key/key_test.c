/*
 * X-HYPER270-TKU IEB Rev
 * Key Matrix Control Program
 * 2006-08-16  <kjlee@hybus.net>
 */

#include <stdio.h>
#include <fcntl.h>

#include <asm/ioctls.h>

#define K_NUM0  13
#define K_NUM1  9
#define K_NUM2  10
#define K_NUM3  11
#define K_NUM4  5
#define K_NUM5  6
#define K_NUM6  7
#define K_NUM7  1
#define K_NUM8  2
#define K_NUM9  3
#define K_DOT   14
#define K_ADD   4
#define K_SUB   8
#define K_MUL   12
#define K_DIV   16
#define K_FUN   15

#define dbg(x...)       printf(x) 

static char keyDev[] = "/dev/key";
static int  keyFd = (-1);

unsigned char key_get(int tmo)
{   
    unsigned char b;

    if (tmo){ 
        if (tmo < 0)
            tmo = ~tmo * 1000;
        else
            tmo *= 1000000;
        while (tmo > 0){
            usleep(400000);
            ioctl(keyFd, FIONREAD, &b);
            if (b) return(b);
            tmo -= 10000;
        }
        return(-1);
    }
    else {
        read(keyFd, &b, sizeof(b));
        return(b);
    }
}

int main()
{
	unsigned char c;

	if((keyFd = open(keyDev, O_RDONLY )) < 0){         // KEY open
		perror("Cannot open /dev/key!");
		exit(-1);
	}

	printf("\n");
	printf("--------------------------\n");
	printf("     [Key Matrix TEST]    \n");
	printf("     Ctrl + C -> Quit	  \n");
	printf("--------------------------\n");
	
	while(1){
		c = key_get(10);
		switch (c){
			case K_NUM0:  dbg("KEY_NUM0\n"); break;
			case K_NUM1:  dbg("KEY_NUM1\n"); break;
			case K_NUM2:  dbg("KEY_NUM2\n"); break;
			case K_NUM3:  dbg("KEY_NUM3\n"); break;
			case K_NUM4:  dbg("KEY_NUM4\n"); break;
			case K_NUM5:  dbg("KEY_NUM5\n"); break;
			case K_NUM6:  dbg("KEY_NUM6\n"); break;
			case K_NUM7:  dbg("KEY_NUM7\n"); break;
			case K_NUM8:  dbg("KEY_NUM8\n"); break;
			case K_NUM9:  dbg("KEY_NUM9\n"); break;
			case K_DOT:  dbg("KEY_DOT\n"); break;
			case K_ADD:  dbg("KEY_ADD\n"); break;	
			case K_SUB:  dbg("KEY_SUB\n"); break;
			case K_MUL:  dbg("KEY_MUL\n"); break;
			case K_DIV:  dbg("KEY_DIV\n"); break;
			case K_FUN:  dbg("KEY_FUN\n"); break;
			default: /* timeout */ break;
	        }
        //sleep(1);
	}
	printf("Exit Program\n");
	close(keyFd);
	return 0;
}

