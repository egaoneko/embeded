/* =================================================
 * Program ID : Calculator.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: Calculator Application Function
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calculator.h"
#include "InfixCalculator.h"

/* Result To String */
int do_to_str(double d, char* r) {
	char *str;
	char str2[5];
	char str3[] = "Result is big";
	int count, sign;
	int i;
	char tmp;

	if (d==0) {
		r[0] = ' ';
		r[1] = '0';
		r[2] = '\0';
	}
	else if (d < 1 && d > -1){
		str = ecvt(d, 1, &count, &sign);

		if (sign == 0)
			r[0] = ' ';
		else
			r[0] = '-';

		r[1] = '1'; r[2] = '.'; r[3] = 'e'; r[4] = '-';
		
		//itoa(abs(count), str2, 10);
		sprintf(str,"%d",abs(count));

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

/* Expression Checker */
int exp_checker(char* s) {
	int len = strlen(s);
	int i;
	int opt_cnt = 0, dgt_cnt = 0, brkl_cnt = 0, brkr_cnt = 0;
	char str[16];
	char op[7]="+-*/()";
	char * pointer = NULL;

	strcpy(str,s);
	pointer=strtok(str,op);

	while(1){
		if(pointer == NULL) break;
		dgt_cnt++;
		pointer=strtok(NULL,op);
	}

	for (i = 0; i< len; i++){

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
