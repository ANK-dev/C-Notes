#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/tree.h"
#include "headers/getword.h"

#define NDISTINCT 1000

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {            /* a new word has arrived */
		p = talloc();           /* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p if p->match == YES */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* treestore: store in list[] pointers to tree nodes */
void treestore(struct tnode *list[], struct tnode *p)
{
	extern int ntn;

	if (p != NULL) {
		treestore(list, p->left);
		if (ntn < NDISTINCT)
			list[ntn++] = p;
		treestore(list, p->right);
	}
}

/* sortlist: sort list of pointers to tree nodes */
void sortlist(struct tnode *list[])
{
	extern int ntn;

	int gap, i, j;
	struct tnode *temp;

	for (gap = ntn/2; gap > 0; gap /= 2)
		for (i = gap; i < ntn; i++)
			for (j = i-gap; j >= 0; j -= gap) {
				if ((list[j]->count) >= (list[j+gap]->count))
					break;
				temp = list[j];
				list[j] = list[j+gap];
				list[j+gap] = temp;
			}
}