#include <stdio.h>
#define MAX_LINE 1000
#define TAB_WIDTH 8
#define FOLD_COLUMN 100
#define MAX_WORD_LENGTH 10

/* fold - fold long input lines into two or more shorter lines */

void fold(char input_line[], int line_length, int fold_column, char output_line[]);
int getline(char line[], int maxline);

main()
{
    char line[MAX_LINE];
    char new_line[MAX_LINE];
    int len;

    printf("Waiting input... Press ^D to send EOF\n");
    while ((len = getline(line, MAX_LINE)) > 0) {
        fold(line, len, FOLD_COLUMN, new_line);
        printf("\n%s\n", new_line);
    }


}

void fold(char input_line[], int line_length, int fold_column, char output_line[])
{
    int i, j = 0;
    int current_column = 0, tab_current_column;
    int word_char_count = 0;
    int is_whitespace;

    for (i = 0; i < line_length; ++i) {
        if (input_line[i] == '\t') {
            tab_current_column = i % TAB_WIDTH;                     /* tab columns are cyclical */
            current_column += TAB_WIDTH - tab_current_column;       /* advance current column to the next tabstop */
        } else {
            ++current_column;
        }

        is_whitespace = input_line[i] == ' ' || input_line[i] == '\t' ? 1 : 0;
        word_char_count = is_whitespace ? 0 : word_char_count + 1;      /* Increment for every character of the word */

        if (current_column > fold_column && input_line[i] != EOF) {

            if (word_char_count < MAX_WORD_LENGTH) {

                i -= word_char_count - 1;   /* go back to the start of the word... */
                j -= word_char_count;       /* ...but keep i one ahead of j to... */
                                            /* ...remove blank space on next line */

            }

            output_line[j++] = '\n';                /* adds newline */
            output_line[j++] = input_line[i];       /* adds current character */

            current_column = 1;     /* the 1st character of the next line has... */
                                    /* ...already been inserted */
        } else {
            output_line[j++] = input_line[i];       /* returns j then increments value */
        }
    }

    output_line[j] = '\0';                          /* terminates the output string */

}



int getline(char line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline - 1 && ((c=getchar()) != '\n') && (c != EOF); ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i++] = c;
    }

    line[i] = '\0';            /* terminates the string */

    return i;
}