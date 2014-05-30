#ifndef __HISTORY__
#define __HISTORY__

#define E_MAX_N 30
#define R_MAX_N 30
#define A_MAX_N 20


struct history{
	int id;
	char exp[E_MAX_N];
	char res[R_MAX_N];
};

int save_history(char *s, char *r, int flag);
int open_history(char *s, char *r, int flag);

#endif
