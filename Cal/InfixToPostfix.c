#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Calculator.h"
#include "ListBaseStack.h"

int GetOpPrec(char op)
{
	switch(op)
	{
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	case '(':
		return 1;
	}

	return -1;
}

int WhoPrecOp(char op1, char op2)
{
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);

	if(op1Prec > op2Prec)
		return 1;
	else if(op1Prec < op2Prec)
		return -1;
	else
		return 0;
}

void ConvToRPNExp(char exp[LEN])
{
	Stack stack;
	int expLen = strlen(exp);
	char convExp[LEN];

	int i, idx = 0;
	int flag_d = 0;
	char tok, popOp;
	
	StackInit(&stack);

	for(i=0; i<expLen; i++)
	{
		tok = exp[i];
		if (isdigit(tok)){
			convExp[idx++] = tok;
		}
		else if (tok == '.'){
			convExp[idx++] = tok;
		}
		else
		{
			convExp[idx++] = ' ';
			switch(tok)
			{
			case '(':
				SPush(&stack, tok);
				break;

			case ')':
				while(1)
				{
					popOp = SPop(&stack);
					if(popOp == '(')
						break;
					convExp[idx++] = popOp;
				}
				break;

			case '+': case '-': 
			case '*': case '/':
				while(!SIsEmpty(&stack) && 
						WhoPrecOp(SPeek(&stack), tok) >= 0)
					convExp[idx++] = SPop(&stack);

				SPush(&stack, tok);
				break;
			}
		}
	}

	while(!SIsEmpty(&stack))
		convExp[idx++] = SPop(&stack);

	convExp[idx] = '\0';

	strcpy(exp, convExp);
}
