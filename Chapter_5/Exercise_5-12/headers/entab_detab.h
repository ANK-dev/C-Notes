#define MAXLINE 100        /* maximum line size */
#define TABINC    8        /* default tab increment size */
#define YES       1
#define NO        0

int settab(int argc, char **argv, char *tab);
void entab(char *tab);
void detab(char *tab);
int tabpos(int pos, char *tab);