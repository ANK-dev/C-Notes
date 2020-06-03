#include <stdio.h>
#define YES 1
#define  NO 0

int inside_comment = NO;
int inside_quote = NO;

int c;
int inQuote(void);
int inComment(void);

/* removecomments - removes all ANSI C-formated comments from an input
 text stream (`//`-style comments are not supported) */

/* call this program with redirected input: `./a.out < source_code.c` */

/* TEST - "These are 'single quotes' inside a double quote" and 'single quotes'
   beside a double quote in a multiline comment */

main()
{
    /**************************************************************************
    *  simple test for comments delimiters within strings, the `test`         *
    *  string should be preserved within its entirety, unlike this comment    *
    *  and others, which should completely disappear!                        */

    char test[] = "this is a test string with a /* comment within a string */ "
                  "and \"these are 'single quotes' inside a double quote\" "
                  "and 'single quotes' beside it.\n";

    /*************************************************************************/

    while ( (c = getchar()) != EOF) {

        inside_comment = inComment();      /* check if inside comment */
        inside_quote = inQuote();          /* check if inside quote */

        /* if `c` is NOT inside a comment, output it; otherwise, supress it */
        if ( !inside_comment ) {
            putchar(c);
        }

    }

    return 0;
}

/*---- Quote Rules ------------------------------------------------------------
*   if a quote is  INside a comment, it CAN'T be displayed
*   if a quote is OUTside a comment, it CAN   be displayed
*----------------------------------------------------------------------------*/

int inQuote(void)
{
    if (!inside_comment) {    /* if not inside a comment, quotes can be
                              displayed */

        if (c == '\'' || c == '"') {    /* if a quote char is found, then... */

            /* ...if inside quote, then not inside
            quote anymore and vice-versa. */
            return inside_quote = !inside_quote;

        } else {
            return inside_quote;    /* ...else keep inside/outside quote. */
        }

    } else {
        return inside_quote;    /* ...else keep inside/outside quote. */
    }
}

/*---- Comment Rules ----------------------------------------------------------
*   if a comment is  INside a quote, it CAN   be displayed
*   if a comment is OUTside a quote, it CAN'T be displayed
*----------------------------------------------------------------------------*/

int inComment(void)
{
    if (!inside_quote) {    /* if not inside a quote, comments can be
                            suppressed */

/*---- check commment beginning delimiter -----------------------------------*/

        if (c == '/') {     /* if a slash char is found,... */
            c = getchar();  /* ...check next character and... */

            if (c == '*') {     /* ...if it's a star,... */
                return inside_comment = YES;    /* ...set inside comment... */
            } else {
                return inside_comment;  /* ...else, keep inside/outside
                                        comment. */
            }

/*---- check comment ending delimiter ---------------------------------------*/

        } else if (c == '*') {
            c = getchar();

            if (c == '/') {
                c = getchar();      /* skip final slash of comment */
                return inside_comment = NO;
            } else {
                return inside_comment;
            }

        } else {
            return inside_comment;
        }

/*---------------------------------------------------------------------------*/

    } else {
        return inside_comment;  /* ...else, keep inside/outside comment. */
    }

}