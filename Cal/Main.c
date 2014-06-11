/* =================================================
 * Program ID : Main.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: Merge Device Driver Application and
 *            : Calculator Application 
 * =================================================
 */


#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include "Dev.h"
#include "InfixCalculator.h"
#include "History.h"

/* KEY_FUN */
unsigned char key_get(int tmo);

/* BTN_FUN */
unsigned char btn_get(int tmo);

/* BTN_Thread */
void * handle_btn(void * arg);
pthread_mutex_t mutx;
int btn_flag[4]={0,};

/* Main */
int main(int ac, char *av[])
{
	/* Init */
	int ch_to_int;
	int idx=0;
	int k;
	int flag_s = 0;
	int data;
	char null[5] = "NULL";
	pthread_t t_id;

	int flag_F=0;
	int flag_E=0;
	int flag_O=0;
	int flag_D=0;
	int flag_B=0;
	int flag_H=0;
	int flag_HE=0;
	int HL_C=0;
	int HL_N=0;

	/* KEY Init */
	unsigned char c;

	/* DOT Init */
	char ch;
	unsigned char dot_col_C[5]={0x00, 0x00, 0x00, 0x00, 0x00};

	/* CLCD Init */
	char exp[MAXCHR]="NULL";
	char res[MAXCHR];
	char before[MAXCHR] = "   Calculator   ";
	char b_his_1[LEN];
	char r_his_1[CLEN];
	char b_his_2[LEN];
	char r_his_2[CLEN];

	/* FND Init */
	int i, n, count;
	char temp;
	unsigned char fnd_C[MAXFND + 1] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	char s[MAXFND];
	unsigned char fnd_buf[MAXFND + 1];
	int fndValue[MAXFND] = { 0 };

	/* Init Device Driver */ 
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
	if(( btnFd = open(btnDev, O_RDWR )) < 0){ 
		error_handling("BTN", btnFd);
	}
	if(( ledFd = open(ledDev, O_RDWR )) < 0){ 
		error_handling("LED", ledFd);
	}

	/* Init Thread */
	pthread_mutex_init(&mutx, NULL);
	pthread_create(&t_id, NULL, handle_btn, (void*)&btnFd);

	printf("\n");
	printf("--------------------------\n");
	printf("     [Multi TEST]    \n");
	printf("     Ctrl + C -> Quit	  \n");
	printf("--------------------------\n");

	/* Init FND */
	memset(s, 0, MAXFND + 2);
	memset(fnd_buf, 0, sizeof(fnd_buf));

	/* Init Clcd */
	memset(exp, 0, sizeof(exp));
	memset(res, 0, sizeof(res));

	/* Clear for Calculator */
	spr_lcd(lcdFd,"   Calculator   ","");
	write(dotFd, dot_col_C, DOT_COL);
	write(fndFd, fnd_C, MAXFND);
	led_start(ledFd,1);

	/* Main Loop */
	while (1){
		/* Check First or Not */
		if (flag_s != 0){
			spr_lcd(before, exp);
		}
		/* First Flag set false */
		if (strcmp(exp, null) == 0) {
			flag_s = 1;
		}
		/* Exit */
		if (btn_flag[0]==1) {
			spr_lcd(lcdFd,"_____Exit_____", "");
			write(dotFd, dot_col_C, DOT_COL);
			write(fndFd, fnd_C, MAXFND);
			led_start(ledFd,5);
			break;
		}

		/* Get Key */
		c = key_get(10);

		/* Check String Length */
		if(idx==15) {
			if(c==K_EQU && btn_flag[3]==0){
			}
			else if(c==K_DIV && btn_flag[3]==1){
			}
			else{
				spr_lcd("Too many input", exp);
				led_start(ledFd,8);
				continue;
			}
		}

		/* Do Calculator Function by using key values */
		switch (c){

		/* Num 0 Key */
		case K_NUM0:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x30, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x30, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				/* Basket Left '(' */
				if(flag_B==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x28, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x28, lcdFd, dotFd, s, exp, &idx, before);
					flag_B=1;
				}
				else{
					continue;
				}
			}
			break;

		/* Num 1 Key */
		case K_NUM1:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x31, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x31, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 2 Key */
		case K_NUM2:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x32, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x32, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 3 Key */
		case K_NUM3:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x33, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x33, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 4 Key */
		case K_NUM4:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x34, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x34, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 5 Key */
		case K_NUM5:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x35, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x35, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				if(flag_H==1){
					/* History Up */
					fnd_clear(s, fnd_buf);
					spr_dis(0x55, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));

					if(HL_N < HL_C+1){
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						open_history(b_his_1, r_his_1, HL_N);
						spr_lcd(lcdFd,b_his_1,"______END______");
					}
					else{
						HL_C++;
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						memset(&b_his_2, 0, sizeof(b_his_2));
						memset(&r_his_2, 0, sizeof(r_his_2));
						open_history(b_his_1, r_his_1, HL_C);
						open_history(b_his_2, r_his_2, HL_C-1);
						spr_lcd(lcdFd,b_his_2,b_his_1);
					}
					continue;
				}
				else {
					continue;
				}
			}
			break;

		/* Num 6 Key */
		case K_NUM6:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x36, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x36, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 7 Key */
		case K_NUM7:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x37, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x37, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Num 8 Key */
		case K_NUM8:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x38, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x38, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				if(flag_H==1){
					/* History Down */
					fnd_clear(s, fnd_buf);
					spr_dis(0x44, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));

					if(HL_C-1==1){
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						open_history(b_his_1, r_his_1, HL_C);
						spr_lcd(lcdFd,"_____FIRST_____",b_his_1);
					}
					else{
						HL_C--;
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						memset(&b_his_2, 0, sizeof(b_his_2));
						memset(&r_his_2, 0, sizeof(r_his_2));
						open_history(b_his_1, r_his_1, HL_C);
						open_history(b_his_2, r_his_2, HL_C-1);
						spr_lcd(lcdFd,b_his_2,b_his_1);
					}
					continue;
				}
				else {
					continue;
				}
			}
			break;

		/* Num 9 Key */
		case K_NUM9:
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				if(flag_HE==1)
					spr_dis(0x39, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
				else
					spr_dis(0x39, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			break;

		/* Dot Key */
		case K_DOT:
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					if(flag_HE==1)
						spr_dis(0x2E, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x2E, lcdFd, dotFd, s, exp, &idx, before);
					flag_D=1;
				}
				else{
					continue;
				}
			}
			else{
				/* Basket Right ')' */
				if(flag_B==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x29, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x29, lcdFd, dotFd, s, exp, &idx, before);
					flag_B=1;
				}
				else{
					continue;
				}
			}
			break;

		/* Add Key */
		case K_ADD:
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x2B, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x2B, lcdFd, dotFd, s, exp, &idx, before);
					flag_O=1;
				}
				else{
					continue;
				}
			}
			else{
				/* History List */
				flag_HE=0;
				flag_H=1;
				for (k = 1; num_history(k); k++);
				HL_N=k-1; HL_C=k-1;

				fnd_clear(s, fnd_buf);
				spr_dis(0x4C, lcdFd, dotFd, s, exp, &idx, before);
				idx=0;
				memset(exp, 0, sizeof(exp));
				memset(res, 0, sizeof(res));

				if((HL_N)<1){
					spr_lcd(lcdFd,"   Not Exist","     History");
				}
				else if(HL_N==1){
					memset(&b_his_1, 0, sizeof(b_his_1));
					memset(&r_his_1, 0, sizeof(r_his_1));
					open_history(b_his_1, r_his_1, HL_N);
					spr_lcd(lcdFd,b_his_1,"");
				}
				else {
					memset(&b_his_1, 0, sizeof(b_his_1));
					memset(&r_his_1, 0, sizeof(r_his_1));
					memset(&b_his_2, 0, sizeof(b_his_2));
					memset(&r_his_2, 0, sizeof(r_his_2));
					open_history(b_his_1, r_his_1, HL_N);
					open_history(b_his_2, r_his_2, HL_N-1);
					spr_lcd(lcdFd,b_his_2,b_his_1);
				}
				continue;
			}
			break;

		/* Subtract Key */
		case K_SUB:
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x2D, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x2D, lcdFd, dotFd, s, exp, &idx, before);
					flag_O=1;
				}
				else{
					continue;
				}
			}
			else{
				if(flag_H==1){
					/* History Edit */
					fnd_clear(s, fnd_buf);
					spr_dis(0x45, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));


					if(HL_C!=0){
						flag_HE=1;
						btn_flag[3]=0;

						spr_lcd(lcdFd,"      EDIT     ","");
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						open_history(b_his_1, r_his_1, HL_C);
					}
					continue;
				}
				else {
					continue;
				}
			}
			break;

		/* Multiply Key */
		case K_MUL:
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x2A, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x2A, lcdFd, dotFd, s, exp, &idx, before);
					flag_O=1;
				}
				else{
					continue;
				}
			}
			else{
				if(flag_H==1){
					/* History Select */
					fnd_clear(s, fnd_buf);
					spr_dis(0x53, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));

					if(HL_C!=0){
						memset(&b_his_1, 0, sizeof(b_his_1));
						memset(&r_his_1, 0, sizeof(r_his_1));
						open_history(b_his_1, r_his_1, HL_C);
						spr_lcd(lcdFd,b_his_1,r_his_1);
					}
					continue;
				}
				else {
					continue;
				}
			}
			break;

		/* Divide Key */
		case K_DIV:
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					if(flag_HE==1)
						spr_dis(0x2F, lcdFd, dotFd, s, exp, &idx, "      EDIT     ");
					else
						spr_dis(0x2F, lcdFd, dotFd, s, exp, &idx, before);
					flag_O=1;
				}
				else{
					continue;
				}
			}
			else{
				/* BackSpace */
				if(idx > 0) {
					exp[idx-1] = '\0';
					idx--;
					fnd_clear(s, fnd_buf);
					spr_dis(0x42, lcdFd, dotFd, s, exp, &idx, before);
				}			
				continue;
			}
			break;

		/* Equal Key */
		case K_EQU:
			if(btn_flag[3]==0){
				/* Equal */
				if(flag_E==0 && flag_O==0 && flag_D==0 && flag_HE==0){
					fnd_clear(s, fnd_buf);
					spr_dis(0x3D, lcdFd, dotFd, s, exp, &idx, before);
					
					if(exp_checker(exp)!=-1){
						do_to_str(EvalInfixExp(exp), res);
						
						save_history(exp,res,0);
						spr_lcd(lcdFd,exp,res);

						memset(before, 0, sizeof(before));
						strcpy(before, exp);
						led_start(ledFd,3);
					}
					else{
						spr_lcd(lcdFd,"  Syntax Error ","");
						led_start(ledFd,2);
					}
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));
					flag_E=1;
					continue;
				}
				else if(flag_E==0 && flag_O==0 && flag_D==0 && flag_HE==1){
					fnd_clear(s, fnd_buf);
					spr_dis(0x3D, lcdFd, dotFd, s, exp, &idx, before);

					if(exp_checker(exp)!=-1){
						do_to_str(EvalInfixExp(exp), res);
						save_history(exp,res,HL_C);

						spr_lcd(lcdFd,exp,res);
						led_start(ledFd,3);
					}
					else{
						spr_lcd(lcdFd,"  Syntax Error ","");
						led_start(ledFd,2);
					}
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));
					flag_HE=0;
					flag_E=1;
					continue;
				}
				else{
					continue;
				}
			}
			else{
				/* Clear */
				fnd_clear(s, fnd_buf);
				spr_dis(0x43, lcdFd, dotFd, s, exp, &idx, before);
				idx=0;
				spr_lcd(lcdFd,before," ");
				memset(exp, 0, sizeof(exp));
				memset(res, 0, sizeof(res));
				continue;
			}
			break;
		default: /* timeout */
			break;

		}
		
		/* FND Display */
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

		/* FND Shift */
		for (i = 0; i < MAXFND-1 ; i++)
		{
			s[i]=s[i+1];
		}
		idx++;
	}
	printf("Exit Program\n");
	pthread_cancel(t_id);
	close(keyFd);
	close(dotFd);
	close(fndFd);
	close(lcdFd);
	close(btnFd);
	close(ledFd);
	return 0;
}

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

/* BTN_FUN */
unsigned char btn_get(int tmo)
{
	unsigned char b;

	if (tmo){
		if (tmo < 0)
			tmo = ~tmo * 1000;
		else
			tmo *= 1000000;
		while (tmo > 0){
			usleep(400000);
			ioctl(btnFd, GPIO_BTN_READ, &b);
			if (b) return(b);
			tmo -= 10000;
		}
		return(-1);
	}
	else {
		read(btnFd, &b, sizeof(b));
		return(b);
	}
} 

/* BTN_Thread */
void * handle_btn(void * arg)
{
	unsigned char dot_col_F[5]={0x7F, 0x48, 0x48, 0x48, 0x40};
	unsigned char dot_col_M[5]={0x7F, 0x20, 0x10, 0x20, 0x7F};
	int bf=*((int*)arg);
	int df=dotFd;
	char  buf;

	while(1) {
	read( bf, &buf, sizeof(buf));
	switch(buf) {
		/* Exit Key */
		case 1:
			pthread_mutex_lock(&mutx);
			btn_flag[0]=1;
			pthread_mutex_unlock(&mutx);
			break;

		case 2:
			pthread_mutex_lock(&mutx);
			btn_flag[1]=1;
			pthread_mutex_unlock(&mutx);
			break;

		case 3:
			pthread_mutex_lock(&mutx);
			btn_flag[2]=1;
			pthread_mutex_unlock(&mutx);
			break;
		
		/* Function Key */ 
		case 4:
			pthread_mutex_lock(&mutx);
			
			if(btn_flag[3]==0){			
				btn_flag[3]=1;
				write(df, dot_col_F, DOT_COL);
			}
			else{
				btn_flag[3]=0;
				write(df, dot_col_M, DOT_COL);
			}
			pthread_mutex_unlock(&mutx);
			break;
		default:
			break;
		}
	usleep(400000);
	}
}
