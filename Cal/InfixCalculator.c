/* =================================================
 * Program ID : InfixCalculator.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: Calculate Infix
 * =================================================
 */

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
