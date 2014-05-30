#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "History.h"

#define START_ID 1

int open_history(char *s, char *r, int flag)  {
	struct history record;
	char str[] = "Not Exist";

	FILE *fp = fopen("history.txt", "rb");

	fseek(fp, (flag - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp) > 0) && (record.id != 0)){
		strcpy(s, record.exp);
		strcpy(r, record.res);
	}
	else {
		strcpy(s, str);
		strcpy(r, str);
		fclose(fp);
		return -1;
	}
	fclose(fp);
}
