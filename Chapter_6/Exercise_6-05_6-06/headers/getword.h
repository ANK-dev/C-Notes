#ifndef GETWORD_H
#define GETWORD_H

int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
int comment(void);
void skipblanks(void);
void error(int c, const char *s);
char *strdup(char *s);

#endif