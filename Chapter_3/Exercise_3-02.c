/**
 * Exercise 3-2 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * escape:  converts whitespace into visible characters 
 * ----------------------------------------------------
 * 
 * unescape:  converts visible characters into whitespace
 * ------------------------------------------------------
 */

#include <stdio.h>

#define MAX_LINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char s[MAX_LINE];
    char test0[] = "this is a \n test\t string!";
    char test1[] = "this is a \\n test\\t string!";

    printf("Escape\n======\n");
    printf("> converts whitespace into visible characters\n\n");
    printf("[Original string]: %s\n", test0);
    escape(s, test0);
    printf("[Escaped  string]: %s\n\n", s);

    printf("Unescape\n========\n");
    printf("> converts visible characters into whitespace\n\n");
    printf("[Original  string]: %s\n", test1);
    unescape(s, test1);
    printf("[Unescaped string]: %s\n\n", s);
    return 0;
}

void escape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i] != '\0') {
        switch (t[i]) { 
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                i++;
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                i++;
                break;
            default:
                s[j++] = t[i++];
                break;
            }
    }

    s[j] = '\0';

}

void unescape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i] != '\0') {
        if (t[i] == '\\') {
            switch (t[++i]) { 
                case 'n':
                    s[j++] = '\n';
                    i++;
                    break;
                case 't':
                    s[j++] = '\t';
                    i++;
                    break;
                default:
                    s[j++] = t[i++];
                    break;
                }
        } else {
            s[j++] = t[i++];
        }
    }

    s[j] = '\0';

}