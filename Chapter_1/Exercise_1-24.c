/**
 * Exercise 1-24 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * syntax checker - checks C source code for basic syntax errors
 * -------------------------------------------------------------
 * 
 * This exercise uses a lot of global variables, which is definitely **NOT**
 * ideal, but since pointers haven't been introduced in this chapter yet,
 * there's no better alternative.
 *
 * It can also seen like a bit of a cheat, but the use of `switch` statements
 * made this exercise much easier to wrap my head around. If strict compliance
 * to the book's order of introduction of structures is desired, they can be
 * easily substituted by `if/else` structures, with the only downside being
 * longer/more complex code.
 *
 * Run this program using input redirection: `$ ./a.out < sourcecode.c`
 */

#include <stdio.h>

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0

/*==== Global Variables =====================================================*/

int c; /* input stream character */

int PAREN_DEPTH_LVL = 0;
int BRACK_DEPTH_LVL = 0;
int BRACE_DEPTH_LVL = 0;

int LINE_NUMBER     = 1;
int COLUMN_NUMBER   = 1;
int LINE_END        = FALSE;
int ERR_NUMBER      = 0;

/*==== Program States =======================================================*/

int PAREN    = FALSE;
int BRACK    = FALSE;
int BRACE    = FALSE;
int S_QUOTE  = FALSE;
int D_QUOTE  = FALSE;
int ESCAPE   = FALSE;
int COMMENT  = FALSE;
int FOR_LOOP = FALSE;

/*==== Function Prototypes ==================================================*/

/*---- Error Checking -------------------------------------------------------*/
void chkForLoop();
void chkParen();
void chkBrack();
void chkBrace();
void chkQuote();
void chkEscape();
void chkComment();

/*---- Error Printing -------------------------------------------------------*/
void printError(int line_number, int column_number, int error_id);

/*===========================================================================*/

int main()
{
    printf("==== SYNTAX CHECKER ====================================\n\n");
    while( (c = getchar()) != EOF ) {
        chkForLoop();
        chkParen();
        chkBrack();
        chkBrace();
        chkQuote();
        chkEscape();
        chkComment();
        ++COLUMN_NUMBER;
        if (c == '\n') {
            ++LINE_NUMBER;
            COLUMN_NUMBER = 1;
            LINE_END = FALSE;
        }
    }

    if (ERR_NUMBER == 0) {
        printf("\n==== END OF ANALYSIS: NO ERRORS FOUND ==================\n");
    } else if (ERR_NUMBER == 1){
        printf("\n==== END OF ANALYSIS: %3d ERROR FOUND ==================\n",
               ERR_NUMBER);
    } else {
        printf("\n==== END OF ANALYSIS: %3d ERRORS FOUND =================\n",
               ERR_NUMBER);
    }

    return 0;
}

void chkForLoop()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE) ) {


        /* get the next 4 characters, check, and put them back into stdin */
        if (!FOR_LOOP) {
            /* i = 1, the first character is nextbuffer[0] = c */
            int i = 1, nextbuffer[5];
            nextbuffer[0] = c;

            /* get the rest of the characters */
            while(i < 5) {
                nextbuffer[i++] = getchar();
            }

            /* put characters back into stdin and check only the buffer */
            while(i > 1) {
                ungetc(nextbuffer[--i], stdin);
            }

            if (
                (
                    nextbuffer[0] == 'f'
                 && nextbuffer[1] == 'o'
                 && nextbuffer[2] == 'r'
                 && nextbuffer[3] == ' '
                 && nextbuffer[4] == '('
                )
                ||
                (
                    nextbuffer[0] == 'f'
                 && nextbuffer[1] == 'o'
                 && nextbuffer[2] == 'r'
                 && nextbuffer[3] == '('
                )
            ) {
                FOR_LOOP = TRUE;
            }

        } else if (c == ')' && PAREN_DEPTH_LVL == 1) {
            FOR_LOOP = FALSE;
        }
    }
}

void chkParen()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE) ) {
        switch (c) {
            
            /* ';' are not allowed in parenthesis except in `for` loop
            statements */
            case ';':
                if (PAREN && !FOR_LOOP) {
                    /* E00: unmatched_left_parenthesis --> ( ? */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 0);
                }
                break;

            case '(':
                ++PAREN_DEPTH_LVL;
                if (PAREN_DEPTH_LVL > 0) {
                    PAREN = TRUE;
                }
                break;

            case ')':
                --PAREN_DEPTH_LVL;
                if (PAREN_DEPTH_LVL == 0) {
                    PAREN = FALSE;
                } else if (PAREN_DEPTH_LVL < 0) {
                    /* E01: unmatched_right_parenthesis --> ? ) */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 1);
                }
                break;
        }
    }
}

void chkBrack()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE) ) {
        switch(c) {
            case ';':
                if (BRACK) {
                    /* E02: unmatched_left_bracket --> [ ? */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 2);
                }
                break;
            case '[':
                ++BRACK_DEPTH_LVL;
                if (BRACK_DEPTH_LVL > 0) {
                    BRACK = TRUE;
                }
                break;
            case ']':
                --BRACK_DEPTH_LVL;
                if (BRACK_DEPTH_LVL == 0) {
                    BRACK = FALSE;
                } else if (BRACK_DEPTH_LVL < 0) {
                    /* E03: unmatched_right_bracket --> ? ] */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 3);
                }
                break;
        }
    }
}

void chkBrace()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE) ) {
        switch (c) {
            case '{':
                ++BRACE_DEPTH_LVL;
                if (BRACE_DEPTH_LVL > 0) {
                    BRACE = TRUE;
                }
                break;
            case '}':
                --BRACE_DEPTH_LVL;
                if (BRACE_DEPTH_LVL == 0) {
                    BRACE = FALSE;
                } else if (BRACE_DEPTH_LVL < 0) {
                    /* E05: unmatched_right_brace --> ? } */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 5);
                }
                break;
        }
    }
}

void chkQuote()
{
    if ( !(COMMENT || ESCAPE) ) {
        switch (c) {
            /* if a ';' is found, no more quotes are allowed (except in `for`
            loops or inside quotes) */
            case ';':
                if ( !(S_QUOTE || D_QUOTE || FOR_LOOP) ) {
                    LINE_END = 1;
                }
                break;
            case '\'':
                if ( !(LINE_END || D_QUOTE) ) {
                    /* if inside quote, go outside quote and vice-versa */
                    S_QUOTE = !S_QUOTE;
                } else if (LINE_END) {
                    /* E06: unbalanced_single_quote --> ?'? */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 6);
                }
                break;
            case '"':
                if ( !(LINE_END || S_QUOTE) ) {
                    /* ditto */
                    D_QUOTE = !D_QUOTE;
                } else if (LINE_END) {
                    /* E07: unbalanced_double_quote --> ?"? */
                    printError(LINE_NUMBER, COLUMN_NUMBER, 7);
                }
                break;
        }
    }
}

void chkEscape()
{

    if (!COMMENT) {
        if (c == '\\') {
            int match = 0;
            char next;
            ESCAPE = TRUE;
            next = getchar();

            switch (next) {
                case  'a':  /* alert bell */
                case  'b':  /* backspace */
                case  'f':  /* page break */
                case  'n':  /* newline */
                case  'r':  /* carriage return */
                case  't':  /* horizontal tab */
                case  'v':  /* vertical tab */
                case '\\':  /* backspace */
                case '\'':  /* single quote */
                case  '"':  /* double quote */
                case  '?':  /* question mark */
                    ESCAPE = FALSE;
                    break;

                /*-------------- octal byte case (0 - 377) --------------*/
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':

                    while (c >= '0' && c <= '7') {
                        ++match;
                        next = getchar();

                        if (match == 3) {
                            break;
                        }

                    }

                    /* no invalid sequence possible as octals can be
                    shortened by following with a non-octal digit or
                    character e.g. \2192 -> \21(octal) + 92(decimal) */

                    /* unget final char as it isn't part of the escape seq. */
                    ungetc(next, stdin);
                    c = next;

                    ESCAPE = FALSE;
                    break;
                /*-------------------------------------------------------*/

                 case 'x': /* hex byte (00-FF) */

                    while (
                              (c >= '0' && c <= '9')
                           || (c >= 'A' && c <= 'F')
                           || (c >= 'a' && c <= 'f')
                    ) {
                        ++match;
                        next = getchar();
                    }

                    if (match != 2) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER - match, 8);
                    }

                    ungetc(next, stdin);
                    c = next;

                    ESCAPE = FALSE;
                    break;

                 case 'u': /* unicode code point up to FFFF hex */

                    while (
                              (c >= '0' && c <= '9')
                           || (c >= 'A' && c <= 'F')
                           || (c >= 'a' && c <= 'f')
                    ) {
                        ++match;
                        next = getchar();

                        if (match == 4) {
                            break;
                        }

                    }

                    if (match != 4) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER - match, 8);
                    }

                    ungetc(next, stdin);
                    c = next;

                    ESCAPE = FALSE;
                    break;

                case 'U': /* unicode in hex (8 hex digits) */

                    while (
                              (c >= '0' && c <= '9')
                           || (c >= 'A' && c <= 'F')
                           || (c >= 'a' && c <= 'f')
                    ) {
                        ++match;
                        next = getchar();

                        if (match == 8) {
                            break;
                        }

                    }

                    if (match != 8) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER - match, 8);
                    }

                    ungetc(next, stdin);
                    c = next;

                    ESCAPE = FALSE;
                    break;

                default:
                    ESCAPE = FALSE;
                    /* E08: invalid_escape_sequence --> \??? */
                    printError(LINE_NUMBER, COLUMN_NUMBER - 1, 8);
                    ungetc(next, stdin);
                    break;
            }

        }
    }
}

void chkComment()
{
    if ( !(S_QUOTE || D_QUOTE) ) {
        switch(c) {
            /**
             *  special case: you can have as many begin-comment delimiters
             *  as you want, but since C comments don't nest, you can only
             *  have one end-comment delimtier
             */
            case '/': {
                int aux = getchar();
                ungetc(aux, stdin);
                if (aux == '*') {
                    COMMENT = TRUE;
                }
                break;
            }

            case '*': {
                int aux = getchar();
                ungetc(aux, stdin);
                if (aux == '/') {
                    if (COMMENT) {
                        COMMENT = FALSE;
                    } else {
                        /* E10: extra_right_comment_delimiter --> ?? * / */
                        printError(LINE_NUMBER, COLUMN_NUMBER, 10); 
                    }
                }
                break;
            }
        }
    }
}

void printError(int line_number, int column_number, int error_id)
{
    char error_description[20][50] = {\
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
        "E10: extra_right_comment_delimiter --> ?? */"
    };

    printf("* Error @ line %d: column %d --- %s\n",
           line_number, column_number, error_description[error_id]);
    ++ERR_NUMBER;
}