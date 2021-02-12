#define BUFSIZE 100

int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
int comment(void);

char *strdup(char *s);