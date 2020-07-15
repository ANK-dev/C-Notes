/**
 * Exercise 2-2 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * write a loop equivalent to the `for` loop above without using `&&` or `||`
 * --------------------------------------------------------------------------
 */

#include <stdio.h>
#define MAX 1000

int main() 
{
    int i = 0, c;
    int lim = MAX - 1;
    char s[MAX];
    while (i < lim - 1) {
            
        if ( ( c = getchar() ) != '\n') {
            
            if (c != EOF) {
                s[i++] = c;
            } else {
                break;
            }

        } else {
            break;
        }

    }

    s[i] = '\0';

    printf("%s\n", s);

    return 0;

}
