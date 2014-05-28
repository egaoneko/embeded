#include <stdio.h>
#include <fcntl.h>
#include "dev.h"

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
	case 4:  dot_col[0] = 0x78; dot_col[1] = 0x08; dot_col[2] = 0x7F; dot_col[3] = 0x08; dot_col[4] = 0x08; break;
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
void spr_dis(char ch, int lcdFd, int dotFd, char *s, char* lcd) {
	int fnd_end=MAXFND-1;
	int ch_to_int = ch - '0';
	lcd[0]=ch;
	lcd[1]='\0';
	write(lcdFd, lcd, MAXCHR);
	asc_to_dot(ch_to_int);
	write(dotFd, dot_col, DOT_COL);
	s[fnd_end] = ch;
}

/* Sample */
int main(int ac, char *av[])
{
	/* Init */
	int ch_to_int;

	/* KEY Init */
	unsigned char c;

	/* DOT Init */
	char ch;

	/* CLCD Init */
	char str[MAXCHR];
	char buf[MAXCHR];

	/* FND Init */
	int i, n, count;
	char temp;
	char s[MAXFND] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char fnd_buf[MAXFND + 1];
	int fndValue[MAXFND] = { 0 };

	if ((keyFd = open(keyDev, O_RDONLY)) < 0){
		error_handling("KEY", keyFd);
	}
	if ((lcdFd = open(lcdDev, O_RDWR)) < 0){
		error_handling("CLCD", lcdFd);
	}
	if ((dotFd = open(dotDev, O_RDWR)) < 0){
		error_handling("DOT", dotFd);
	}
	if ((fndFd = open(fndDev, O_WRONLY)) < 0){
		error_handling("FND", fndFd);
	}

	printf("\n");
	printf("--------------------------\n");
	printf("     [Multi TEST]    \n");
	printf("     Ctrl + C -> Quit	  \n");
	printf("--------------------------\n");

	memset(s, 0, MAXFND + 2);
	memset(fnd_buf, 0, sizeof(fnd_buf));

	while (1){
		memset(str, 0, sizeof(str));
		memset(buf, 0, sizeof(buf));
		
		c = key_get(10);

		switch (c){
		case K_NUM0:		
			spr_dis(0x30, lcdFd, dotFd, s, str);
			break;
		case K_NUM1:
			spr_dis(0x31, lcdFd, dotFd, s, str);
			break;
		case K_NUM2:
			spr_dis(0x32, lcdFd, dotFd, s, str);
			break;
		case K_NUM3:
			spr_dis(0x33, lcdFd, dotFd, s, str);
			break;
		case K_NUM4:
			spr_dis(0x34, lcdFd, dotFd, s, str);
			break;
		case K_NUM5:
			spr_dis(0x35, lcdFd, dotFd, s, str);
			break;
		case K_NUM6:
			spr_dis(0x36, lcdFd, dotFd, s, str);
			break;
		case K_NUM7:
			spr_dis(0x37, lcdFd, dotFd, s, str);
			break;
		case K_NUM8:
			spr_dis(0x38, lcdFd, dotFd, s, str);
			break;
		case K_NUM9:
			spr_dis(0x39, lcdFd, dotFd, s, str);
			break;
		case K_DOT:
			spr_dis(0x2E, lcdFd, dotFd, s, str);
			break;
		case K_ADD:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2B, lcdFd, dotFd, s, str);
			break;
		case K_SUB:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2D, lcdFd, dotFd, s, str);
			break;
		case K_MUL:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2A, lcdFd, dotFd, s, str);
			break;
		case K_DIV:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2F, lcdFd, dotFd, s, str);
			break;
		case K_FUN:
			fnd_clear(s, fnd_buf);
			spr_dis(0x46, lcdFd, dotFd, s, str);
			break;
		default: /* timeout */
			break;

		}

		for (i = 0; i < MAXFND; i++)
		{
			if ((s[i] < 0x30 && s[i] != '.') || (s[i] > 0x39 && s[i] != '.'))
			{
				if (s[i] != 0x71)
					s[i] = 0xF;
			}
		}

		for (i = 0; i < MAXFND; i++)
		{
			fndValue[i] = s[i] - '0';
		}

		for (i = 0; i < MAXFND; i++)
		{
			fnd_buf[i] = asc_to_fnd(fndValue[i]);
		}
		write(fndFd, fnd_buf, MAXFND);

		for (i = 0; i < MAXFND-1 ; i++)
		{
			s[i]=s[i+1];
		}
	}
	printf("Exit Program\n");
	close(keyFd);
	close(dotFd);
	close(fndFd);
	close(lcdFd);
	return 0;
}


