#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);

/* Removes trailing blanks, tabs and blank lines from input */
main()
{
    char line[MAXLINE];     /* current input line */

    while (getline(line, MAXLINE) > 0) {
        printf("\n\n%s\n", line);
    }

    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i = 0, bl = 0, tab = 0, nl = 0;

    while (i < lim - 1 && ((c=getchar()) != EOF)){
        if (c == ' ') {
            ++bl;
            tab = nl = 0;
            if (bl == 1){
                s[i] = c;
                ++i;
            }
        } else if (c == '\t') {
            ++tab;
            bl = nl = 0;
            if (tab == 1){
                s[i] = c;
                ++i;
            }
        } else if (c == '\n'){
            ++nl;
            tab = bl = 0;
            if (nl == 1){
                s[i] = c;
                ++i;
            }
        } else {
            bl = tab = nl = 0;
            s[i] = c;
            ++i;
        }
    }

    s[i] = '\0';
    return i;
}
