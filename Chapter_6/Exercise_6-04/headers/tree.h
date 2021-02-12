#ifndef TREE_H
#define TREE_H

struct tnode {                   /* the tree node      */
	char *word;                  /* points to the text */
	int count;                   /* line numbers       */
	struct tnode *left;          /* left child         */
	struct tnode *right;         /* right child        */
};

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct tnode *talloc(void);
void treestore(struct tnode *list[], struct tnode *p);
void sortlist(struct tnode *list[]);

#endif