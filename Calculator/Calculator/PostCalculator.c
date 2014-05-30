#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <ctype.h>
#include "Calculator.h"
#include "ListBaseStack.h"

double EvalRPNExp(char exp[LEN])
{
	Stack stack;
	int expLen = strlen(exp);
	int i,j;
	int flag_d = 0;
	int flag_dot = 0, cnt_dot=0;
	char tok;
	double op1, op2;

	StackInit(&stack);

	for(i=0; i<expLen; i++)
	{
		tok = exp[i];

		if(isdigit(tok)||tok==' '||tok=='.')
		{
			if (tok == ' '){
				flag_d = 0;
				flag_dot = 0;
				continue;
			}

			if (tok == '.'){
				flag_dot = 1;
				cnt_dot = 1;
				continue;
			}

			if (flag_d == 0){
				flag_d = 1;
				SPush(&stack, tok - '0');
			}
			else if (flag_d == 1&& flag_dot!=1){
				double digit = SPop(&stack);
				SPush(&stack, (digit * 10) + tok - '0');
			}
			else if (flag_d == 1 && flag_dot == 1){
				double digit = SPop(&stack);
				double dot = tok - '0';
				for (j = 0; j < cnt_dot; j++){
					dot /= 10;
				}
				SPush(&stack, digit + dot);
			}
		}
		else
		{
			flag_d = 0;
			op2 = SPop(&stack); 
			op1 = SPop(&stack);

			switch(tok)
			{
			case '+':
				SPush(&stack, op1+op2);
				break;
			case '-':
				SPush(&stack, op1-op2);
				break;
			case '*':
				SPush(&stack, op1*op2);
				break;
			case '/':
				SPush(&stack, op1/op2);
				break;
			}
		}
	}
	return SPop(&stack);
}
