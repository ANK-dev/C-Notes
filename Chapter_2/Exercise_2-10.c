/**
 * Exercise 2-10 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * lower (conditional expression ver.): converts upper case to lower case
 * ----------------------------------------------------------------------
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int lower(int c);
char *getline(char s[]);

int main()
{
    int c;

    printf("lower (conditional expression ver.)\n"
           "===================================\n");
    printf("> converts upper case to lower case; ASCII only\n\n");

    /* get the input string */
    printf("Type the input string (CTRL + D to exit)\n");

    c = '\0';
    while (c != EOF) {
        printf("\n> ");        
        while ((c = getchar()) != EOF && c != '\n') {
            putchar(lower(c));
        }
    }
    
    putchar('\n');

    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
