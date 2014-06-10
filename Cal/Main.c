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

/* Sample */
int main(int ac, char *av[])
{
	/* Init */
	int ch_to_int;
	int idx=0;
	int k;
	int flag_s = 0;
	char null[5] = "NULL";
	pthread_t t_id;

	int flag_F=0;
	int flag_E=0;
	int flag_O=0;
	int flag_D=0;
	int flag_B=0;
	int flag_H=0;

	/* KEY Init */
	unsigned char c;

	/* DOT Init */
	char ch;

	/* CLCD Init */
	char exp[MAXCHR]="NULL";
	char res[MAXCHR];
	char before[MAXCHR] = "Calculator";
	char b_his_1[LEN];
	char r_his_1[CLEN];
	char b_his_2[LEN];
	char r_his_2[CLEN];

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
	if(( btnFd = open(btnDev, O_RDWR )) < 0){ 
		error_handling("BTN", btnFd);
	}
	if(( ledFd = open(btnDev, O_RDWR )) < 0){ 
		error_handling("LED", ledFd);
	}

	pthread_mutex_init(&mutx, NULL);
	pthread_create(&t_id, NULL, handle_btn, (void*)&btnFd);

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
			printf("##\n");
			//pthread_mutex_lock(&mutx);
			printf("##\n");
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x30, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				/* Basket Left '(' */
				if(flag_B==0){
					fnd_clear(s, fnd_buf);
					spr_dis(0x28, lcdFd, dotFd, s, exp, &idx, before);
					flag_B=1;
				}
				else{
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM1:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x31, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM2:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x32, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM3:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x33, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM4:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x34, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM5:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x35, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				if(flag_H==1){
					/* History Down */
					fnd_clear(s, fnd_buf);
					spr_dis(0x44, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));
					continue;
				}
				else {
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM6:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x36, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM7:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x37, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM8:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x38, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				if(flag_H==1){
					/* History Up */
					fnd_clear(s, fnd_buf);
					spr_dis(0x55, lcdFd, dotFd, s, exp, &idx, before);
					idx=0;
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));
					continue;
				}
				else {
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_NUM9:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				flag_E=0;
				flag_O=0;
				flag_D=0;
				flag_B=0;
				flag_H=0;
				spr_dis(0x39, lcdFd, dotFd, s, exp, &idx, before);
			}
			else{
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_DOT:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
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
					spr_dis(0x28, lcdFd, dotFd, s, exp, &idx, before);
					flag_B=1;
				}
				else{
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_ADD:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					spr_dis(0x2B, lcdFd, dotFd, s, exp, &idx, before);
					flag_O=1;
				}
				else{
					continue;
				}
			}
			else{
				/* History List */
				flag_H=1;
				for (k = 1; num_history(k); k++);

				fnd_clear(s, fnd_buf);
				spr_dis(0x4C, lcdFd, dotFd, s, exp, &idx, before);
				idx=0;
				memset(exp, 0, sizeof(exp));
				memset(res, 0, sizeof(res));

				if((k-1)<1){
					spr_lcd(lcdFd,"   Not Exist","     History");
				}
				else if((k-1)==1){
					memset(&b_his_1, 0, sizeof(b_his_1));
					memset(&r_his_1, 0, sizeof(r_his_1));
					open_history(b_his_1, b_his_1, k-1);
					spr_lcd(lcdFd,b_his_1,"");
				}
				else {
					memset(&b_his_1, 0, sizeof(b_his_1));
					memset(&r_his_1, 0, sizeof(r_his_1));
					memset(&b_his_2, 0, sizeof(b_his_2));
					memset(&r_his_2, 0, sizeof(r_his_2));
					open_history(b_his_1, r_his_1, k-1);
					open_history(b_his_2, r_his_2, k-2);
					spr_lcd(lcdFd,b_his_2,b_his_1);
				}
				continue;
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_SUB:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
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
					continue;
				}
				else {
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_MUL:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
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
					continue;
				}
				else {
					continue;
				}
			}
			//pthread_mutex_unlock(&mutx);
			break;
		case K_DIV:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
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
			//pthread_mutex_unlock(&mutx);
			break;
		case K_EQU:
			//pthread_mutex_lock(&mutx);
			if(btn_flag[3]==0){
				/* Equal */
				if(flag_E==0 && flag_O==0 && flag_D==0){
					fnd_clear(s, fnd_buf);
					spr_dis(0x3D, lcdFd, dotFd, s, exp, &idx, before);

					do_to_str(EvalInfixExp(exp), res);
					idx=0;
					save_history(exp,res,0);

					spr_lcd(lcdFd,exp,res);

					memset(before, 0, sizeof(before));
					strcpy(before, exp);
					memset(exp, 0, sizeof(exp));
					memset(res, 0, sizeof(res));
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
			//pthread_mutex_unlock(&mutx);
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
	unsigned char dot_col[5]={0x7F, 0x48, 0x48, 0x48, 0x40};
	int bf=*((int*)arg);
	int df=dotFd;
	char  buf;

	while(1) {
	read( bf, &buf, sizeof(buf));
	switch(buf) {
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
		case 4:
			pthread_mutex_lock(&mutx);
			write(df, dot_col, DOT_COL);
			if(btn_flag[3]==0)			
				btn_flag[3]=1;
			else
				btn_flag[3]=0;
			pthread_mutex_unlock(&mutx);
			break;
		default:
			break;
		}
	usleep(400000);
	}
}
