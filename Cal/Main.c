#include <stdio.h>
#include <fcntl.h>
#include "Dev.h"
#include "InfixCalculator.h"
#include "History.h"

/* Sample */
int main(int ac, char *av[])
{
	/* Init */
	int ch_to_int;
	int idx=0;
	int flag_s = 0;
	char null[5] = "NULL";

	/* KEY Init */
	unsigned char c;

	/* DOT Init */
	char ch;

	/* CLCD Init */
	char exp[MAXCHR];
	char res[MAXCHR];
	char before[MAXCHR] = "NULL";

	/* FND Init */
	int i, n, count;
	char temp;
	//char s[MAXFND] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char s[MAXFND];
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

	memset(exp, 0, sizeof(exp));
	memset(res, 0, sizeof(res));

	while (1){
		if(idx==32) {
			memset(exp, 0, sizeof(exp));
			memset(res, 0, sizeof(res));
			idx=0;
		}

		if (flag_s != 0){
			spr_lcd(before, exp);
		}
		if (strcmp(exp, null) == 0) {
			flag_s = 1;
		}
		
		c = key_get(10);


		switch (c){
		case K_NUM0:		
			spr_dis(0x30, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM1:
			spr_dis(0x31, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM2:
			spr_dis(0x32, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM3:
			spr_dis(0x33, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM4:
			spr_dis(0x34, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM5:
			spr_dis(0x35, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM6:
			spr_dis(0x36, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM7:
			spr_dis(0x37, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM8:
			spr_dis(0x38, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_NUM9:
			spr_dis(0x39, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_DOT:
			spr_dis(0x2E, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_ADD:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2B, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_SUB:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2D, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_MUL:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2A, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_DIV:
			fnd_clear(s, fnd_buf);
			spr_dis(0x2F, lcdFd, dotFd, s, exp, &idx);
			break;
		case K_EQU:
			fnd_clear(s, fnd_buf);
			spr_dis(0x3D, lcdFd, dotFd, s, exp, &idx);

			do_to_str(EvalInfixExp(exp), res);
			idx=0;
			save_history(exp,res,0);

			spr_lcd(lcdFd,exp,res);

			memset(before, 0, sizeof(before));
			strcpy(before, exp);
			memset(exp, 0, sizeof(exp));
			memset(res, 0, sizeof(res));
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
		idx++;
	}
	printf("Exit Program\n");
	close(keyFd);
	close(dotFd);
	close(fndFd);
	close(lcdFd);
	return 0;
}