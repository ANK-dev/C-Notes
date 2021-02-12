/*
 * Exercise 6-02 - K&R 2nd ED
 * -- ANK-dev
 *
 * "Write a program that reads a C program and prints in alphabetical order
 * each group of variable names that are identical in the first 6 characters,
 * but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line."
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "headers/getword.h"

enum bool_e {NO, YES};

struct tnode {              /* the tree node      */
	char *word;             /* points to the text */
	enum bool_e match;      /* match found        */
	struct tnode *left;     /* left child         */
	struct tnode *right;    /* right child        */
};

#define MAXWORD 100

int compare(char *s, struct tnode *p, int num, enum bool_e *found);
int getword(char *, int);
char *strdup(char *s);
void treeprint(struct tnode *p);
struct tnode *addtree(struct tnode *p, char *w, int num, enum bool_e *found);
struct tnode *talloc(void);

/* print in alphabetic order each group of variable names identical in the first
 * num characters (default 6) */
int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	enum bool_e found = NO;     /* YES if match was found */
	int num;                    /* number of the first indent. chars */

	num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0] + 1) : 6;
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]) && strlen(word) >= (size_t) num)
			root = addtree(root, word, num, &found);
		found = NO;
	}
	treeprint(root);
	return 0;
}


/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int num, enum bool_e *found)
{
	int cond;

	if (p == NULL) {            /* a new word has arrived */
		p = talloc();           /* make a new node */
		p->word = strdup(w);
		p->match = *found;
		p->left = p->right = NULL;
	} else if ((cond = compare(w, p, num, found)) < 0)
		p->left = addtree(p->left, w, num, found);
	else if (cond > 0)
		p->right = addtree(p->right, w, num, found);
	return p;
}

/* compare: compare words and update p->match */
int compare(char *s, struct tnode *p, int num, enum bool_e *found)
{
	int i;
	char *t = p->word;

	for (i = 0; *s == *t; i++, s++, t++)
		if (*s == '\0')
			return 0;
	if (i >= num) {     /* identical in the first num chars ? */
		*found = YES;
		p->match = YES;
	}
	return *s - *t;
}

/* treeprint: in-order print of tree p if p->match == YES */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		if (p->match)
			printf("%s\n", p->word);
		treeprint(p->right);
	}
}

/* strdup: make a duplicate of s */
char *strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}