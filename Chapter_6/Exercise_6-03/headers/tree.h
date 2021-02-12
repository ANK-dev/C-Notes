#ifndef TREE_H
#define TREE_H

#include "linklist.h"

struct linklist;

struct tnode {                   /* the tree node      */
	char *word;                  /* points to the text */
	struct linklist *lines;      /* line numbers       */
	struct tnode *left;          /* left child         */
	struct tnode *right;         /* right child        */
};

struct tnode *addtree(struct tnode *p, char *w, int linenum);
void treeprint(struct tnode *p);
struct tnode *talloc(void);

#endif