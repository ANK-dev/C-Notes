#include <stdio.h>
#include <stdlib.h>
#include "../headers/linklist.h"
#include "../headers/tree.h"

/* addln: add a line number to the linked list */
void addln(struct tnode *p, int linenum)
{
	struct linklist *temp;

	temp = p->lines;
	while (temp->ptr != NULL && temp->lnum != linenum)
		temp = temp->ptr;
	if (temp->lnum != linenum) {
		temp->ptr = lalloc();
		temp->ptr->lnum = linenum;
		temp->ptr->ptr = NULL;
	}
}

/* lalloc: make a linklist node */
struct linklist *lalloc(void)
{
	return (struct linklist *) malloc(sizeof(struct linklist));
}