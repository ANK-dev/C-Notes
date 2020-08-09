/**
 * Exercise 3-4 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * > In a two's complement number representation, out version of `itoa` does not
 * > handle the largest negative number, that is, the value of n equal to
 * > -(2ʷᵒʳᵈˢⁱᶻᵉ⁻¹). Explain why not. Modify it to print that value correctly,
 * > regardless of the machine on which it runs.
 *
 * __ANSWER__: Since the largest _negative number_ that can be held is larger
 * than the largest _positive number_, when the program tries to invert the sign
 * of `INT_MIN` the result gets corrupted.
 *
 *******************************************************************************
 *
 *
 * itoa (fixed ver.):  convert n to characters in s
 * ------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int input = INT_MIN;
    char output[20];

    printf("itoa\n====\n");
    printf("> convert n to characters in s\n\n");

    printf("input is %d\n", input);

    itoa(input, output);

    printf("output is %s\n", output);


    return 0;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i; 
    int sign = (n < 0) ? -1 : 1;

    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = sign * (n % 10) + '0';   /* get next digit and correct sign */
    } while ((n /= 10) != 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
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