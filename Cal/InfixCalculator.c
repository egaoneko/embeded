#include <string.h>
#include <stdlib.h>
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
