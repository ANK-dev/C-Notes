#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/tree.h"
#include "../headers/linklist.h"
#include "../headers/getword.h"

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
	int cond;

	if (p == NULL) {            /* a new word has arrived */
		p = talloc();           /* make a new node */
		p->word = strdup(w);
		p->lines = lalloc();
		p->lines->lnum = linenum;
		p->lines->ptr = NULL;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		addln(p, linenum);
	else if (cond < 0)
		p->left = addtree(p->left, w, linenum);
	else
		p->right = addtree(p->right, w, linenum);
	return p;
}

/* treeprint: in-order print of tree p if p->match == YES */
void treeprint(struct tnode *p)
{
	struct linklist *temp;

	if (p != NULL) {
		treeprint(p->left);
		printf("%10s: ", p->word);
		for (temp = p->lines; temp != NULL; temp = temp->ptr)
			printf("%4d ", temp->lnum);
		printf("\n");
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}