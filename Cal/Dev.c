#include <stdio.h>
#include <fcntl.h>
#include "Dev.h"

unsigned char dot_col[5] = {0};

/* KEY_FUN */
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

/* FND_FUN */
unsigned char asc_to_fnd(int n){
	unsigned char c;

	switch (n) {
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
	case -2: c = 0x80; break;
	default: c = 0x40; break;
	}
	return c;
}
void fnd_clear(char* s, char* fnd_buf)
{
	memset(s, 0, MAXFND + 2);
	memset(fnd_buf, 0, sizeof(fnd_buf));
}

/* DOT_FUN */
unsigned char asc_to_dot(int asc){
	switch (asc){
	case 0:  dot_col[0] = 0x7F; dot_col[1] = 0x41; dot_col[2] = 0x41; dot_col[3] = 0x41; dot_col[4] = 0x7F; break;
	case 1:  dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x7F; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
	case 2:  dot_col[0] = 0x4F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x79; break;
	case 3:  dot_col[0] = 0x49; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x7F; break;
	case 4:  dot_col[0] = 0x78; dot_col[1] = 0x08; dot_col[2] = 0x08; dot_col[3] = 0x7F; dot_col[4] = 0x08; break;
	case 5:  dot_col[0] = 0x79; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x4F; break;
	case 6:  dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x4F; break;
	case 7:  dot_col[0] = 0x40; dot_col[1] = 0x40; dot_col[2] = 0x40; dot_col[3] = 0x40; dot_col[4] = 0x7F; break;
	case 8:  dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x7F; break;
	case 9:  dot_col[0] = 0x78; dot_col[1] = 0x48; dot_col[2] = 0x48; dot_col[3] = 0x48; dot_col[4] = 0x7F; break;
	case -2: dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x08; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
	case -5: dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x3E; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
	case -3: dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x08; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
	case -6: dot_col[0] = 0x22; dot_col[1] = 0x14; dot_col[2] = 0x08; dot_col[3] = 0x14; dot_col[4] = 0x22; break;
	case -1: dot_col[0] = 0x08; dot_col[1] = 0x08; dot_col[2] = 0x2A; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
	case 13: dot_col[0] = 0x00; dot_col[1] = 0x14; dot_col[2] = 0x14; dot_col[3] = 0x14; dot_col[4] = 0x00; break;
	case 22: dot_col[0] = 0x7F; dot_col[1] = 0x48; dot_col[2] = 0x48; dot_col[3] = 0x48; dot_col[4] = 0x40; break;

	defualt: break;
	}
}

/* Error Handling */
void error_handling(char *msg, int fd)
{
	printf("Cannot open %s (%d)", msg, fd);
	exit(-1);
}

/* Spray Display */
void spr_dis(char ch, int lcdFd, int dotFd, char *s, char* lcd, int* idx) {
	int fnd_end=MAXFND-1;
	int ch_to_int = ch - '0';
	
	if(ch!=0x3D){
		lcd[*idx]=ch;
		lcd[*idx+1]='\0';
		write(lcdFd, lcd, MAXCHR);
	}
	else if(ch==0x3D) {
		lcd[*idx]='\0';
	}
	asc_to_dot(ch_to_int);
	write(dotFd, dot_col, DOT_COL);
	s[fnd_end] = ch;
}

void spr_lcd(int lcdFd, char* exp, char* res) {
	char data[32];
	memset(data, 0, sizeof(data));
	strcpy(data, exp);
	strcat(data, res);
	write(lcdFd, data, MAXCHR);
}


