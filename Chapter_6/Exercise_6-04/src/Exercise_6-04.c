/*
 * Exercise 6-04 - K&R 2nd ED
 * -- ANK-dev
 *
 * "Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurence. Precede each word by its count."
 */

#include <stdio.h>
#include <ctype.h>
#include "headers/tree.h"
#include "headers/getword.h"

#define MAXWORD    100
#define NDISTINCT 1000

struct tnode *list[NDISTINCT];      /* pointers to tree nodes */
int ntn = 0;                        /* number of tree nodes   */

/* print distinct words sorted in decreasing order of freq. */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];
    int i;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treestore(list, root);
    sortlist(list);
    for (i = 0; i < ntn; i++)
        printf("%2d:%20s\n", list[i]->count, list[i]->word);
    return 0;
}