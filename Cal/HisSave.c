/* =================================================
 * Program ID : HisSave.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: History Saver
 * =================================================
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "History.h"
#include "Calculator.h"

#define START_ID 1

int save_history(char *s, char *r, int flag){
	struct history record;
	int b_Id = 1;
	FILE *fp;
	
	if (flag != 0)
		fp= fopen("history.txt", "r+b"); //r+ : overwrite, w+ : rewrite, a+ : append
	else
		fp = fopen("history.txt", "a+b");

	if (fp == NULL){
		fp = fopen("history.txt", "a+b");
	}

	fseek(fp, 0L, SEEK_SET);
	do{
		if ((fread(&record, sizeof(record), 1, fp) > 0) && (record.id != 0)) {
			b_Id++;
		}
		else break;
		fseek(fp, sizeof(record), SEEK_CUR);
	} while (1);

	if (flag != 0)
		b_Id = flag;


	record.id = b_Id;
	strcpy(record.exp, s);
	strcpy(record.res, r);

	fseek(fp, (b_Id - START_ID) * sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp);
	fclose(fp);
}

