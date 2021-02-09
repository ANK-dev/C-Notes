#define MAXTOKEN 100
#define BUFSIZE  100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void dirdcl(void);

int gettoken(void);
void errmsg(const char *);

int  getch(void);
void ungetch(int c);
void bufclr(void);

void parmdcl(void);
void dclspec(void);
int typespec(void);
int typequal(void);
/*int compare(char **, char **);*/
int compare(const void *s, const void *t);