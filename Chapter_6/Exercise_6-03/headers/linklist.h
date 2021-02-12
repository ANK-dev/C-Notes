#ifndef LINKLIST_H
#define LINKLIST_H

#include "tree.h"

struct linklist {           /* linked list of line numbers */
	int lnum;
	struct linklist *ptr;
};

struct linklist *lalloc(void);

struct tnode;              /* forward declaration */

void addln(struct tnode *p, int linenum);

#endif