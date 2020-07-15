/**
 * Exercise 2-4 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * squeeze alt. version:  delete all s2 characters from s1
 * -------------------------------------------------------
 */

#include <stdio.h>
#define MAXLINE 1000

void squeeze(char s1[], char s2[]);
void getline(char s[]);

int main()
{
    char string1[MAXLINE], string2[MAXLINE];
    
    printf("squeeze alt. version\n====================\n\n");
    printf("> All the characters from the 1st string that match the characters "
           "from the 2nd string will be removed!\n\n");
    printf("Type the 1st string: ");
    getline(string1);
    printf("Type the 2nd string: ");
    getline(string2);
    squeeze(string1, string2);
    printf("\nThe resulting string is: %s\n", string1);
    return 0;
}

void squeeze(char s1[], char s2[])
{
  int i, j, k, found;

  for (i = j = 0; s1[i] != '\0'; i++) {
    found = 0;
     
    for (k = 0; s2[k] != '\0'; k++) {
        if (s1[i] == s2[k]) {
            found = 1;
            break;
        }
    }
      
    if (!found) s1[j++] = s1[i];

  }
  
  s1[j] = '\0';

}

void getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAXLINE - 1) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';
}