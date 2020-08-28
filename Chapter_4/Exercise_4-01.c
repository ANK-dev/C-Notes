/**
 * Exercise 4-1 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * strrindex(s,t):  returns the position of the _rightmost_ occurrence of t in s
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

int getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main()
{
    char pattern[MAXLINE];    /* pattern to search for */
    char line[MAXLINE];
    int rightmost_position;

    printf("strrindex\n=========\n");
    printf("> returns the position of the _rightmost_ occurrence of pattern "
           "`t` in string `s`\n\n");

    do {
        printf("Insert pattern to search for: ");
    } while (getline(pattern, MAXLINE) == 0);

    printf("Insert string to search for pattern -- EOF (CTRL + D) to exit:\n");
    while (getline(line, MAXLINE) > 0) {
        rightmost_position = strrindex(line, pattern);

        if (rightmost_position != -1) {
            printf("Rightmost match FOUND @ index %d\n\n", rightmost_position);
        } else {
            printf("Rightmost match NOT FOUND in string\n\n");
        }
    }
    return 0;
}

/* getline:  get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strrindex:  return index of _rightmost_ t in s, -1 if none */
int strrindex(char s[], char t[])
{
    int i, j, k;
    int last_position = -1;     /* rightmost position where pattern was found */

    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            last_position = i;
    }
    return last_position;
}
