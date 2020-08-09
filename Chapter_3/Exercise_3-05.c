/**
 * Exercise 3-5 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * itob:  converts n to base b in string s
 * ---------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 20

void itob(int n, char s[], int b);
void reverse(char s[]);
char *getline(char s[]);

int main()
{
    int number_input;
    int number_base;
    char input[MAX_LINE];
    char output[MAX_LINE];

    printf("itob\n====\n");
    printf("> converts n to base b in string s\n\n");

    printf("Please type the input number (base 10): ");
    number_input = atoi(getline(input));

    do {
        printf("Please type the output base (>= 2): ");

        /* number_base == 0 is allowed otherwise EOF (CTRL+D) gets stuck */
    } while ( (number_base = atoi(getline(input))) < 2 && number_base != 0);
    

    printf("\ninput is %d (base 10)\n", number_input);

    itob(number_input, output, number_base);
    printf("output is %s (base %d)\n", output, number_base);
    return 0;
}

/* itob:  converts n to base b in string s */
void itob(int n, char s[], int b)
{
    int i;
    int sign = (n < 0) ? -1 : 1;

    /* do not process if base is < 2 */
    if (b < 2) return;

    i = 0;
    do {       /* generate digits in reverse order */
        if (b > 10 && n % b > 9) {
            /* use letters for digits beyond 9 */
            s[i++] = sign * (n % b) - 10 + 'A';
        } else {
            s[i++] = sign * (n % b) + '0';
        }
    } while ((n /= b) != 0);     /* delete it */

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

char *getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAX_LINE) s[i++] = c;
    }

    if (c == EOF) putchar('\n');

    s[i] = '\0';

    return s;
}