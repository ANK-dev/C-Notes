#ifndef STRUCT_PROC_H
#define STRUCT_PROC_H

struct nlist {              /* table entry         */
	struct nlist *next;     /* next entry in chain */
	char *name;             /* defined name        */
	char *defn;             /* replacement text    */
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
unsigned hash(char *s);

#endif