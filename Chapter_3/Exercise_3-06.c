/**
 * Exercise 3-6 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * itoa (3 args ver.):  convert n to characters in s
 * -------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <limits.h>

#define MAX_LINE 50
#define PADDING 15

void itoa(int n, char s[], int min_width);
void reverse(char s[]);

int main()
{
    int input = INT_MIN;
    char output[MAX_LINE];

    printf("itoa\n====\n");
    printf("> convert n to characters in s\n\n");

    printf("Min. output width (padding) = %d\n\n",
           PADDING < MAX_LINE ? PADDING : MAX_LINE);

    printf("input is %d\n", input);

    itoa(input, output, PADDING);
    printf("output is %s\n", output);

    return 0;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int min_width)
{
    int i; 
    int sign = (n < 0) ? -1 : 1;

    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = sign * (n % 10) + '0';   /* get next digit and correct sign */
    } while ((n /= 10) != 0);     /* delete it */
    
    if (sign < 0)
        s[i++] = '-';
    
    while (i < min_width && i < MAX_LINE) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}