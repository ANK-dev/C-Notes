/**
 * Exercise 3-3 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * expand:  expands shorthand notation into complete list
 * ------------------------------------------------------
 */

#include <stdio.h>

#define MAX_LINE 1000

void expand(char s1[], char s2[]);
void getline(char s[]);

int main()
{
    /* char input[] = "The ASCII table is A-Za-z0-9!-/:-@[-`{-~"; */
    char input[MAX_LINE];
    char output[MAX_LINE];

    printf("expand\n======\n");
    printf("> expands shorthand notation into complete list\n\n");
    expand(input, output);

    printf("Please type the input string (%d characters max): ",
           MAX_LINE); 

    getline(input);
    expand(input, output);

    printf("\n[Original string]: %s\n[Expanded string]: %s\n", input, output);
    return 0;
}

void expand(char s1[], char s2[])
{
    int i = 0, j = 0;
    char list_start, list_end;

    /* string terminator `\0` needs to be on index MAX_LINE - 1 */
    while (s1[i] != '\0' && j < MAX_LINE - 1) {

        if (i == 0 || s1[i - 1] == ' ' || s1 [i + 1] == ' ') {
            s2[j++] = s1[i++];

        } else if (s1[i - 1] != '-' && s1[i] == '-' && s1[i + 1] != '-') {

            /* "+ 1": the first character was already inserted */
            list_start = s1[i - 1] + 1;
            list_end = s1[i + 1];

            while (list_start <= list_end && j < MAX_LINE - 1) {
                /* add the next character into array */
                s2[j++] = list_start++;
            }

            /* skips over the dash and final character */
            i += 2;

        } else {
            s2[j++] = s1[i++];
        }
    }

    s2[j] = '\0';

}

void getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAX_LINE) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';

}