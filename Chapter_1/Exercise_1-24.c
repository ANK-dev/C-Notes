#include <stdio.h>
#define MAXLINE 1000
#define  IN 1
#define OUT 0

/*==== Globals ==============================================================*/

int parenthesis_depth_level = 0;
int brackets_depth_level = 0;
int braces_depth_level = 0;
int is_inside_for_loop_declaration = OUT;
int is_inside_comment = OUT;
int is_inside_quote = OUT;

int line_number = 1;
/*===========================================================================*/


/*==== Program States =======================================================*/

int   PARENTHESIS = OUT;
int      BRACKETS = OUT;
int        BRACES = OUT;
int SINGLE_QUOTES = OUT;
int DOUBLE_QUOTES = OUT;
int        ESCAPE = OUT;
int       COMMENT = OUT;

/*===========================================================================*/

int getLine(char input_line[], int maxline);

void checkParenthesis(char input_line[], int line_length);
void checkBrackets(char input_line[], int line_length);
void checkBraces(char input_line[], int line_length);
void checkQuotes(char input_line[], int line_length);
void checkEscapes(char input_line[], int line_length);
void checkComments(char input_line[], int line_length);

int insideForLoopDeclaration(char input_line[], int index, int line_length);

void printError(int line_number, int column, int error_id);

/* syntax checker - checks basic syntax errors in a C source code */

int main(void)
{
    int length;
    char line[MAXLINE];
    while ((length = getLine(line, MAXLINE)) > 0) {
        checkParenthesis(line, length);
        checkBrackets(line, length);
        checkBraces(line, length);
        checkQuotes(line, length);
        checkEscapes(line, length);
        checkComments(line, length);

    }
}

int getLine(char input_line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline - 1 && ((c=getchar()) != '\n') && (c != EOF); ++i) {
        input_line[i] = c;
    }

    if (c == '\n') {
        input_line[i++] = c;
    }

    input_line[i] = '\0';            /* terminates the string */

    return i;
}

void checkParenthesis(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {

        char c = input_line[i];

        if ( !(insideComment(c) || insideQuote(c)) ) {

            if (!insideForLoopDeclaration(input_line, i, line_length)) {
                if (c == ';' && PARENTHESIS == IN){
                    printError(line_number, i + 1, 0);  /* "E00: unmatched_left_parenthesis --> ( ?" */
                }
            }

            if (c == '(') {

                if (!PARENTHESIS) {
                    PARENTHESIS = IN;
                    ++parenthesis_depth_level;
                } else {
                    ++parenthesis_depth_level;
                }

            } else if (c == ')') {

                if (PARENTHESIS) {
                    --parenthesis_depth_level;

                    if (parenthesis_depth_level <= 0) {
                        PARENTHESIS = OUT;
                    }

                } else {
                    printError(line_number, i + 1, 1);  /* "E01: unmatched_right_parenthesis --> ? )" */
                    --parenthesis_depth_level;    /* if parenthesis level < 0 then it's unbalanced */
                }

            }
        }
    }
}

void checkBrackets(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {

        char c = input_line[i];

        if ( !(insideComment(c) || insideQuote(c)) ) {

            if (!insideForLoopDeclaration(input_line, i, line_length)) {
                if (c == ';' && BRACKETS){
                    printError(line_number, i + 1, 2);  /* "E02: unmatched_left_bracket --> [ ?" */
                }
            }

            if (c == '[') {

                if (BRACKETS) {
                    BRACKETS = IN;
                    ++brackets_depth_level;
                } else {
                    ++brackets_depth_level;
                }

            } else if (c == ')') {

                if (BRACKETS) {
                    --brackets_depth_level;

                    if (brackets_depth_level <= 0) {
                        BRACKETS = OUT;
                    }

                } else {
                    printError(line_number, i + 1, 3);  /* "E03: unmatched_right_bracket --> ? ]" */
                    --brackets_depth_level;    /* if brackets level < 0 then it's unbalanced */
                }

            }
        }
    }
}

void checkBraces(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {

        char c = input_line[i];

        if ( !(insideComment(c) || insideQuote(c)) ) {

            if (!insideForLoopDeclaration(input_line, i, line_length)) {
                if (c == ';' && BRACES){
                    printError(line_number, i + 1, 4);  /* "E04: unmatched_left_brace --> { ?" */
                }
            }

            if (c == '[') {

                if (!BRACES) {
                    BRACES = IN;
                    ++braces_depth_level;
                } else {
                    ++braces_depth_level;
                }

            } else if (c == ')') {

                if (BRACES) {
                    --braces_depth_level;

                    if (braces_depth_level <= 0) {
                        BRACES = OUT;
                    }

                } else {
                    printError(line_number, i + 1, 5);  /* "E05: unmatched_right_brace --> ? }" */
                    --braces_depth_level;    /* if braces level < 0 then it's unbalanced */
                }

            }
        }
    }
}

void checkQuotes(char input_line[], int line_length)
{
    int i;
    int line_over = 0;
    for (i = 0; i < line_length; ++i) {
        char c = input_line[i];

        if (!(COMMENT || ESCAPE) ) {

            if (c == '\'') {

                if (!line_over) {
                    SINGLE_QUOTES = !SINGLE_QUOTES;
                } else {
                    printError(line_number, i + 1, 6);
                }

            } else if (c == '"') {

                if (!line_over) {
                    DOUBLE_QUOTES = !DOUBLE_QUOTES;
                } else {
                    printError(line_number, i + 1, 7);
                }

            }

            if (c == ';' && !QUOTES) {
                line_over = 1;
            }

        }
    }
}

void checkComments(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {
        char c = input_line[i];
    
        if ( !(SINGLE_QUOTES || DOUBLE_QUOTES) ) {

            if (c == '/') {
                
                if (input_line[i + 1] == '*') {
                    COMMENT = IN;
                }

            } else if (c == '*') {

                if (input_line[i + 1] == '/') {
                    if (COMMENT) {
                        COMMENT = OUT;
                    } else {
                        printError(line_number, i + 1, 10);
                    }
                    
                }

            }

        }

    }
}

void checkEscapes(char input_line[], int line_length) 
{
    int i;
    char valid_escape_sequences [17][10] = {
        "\\a", "\\b", "\\e", "\\f", "\\n", "\\r", "\\t", "\\v", "\\\\", "\\'",
        "\\\"", "\\?", "\\", "\\x", "\\u", "\\U", '\0'
    };


    for (i = 0; i < line_length; ++i) {
        char c = input_line[i];

        if (c == '\\') {

            int j;
            int match = 0;
            for (j = i + 1; j < i + 11; ++j) {

                int k;
                for (k = 0; k < 16; ++k) {

                    int h;
                    for (h = 0; h < 10; ++h) {

                        if (input_line[j]  == valid_escape_sequences[k][h]) {
                            ++match;
                            ESCAPE = IN;
                        } else {
                            ESCAPE = OUT;
                        }

                    }

                }
            }

            if (match == 0) {
                printError(line_number, i + 1, 8);
            }
            
        }
    }
}

void printError(int line_number, int column, int error_id)
{
    char error_type[20][50] = {
        "E00: unmatched_left_parenthesis --> ( ?",
        "E01: unmatched_right_parenthesis --> ? )",
        "E02: unmatched_left_bracket --> [ ?",
        "E03: unmatched_right_bracket --> ? ]",
        "E04: unmatched_left_brace --> { ?",
        "E05: unmatched_right_brace --> ? }",
        "E06: unbalanced_single_quote --> ?'?",
        "E07: unbalanced_double_quote --> ?\"?",
        "E08: invalid_escape_sequence --> \\???",
        "E09: extra_left_comment_delimiter --> /* ??",
        "E10: extra_right_comment_delimiter --> ?? */",
        '\0'
    };

    printf("Error @ line %d: column %d --- %s\n",
           line_number, column, error_type[error_id]);
}

int insideForLoopDeclaration(char input_line[], int index, int line_length)
{
    char c = input_line[index];
    if ( !(insideComment(c) || insideQuote(c)) ) {

        if (is_inside_for_loop_declaration == OUT) {

            /*
             *       +3
             *      ~~~
             *     V  V      index = 4
             *  ... for      line_length = 8
             *  ...4567
             */

            if ( (index + 3) <= (line_length - 1)  ) {
                char aux[5] = {input_line[index],
                            input_line[index + 1],
                            input_line[index + 2],
                            input_line[index + 3],
                            '\0'}

                if (aux == " for") {
                    return is_inside_for_loop_declaration = IN;
                } else {
                    return is_inside_for_loop_declaration = OUT;
                }

            } else {
                return is_inside_for_loop_declaration = OUT;
            }

        } else if (input_line[index] == ')') {
            return is_inside_for_loop_declaration = OUT;
        }

    }

}