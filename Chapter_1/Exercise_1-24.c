#include <stdio.h>
#define MAXLINE 1000
#define  IN 1
#define OUT 0

/*==== Globals ==============================================================*/

int parenthesis_depth_level = 0;
int brackets_depth_level = 0;
int braces_depth_level = 0;

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
int      FOR_LOOP = OUT;

/*===========================================================================*/

int getLine(char input_line[], int maxline);

void checkParenthesis(char input_line[], int line_length);
void checkBrackets(char input_line[], int line_length);
void checkBraces(char input_line[], int line_length);
void checkQuotes(char input_line[], int line_length);
void checkEscapes(char input_line[], int line_length);
void checkComments(char input_line[], int line_length);

int insideForLoopDeclaration(char input_line[], int index);

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
        ++line_number;
    }
    
    return 0;

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
        
        /* parenthesis aren't checked if inside comment, quotes or `for` loops */
        if ( !(COMMENT || SINGLE_QUOTES || DOUBLE_QUOTES || FOR_LOOP) ) {

            switch (input_line[i]) {
                
                case ';':
                    if (PARENTHESIS == IN) {
                        printError(line_number, i + 1, 0);  /* "E00: unmatched_left_parenthesis --> ( ?" */
                    }
                    break;

                case '(':
                    if (!PARENTHESIS) {
                        PARENTHESIS = IN;
                        ++parenthesis_depth_level;
                    } else {
                        ++parenthesis_depth_level;
                    }
                    break;

                case ')':
                    if (PARENTHESIS) {
                        --parenthesis_depth_level;

                        if (parenthesis_depth_level <= 0) {
                            PARENTHESIS = OUT;
                        }

                    } else {
                        --parenthesis_depth_level;  /* if parenthesis level < 0 then it's unbalanced */
                        printError(line_number, i + 1, 1); /* "E01: unmatched_right_parenthesis --> ? )" */
                    }
                    break;
            
            }
        
        }
    
    }
}

void checkBrackets(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {
        
        /* brackets aren't checked if inside comments or quotes */
        if ( !(COMMENT || SINGLE_QUOTES || DOUBLE_QUOTES) ) {

            switch (input_line[i]) {
                
                case ';':
                    if (BRACKETS) {
                        printError(line_number, i + 1, 2); /* "E02: unmatched_left_bracket --> [ ?" */
                    }
                    break;

                case '[':
                    if (!BRACKETS) {
                        BRACKETS = IN;
                        ++brackets_depth_level;
                    } else {
                        ++brackets_depth_level;
                    }
                    break;

                case ']':
                    if (BRACKETS) {
                        --brackets_depth_level;

                        if (brackets_depth_level <= 0) {
                            BRACKETS = OUT;
                        }

                    } else {
                        --brackets_depth_level; /* if brackets level < 0 then it's unbalanced */
                        printError(line_number, i + 1, 3); /* "E03: unmatched_right_bracket --> ? ]" */
                    }
                    break;
            
            }
        
        }
    
    }
}

void checkBraces(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {

        /* braces aren't checked if inside comments or quotes */
        if ( !(COMMENT || SINGLE_QUOTES || DOUBLE_QUOTES) ) {
            
            switch (input_line[i]) {

                case '{':
                    if (!BRACES) {
                        BRACES = IN;
                        ++braces_depth_level;   /* check if it's possible to add E04! */
                    } else {
                        ++braces_depth_level;
                    }
                    break;

                case '}':
                    if (BRACES) {
                        --braces_depth_level;

                        if (braces_depth_level <= 0) {
                            BRACES = OUT;
                        }

                    } else {
                        --braces_depth_level; /* if braces level < 0 then it's unbalanced */
                        printError(line_number, i + 1, 5); /* "E05: unmatched_right_brace --> ? }" */
                    }
                    break;
            
            }
        
        }

    }
}

void checkQuotes(char input_line[], int line_length)
{
    int line_end = 0;
    int i;
    for (i = 0; i < line_length; ++i) {

        /* quotes aren't checked if inside comments or escape chars */
        if ( !(COMMENT || ESCAPE) ) {

            switch (input_line[i]) {
                
                case ';':
                    if ( !(SINGLE_QUOTES || DOUBLE_QUOTES) ) {
                        line_end = 1;
                    }
                    break;

                case '\'':
                    if (!line_end) {
                        /* flip state -> if inside quote, then outside and vice-versa */
                        SINGLE_QUOTES = !SINGLE_QUOTES;
                    } else {
                        printError(line_number, i + 1, 6); /* E06: unbalanced_single_quote --> ?'? */
                    }
                    break;
                
                case '"':
                    if (!line_end) {
                        /* flip state -> if inside quote, then outside and vice-versa */
                        DOUBLE_QUOTES = !DOUBLE_QUOTES;
                    } else {
                        printError(line_number, i + 1, 7); /* E07: unbalanced_double_quote --> ?"? */
                    }
                    break;
            
            }
        
        }
    
    }
}

void checkComments(char input_line[], int line_length)
{
    int i;
    for (i = 0; i < line_length; ++i) {
        
        /* comments aren't checked if inside quotes */
        if ( !(SINGLE_QUOTES || DOUBLE_QUOTES) ) {

            switch (input_line[i]) {

                /* 
                 *  special case: you can have as many begin-comment delimiters
                 *  as you want, but since C comments don't nest, you can only
                 *  have one end-comment delimtier
                 */
                case '/':
                    if (input_line[i + 1] == '*') {
                        COMMENT = IN;
                    }
                    break;

                case '*':
                    if (input_line[i + 1] == '/') {
                        if (COMMENT) {
                            COMMENT = OUT;
                        } else {
                            printError(line_number, i + 10, 10); /* E10: extra_right_comment_delimiter --> ?? * / */
                        }
                    }
            }
        }

    }
}

void checkEscapes(char input_line[], int line_length) {
    int i;
    for (i = 0; i < line_length; ++i) {
        
        /* escape chars aren't checked if inside comments */
        if (!COMMENT) {
            if (input_line[i++] == '\\') {
                int match = 0;
                ESCAPE = IN;

                switch (input_line[i++]) {
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
                        ESCAPE = OUT;
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

                        while (input_line[i] >= '0' && input_line[i] <= '7') {
                            ++match;
                            ++i;

                            if (match == 3) {
                                break;
                            }

                        }

                        /* no invalid sequence possible as octals can be
                        shortened by following with a non-octal digit or
                        character e.g. \2192 -> \21(octal) + 92(decimal) */

                        ESCAPE = OUT;
                        break;
                    /*-------------------------------------------------------*/

                    case 'x': /* hex byte (00-FF) */

                        while (
                                (input_line[i] >= '0' && input_line[i] <= '9') 
                             || (input_line[i] >= 'A' && input_line[i] <= 'F')
                             || (input_line[i] >= 'a' && input_line[i] <= 'f')
                        ) {
                            ++match;
                            ++i;
                        }

                        if (match != 2) {
                            /* E08: invalid_escape_sequence --> \??? */
                            printError(line_number, i + 1, 8); 
                        }

                        ESCAPE = OUT;
                        break;

                    case 'u': /* unicode code point up to FFFF hex */

                        while (
                                (input_line[i] >= '0' && input_line[i] <= '9') 
                             || (input_line[i] >= 'A' && input_line[i] <= 'F')
                             || (input_line[i] >= 'a' && input_line[i] <= 'f')
                        ) {
                            ++match;
                            ++i;

                            if (match == 4) {
                                break;
                            }

                        }

                        if (match != 4) {
                            /* E08: invalid_escape_sequence --> \??? */
                            printError(line_number, i + 1, 8); 
                        }

                        ESCAPE = OUT;
                        break;

                    case 'U': /* unicode in hex (8 hex digits) */

                        while (
                                (input_line[i] >= '0' && input_line[i] <= '9') 
                             || (input_line[i] >= 'A' && input_line[i] <= 'F')
                             || (input_line[i] >= 'a' && input_line[i] <= 'f')
                        ) {
                            ++match;
                            ++i;

                            if (match == 8) {
                                break;
                            }

                        }

                        if (match != 8) {
                            /* E08: invalid_escape_sequence --> \??? */
                            printError(line_number, i + 1, 8); 
                        }

                        ESCAPE = OUT;
                        break;

                    default:
                        printError(line_number, i + 1, 8); 
                        break;

                }

            }
        }
    }
}

void printError(int line_number, int column, int error_id)
{
    char error_type[20][50] = {\
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
           line_number, column, error_type[error_id]);
}

int insideForLoopDeclaration(char input_line[], int index)
{
    if ( !(COMMENT || SINGLE_QUOTES || DOUBLE_QUOTES) ) {
        
        int i;
        for (i = index; i > 0; --i) {
        
            if (!FOR_LOOP) {

                if ( 
                       (
                           input_line[i - 4] == 'f'
                        && input_line[i - 3] == 'o'
                        && input_line[i - 2] == 'r'
                        && input_line[i - 1] == ' '
                        && input_line[i]     == '('
                       )
                    ||  /* or */
                       (
                            input_line[i - 3] == 'f'
                        &&  input_line[i - 2] == 'o'
                        &&  input_line[i - 1] == 'r'
                        &&  input_line[i]     == '('
                       )
                   ) {
                        return FOR_LOOP = IN;
                    }

            } else if (input_line[i] == ')') {
                return FOR_LOOP = OUT;
            }
        }

        return FOR_LOOP = OUT;

    }

    return FOR_LOOP;

}