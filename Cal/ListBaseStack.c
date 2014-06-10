/* =================================================
 * Program ID : ListBaseStack.c
 * Author     : SUM Project
 * Create Date: 2014-05-28
 * Compile Row: make - Reference Makefile
 * Description: ListBaseStack Application
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ListBaseStack.h"

/* Stack Init */
void StackInit(Stack * pstack)
{
	pstack->head = NULL;
}

/* Stack Empty Checker */
int SIsEmpty(Stack * pstack)
{
	if(pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

/* Push in Stack */
void SPush(Stack * pstack, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;
}

/* Pop from Stack */
Data SPop(Stack * pstack)
{
	Data rdata;
	Node * rnode;

	if(SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);

	return rdata;
}

/* Peek from Stack */
Data SPeek(Stack * pstack)
{
	if(SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->head->data;
}
