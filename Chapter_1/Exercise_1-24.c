#include <stdio.h>

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0

/*==== Global Variables =====================================================*/
int c; /* input stream character */

int PAREN_DEPTH_LVL = 0;
int BRACK_DEPTH_LVL = 0;
int BRACE_DEPTH_LVL = 0;

int LINE_NUMBER = 1;
int COLUMN_NUMBER = 1;
int LINE_END    = FALSE;

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
    printf("End of file");
    return 0;
}

void chkForLoop()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE) ) {
        /* i = 1, the first character was already gotten */
        int i = 1, auxbuffer[5];

        auxbuffer[0] = c;

        /* get the next 4 characters, check, and put them back into stdin */
        if (!FOR_LOOP) {
            /* check EOF or not? */
            while(i < 5) {
                auxbuffer[i++] = getchar();
            }

            /* put characters back into stream and check only the buffer */
            while(i > 1) {
                ungetc(auxbuffer[--i], stdin);
            }

            if (
                (
                    auxbuffer[0] == 'f'
                 && auxbuffer[1] == 'o'
                 && auxbuffer[2] == 'r'
                 && auxbuffer[3] == ' '
                 && auxbuffer[4] == '('
                )
                ||
                (
                    auxbuffer[0] == 'f'
                 && auxbuffer[1] == 'o'
                 && auxbuffer[2] == 'r'
                 && auxbuffer[3] == '('
                )
            ) {
                FOR_LOOP = TRUE;
            }

        } else if (c == ')') {
            FOR_LOOP = FALSE;
        }
    }
}

void chkParen()
{
    if ( !(COMMENT || S_QUOTE || D_QUOTE || FOR_LOOP) ) {
        switch (c) {
            case ';':
                if (PAREN) {
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
            case ';':
                if ( !(S_QUOTE || D_QUOTE) ) {
                    LINE_END = 1;
                }
                break;
            case '\'':
                if (!LINE_END) {
                    S_QUOTE = !S_QUOTE;
                } else {
                    printError(LINE_NUMBER, COLUMN_NUMBER, 6);
                }
                break;
            case '"':
                if (!LINE_END) {
                    D_QUOTE = !D_QUOTE;
                } else {
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
            ESCAPE = TRUE;
            c = getchar();

            switch (c) {
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
                        c = getchar();

                        if (match == 3) {
                            break;
                        }

                    }

                    /* no invalid sequence possible as octals can be
                    shortened by following with a non-octal digit or
                    character e.g. \2192 -> \21(octal) + 92(decimal) */

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
                        c = getchar();
                    }

                    if (match != 2) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER, 8); 
                    }

                    ESCAPE = FALSE;
                    break;
                
                 case 'u': /* unicode code point up to FFFF hex */

                    while (
                              (c >= '0' && c <= '9') 
                           || (c >= 'A' && c <= 'F')
                           || (c >= 'a' && c <= 'f')
                    ) {
                        ++match;
                        c = getchar();

                        if (match == 4) {
                            break;
                        }

                    }

                    if (match != 4) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER, 8); 
                    }

                    ESCAPE = FALSE;
                    break;
               
                case 'U': /* unicode in hex (8 hex digits) */

                    while (
                              (c >= '0' && c <= '9') 
                           || (c >= 'A' && c <= 'F')
                           || (c >= 'a' && c <= 'f')
                    ) {
                        ++match;
                        c = getchar();

                        if (match == 8) {
                            break;
                        }

                    }

                    if (match != 8) {
                        /* E08: invalid_escape_sequence --> \??? */
                        printError(LINE_NUMBER, COLUMN_NUMBER, 8); 
                    }

                    ESCAPE = FALSE;
                    break;

                default:
                    ESCAPE = FALSE;
                    printError(LINE_NUMBER, COLUMN_NUMBER, 8); 
                    break;
            }

        }
    }
}

void chkComment()
{
    if ( !(S_QUOTE || D_QUOTE) ) {
        switch(c) {
            /* 
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
                        printError(LINE_NUMBER, COLUMN_NUMBER, 10); /* E10: extra_right_comment_delimiter --> ?? * / */
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
        "E00: unmatched_left_parenthesis --> ( ?",\
        "E01: unmatched_right_parenthesis --> ? )",\
        "E02: unmatched_left_bracket --> [ ?",\
        "E03: unmatched_right_bracket --> ? ]",\
        "E04: unmatched_left_brace --> { ?",\
        "E05: unmatched_right_brace --> ? }",\
        "E06: unbalanced_single_quote --> ?'?",\
        "E07: unbalanced_double_quote --> ?\"?",\
        "E08: invalid_escape_sequence --> \\???",\
        "E09: extra_left_comment_delimiter --> /* ??",\
        "E10: extra_right_comment_delimiter --> ?? */"\
    };

    printf("Error @ line %d: column %d --- %s\n",
        line_number, column_number, error_description[error_id]);   
}