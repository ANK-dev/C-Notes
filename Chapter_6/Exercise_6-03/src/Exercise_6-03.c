/*
 * Exercise 6-03 - K&R 2nd ED
 * -- ANK-dev
 *
 * "Write a cross-referencer that prints a list of all words in a document,
 * and, for each word, a list of the line numbers on which it occurs. Remove
 * noise words like "the," "and," and so on."
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "headers/getword.h"
#include "headers/linklist.h"
#include "headers/tree.h"

#define MAXWORD 100

int noiseword(char *w);

/* cross-referencer */
int main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	int linenum = 1;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && noiseword(word) == -1)
			root = addtree(root, word, linenum);
		else if (word[0] == '\n')
			linenum++;
	treeprint(root);
	return 0;
}

/* noiseword: identify word as a noise word */
int noiseword(char *w)
{
	static const char *nw[] = {
		"a",
		"and",
		"are",
		"in",
		"is",
		"of",
		"or",
		"that",
		"the",
		"this",
		"to"
	};
	int cond, mid;
	int low = 0;
	int high = sizeof(nw) / sizeof(char *) - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(w, nw[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}