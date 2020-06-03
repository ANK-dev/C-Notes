#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);

/* print all input lines that are longer than 80 characters */
main()
{
    int len;        /* current line length */
    int min;        /* minimum length (80 characters) */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    min = 80;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len > min) {
            printf("\n\nLength: %d. %s\n", len, line);
        }

    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    } else {
        /* if line is longer than 1000 characters, keep counting.*/
        while ((c=getchar()) != EOF && c != '\n'){  
            ++i;
        }
    }
    s[i] = '\0';
    return i;
}
