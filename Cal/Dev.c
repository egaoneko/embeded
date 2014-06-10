/* =================================================
 * Program ID : Dev.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: Device Driver Application Function
 * =================================================
 */

#include <stdio.h>
#include <fcntl.h>
#include "Dev.h"

unsigned char dot_col[5] = {0};

/* KEY_FUN 
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
} */

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
	case 18: dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x36; break;
	case 29: dot_col[0] = 0x7F; dot_col[1] = 0x20; dot_col[2] = 0x10; dot_col[3] = 0x20; dot_col[4] = 0x7F; break;
	case 28: dot_col[0] = 0x7F; dot_col[1] = 0x01; dot_col[2] = 0x01; dot_col[3] = 0x01; dot_col[4] = 0x01; break;
	case 21: dot_col[0] = 0x7F; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x49; break;
	case -8: dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x3E; dot_col[3] = 0x41; dot_col[4] = 0x00; break;
	case -7: dot_col[0] = 0x00; dot_col[1] = 0x41; dot_col[2] = 0x3E; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
	case 37: dot_col[0] = 0x7C; dot_col[1] = 0x02; dot_col[2] = 0x01; dot_col[3] = 0x02; dot_col[4] = 0x7C; break;
	case 20: dot_col[0] = 0x7F; dot_col[1] = 0x41; dot_col[2] = 0x41; dot_col[3] = 0x22; dot_col[4] = 0x1C; break;
	case 19: dot_col[0] = 0x1C; dot_col[1] = 0x22; dot_col[2] = 0x41; dot_col[3] = 0x41; dot_col[4] = 0x22; break;
	case 35: dot_col[0] = 0x32; dot_col[1] = 0x49; dot_col[2] = 0x49; dot_col[3] = 0x49; dot_col[4] = 0x26; break;
	defualt: dot_col[0] = 0x00; dot_col[1] = 0x00; dot_col[2] = 0x00; dot_col[3] = 0x00; dot_col[4] = 0x00; break;
	}
}

/* Error Handling */
void error_handling(char *msg, int fd)
{
	printf("Cannot open %s (%d)", msg, fd);
	exit(-1);
}

/* Spray Display */
void spr_dis(char ch, int lcdFd, int dotFd, char *s, char* lcd, int* idx, char* before) {
	int fnd_end=MAXFND-1;
	int ch_to_int = ch - '0';
	char data[32];
	
	if(ch!=0x3D &&  ch!=0x42 &&  ch!=0x4C &&  ch!=0x45 && ch!=0x44 && ch!=0x55 && ch!=0x53 && ch!=0x43){
		lcd[*idx]=ch;
		lcd[*idx+1]='\0';
		strcpy(data, before);
		strcat(data, "\n");
		strcat(data, lcd);
		write(lcdFd, data, MAXCHR);
	}
	else if(ch==0x3D) {
		lcd[*idx]='\0';
	}
	else if(ch==0x42) {
		strcpy(data, before);
		strcat(data, "\n");
		strcat(data, lcd);
		write(lcdFd, data, MAXCHR);
	}
	else if(ch==0x4C || ch==0x45 || ch==0x44 || ch==0x55 || ch==0x53 || ch==0x43) {
	}
	asc_to_dot(ch_to_int);
	write(dotFd, dot_col, DOT_COL);
	s[fnd_end] = ch;
}

void spr_lcd(int lcdFd, char* exp, char* res) {
	char data[32];
	memset(data, 0, sizeof(data));
	strcpy(data, exp);
	strcat(data, "\n");
	strcat(data, res);
	write(lcdFd, data, MAXCHR);
}

/* LED Write */
void led_start(int dev, int num){
  
	unsigned char data;

	switch(num){
		/* Start Success */
		case 1:
			data  =0x7f;
			write(dev, &data, sizeof(unsigned char));
			break;
		
		/* Syntax Error */
		case 2:
			data  = 0xbf;
			write(dev, &data, sizeof(unsigned char));
			break;

		/* Calulate Success */
		case 3:
			data  = 0xdf;
			write(dev, &data, sizeof(unsigned char));
			break;
		case 4:
			data  =0xef;
			write(dev, &data, sizeof(unsigned char));
			break;

		/* Exit Success */
		case 5:
			data  = 0xf7; 
			write(dev, &data, sizeof(unsigned char));
			break;
		case 6:
			data  =0xfb;
			write(dev, &data, sizeof(unsigned char));
			break;
		case 7:
			data  = 0xfd; 
			write(dev, &data, sizeof(unsigned char));
			break;
		case 8:
			data  = 0xfe;
			write(dev, &data, sizeof(unsigned char));
			break;
		case 0:
			break;
	}

 }
