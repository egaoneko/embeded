#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "Calculator.h"
#include "InfixToPostfix.h"
#include "PostCalculator.h"

double EvalInfixExp(char exp[LEN])
{
	int len = strlen(exp);
	double ret;
	char expcpy[LEN];
	strcpy(expcpy, exp);

	ConvToRPNExp(expcpy);
	ret = EvalRPNExp(expcpy);

	return ret;
}
