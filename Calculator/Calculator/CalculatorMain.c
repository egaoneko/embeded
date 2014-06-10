#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//#include <conio.h>
#include <ctype.h>
#include "Calculator.h"
#include "InfixCalculator.h"



int main(void)
{
	int i = 0, j = 0, k = 0;
	int flag_s = 0;
	char null[5] = "NULL";
	char in[LEN] = "NULL";
	char before[LEN] = "NULL";
	char res[CLEN];
	char before_2[LEN] = "NULL";
	char res_2[CLEN];
	

	//printf("=======================\n");
	//printf("Input an expression\n");
	//printf("=======================\n");

	while (1) {
		/* Start Flag */
		system("cls");
		if (flag_s != 0){
			spray(before, in);
		}
		if (strcmp(in, null) == 0) {
			flag_s = 1;
			memset(&in, 0, sizeof(in));
		}

		/* Input Data */
		in[i] = getche();
		fflush(stdout);

		/* Fun_Backspace */
		if (in[i] == 8) {
			in[i-1] = '\0';
			i--;
			continue;
		}

		/* Enter Data */
		if (in[i] == 13)
		{
			system("cls");
			in[i] = '\0';
			printf("%s \n", in);
			do_to_str(EvalInfixExp(in), res);
			printf("%s", res);
			i = 0;

			save_history(in,res,0);

			for (k = 1; num_history(k); k++);

			printf("\n##%d##\n", k-1);

			for (j = 1; j < k; j++){
				memset(&before_2, 0, sizeof(before_2));
				memset(&res_2, 0, sizeof(res_2));
				open_history(before_2, res_2, j);
				printf("\n%s\n", before_2);
				printf("%s\n", res_2);
			}

			memset(&before, 0, sizeof(before));
			strcpy(before, in);
			memset(&in, 0, sizeof(in));
			memset(&res, 0, sizeof(res));
			
			//memset(&before_2, 0, sizeof(before_2));
			//memset(&res_2, 0, sizeof(res_2));

			//open_history(before_2, res_2, 2);
			//printf("\n%s\n", before_2);
			//printf("%s\n", res_2);

			do{
				in[i] = getche();
				if (isFun(in[i])){
					spray(before, in);
				}
			} while (isFun(in[i]));
			i++;
			continue;
		}
		i++;
	}
	getch();

	return 0;
}

void spray(char before[LEN], char in[LEN]){
	char null[5] = "NULL";

	system("cls");
	if (strcmp(before, null) != 0)
		printf("%s = %f \n", before, EvalInfixExp(before));
	if (strcmp(in, null) != 0)
		printf("%s", in);
}

int isFun(char in){
	switch (in){
	case 8 :
		return 1;
	case 13 :
		return 1;
	case '\n' :
		return 1;
	}
	return 0;
}

int do_to_str(double d, char* r) {
	char *str;
	char str2[5];
	char str3[] = "Result is big";
	int count, sign;
	int i;
	char tmp;

	if (d < 1 && d > -1){
		str = ecvt(d, 1, &count, &sign);

		if (sign == 0)
			r[0] = ' ';
		else
			r[0] = '-';

		r[1] = '1'; r[2] = '.'; r[3] = 'e'; r[4] = '-';
		
		itoa(abs(count), str2, 10);

		for (i = 0; i < strlen(str2); i++){
			r[i + 5] = str2[i];
		}

		r[i+5] = '\0';
	}
	else {
		str = ecvt(d, CLEN, &count, &sign);
		strcpy(r, str);

		if (count>13){
			strcpy(r, str3);
			return -1;
		}

		for (i = CLEN - 1; i > count; i--)
			r[i] = r[i - 1];

		r[count] = '.';

		for (i = CLEN - 1; i > 0; i--)
			r[i] = r[i - 1];

		if (sign == 0)
			r[0] = ' ';
		else
			r[0] = '-';

		r[CLEN - 1] = '\0';
	}
}

int exp_checker(char* s) {
	int len = strlen(s);
	int i;
	int opt_cnt = 0, dgt_cnt = 0, brkl_cnt = 0, brkr_cnt = 0;


	for (i = 0; i< len; i++){
		if (isdigit(s[i])){
			dgt_cnt++;
			continue;
		}

		switch (s[i]){
		case '(':
			brkl_cnt++;
			break;
		case ')':
			brkr_cnt++;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			opt_cnt++;
			break;
		}
	}

	if (brkl_cnt != brkr_cnt)
		return -1;
	else if ((dgt_cnt - 1) != opt_cnt)
		return -1;

	return 0;
}