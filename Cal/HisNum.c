/* =================================================
 * Program ID : HisNum.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: History Number Checker
 * =================================================
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "History.h"
#include "Calculator.h"

#define START_ID 1

int num_history(int flag){
	struct history record;
	FILE *fp = fopen("history.txt", "rb");

	if (fp == NULL){
		return -1;
	}

	fseek(fp, (flag - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp) > 0) && (record.id != 0)){
		fclose(fp);
		return 1;
	}
	else {
		fclose(fp);
		return 0;
	}
}

