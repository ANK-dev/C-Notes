/**
 * Exercise 2-5 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * any:  returns the location of a character from an input string
 * --------------------------------------------------------------
 */

#include <stdio.h>
#define MAXLINE 1000

int any(char s1[], char s2[]);
void getline(char s[]);

int main()
{
    char string1[MAXLINE], string2[MAXLINE];
    printf("any\n===\n\n");
    printf("> Finds the first location of a character in the 1st string that "
           "matches *any* character from the 2nd string.\n\n");
    printf("Type the 1st string: ");
    getline(string1);
    printf("Type the 2nd string: ");
    getline(string2);
    printf("\nThe first location of a character from the 2nd string is: %d\n",
           any(string1, string2));
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j, found;
    for (i = 0; s1[i] != '\0'; ++i) {
        found = 0;

        for (j = 0; s2[j] != '\0'; ++j) {
            if (s2[j] == s1[i]) {
                found = 1;
                break;
            }
        }

        if (found) break;

    }

    return found ? i : -1;
}

void getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAXLINE - 1) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';
}