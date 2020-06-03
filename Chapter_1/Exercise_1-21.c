#include <stdio.h>
#define MAXLINE 1000
#define N 8

/* entab - replaces strings of blanks by the appropriate number of tabs and
spaces */

int getline(char line[], int maxline);
int spacesToTab(int column_width, char string[], int length, char new_string[]);

main() {
    char line[MAXLINE];
    char new_line[MAXLINE];
    int len;

    printf("Waiting input... Press ^D to send EOF\n");
    while ((len = getline(line, MAXLINE)) > 0) {
        spacesToTab(N, line, len, new_line);
        printf("\n%s\n", new_line);
    }

    return 0;
}

int getline(char line[], int maxline) {
    int c, i;

    for (i = 0; i < maxline - 1 && ((c=getchar()) != '\n') && (c != EOF); ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';            /* terminates the input string */

    return i;
}

int spacesToTab(int column_width, char string[], int length, char new_string[]) {
    int i, j = 0;   /* i, j: indexes for string and new_string arrays, respectively */
    int number_of_spaces = 0;
    int tab_current_column;

    for (i = 0; i < length; ++i) {

        if (string[i] == ' ') {

            ++number_of_spaces;
            tab_current_column = (i + 1) % N;

            if (tab_current_column == 0) {
                if (number_of_spaces != 1) {
                    new_string[j] ='\t';        /* if the number of spaces can reach the next tabstop, insert a tab... */
                    number_of_spaces = 0;
                    ++j;
                } else {
                    new_string[j] = ' ';        /* if only 1 space is needed to reach the next tabstop, insert a space */
                    number_of_spaces = 0;
                    ++j;
                }
            }

        } else if (string[i] != ' ' && number_of_spaces != 0) {
            int k;

            for (k = 0; k < number_of_spaces; ++k) {     
                new_string[j] = ' ';        /* ...else, insert missing spaces... */
                ++j;
            }

            new_string[j] = string[i];      /* ...and the current character */
            number_of_spaces = 0;
            ++j;

        } else {
            new_string[j] = string[i];
            number_of_spaces = 0;
            ++j;
        }

    }

    new_string[j] = '\0';   /* terminates the new_string */
}