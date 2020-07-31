/**
 * Exercise 2-3 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * htoi:  converts string of hex digits into its equivalent integer value
 * ----------------------------------------------------------------------
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 11
#define MAXDIGITS MAXLINE - 3

int htoi(char s[]);
int getline(char s[]);

int main() 
{
    char hex_string[MAXLINE];
    printf("hex-to-int\n==========\n\n");
    while (getline(hex_string) > 0) {
        printf("The equivalent decimal integer is: %d\n\n", htoi(hex_string));
    }
    return 0;

}

int htoi(char s[])
{
    int i, end, n = 0;

    /* skips 0x if it exists */
    i = s[0] == '0' && tolower(s[1]) == 'x' ? 2 : 0;
    
    /* end of the string after 8 hex digits -- skipping `0x` */
    end = MAXDIGITS + i;
    for (; isxdigit(s[i]) && i < end; ++i) {
    
        if (isdigit(s[i])) {
            n = 16 * n + (s[i] - '0');
        } else {
            n = 16 * n + (tolower(s[i]) - 'a' + 10);
        }
        
    }

    return n;

}

int getline(char s[])
{
    int c, i = 0;

    printf("Type a hex number, only the first %d digits will be considered: ",
           MAXDIGITS);

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAXLINE - 1) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';
    return i;
}