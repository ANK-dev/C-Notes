#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
void reverse(int length, char string[], char revstring[]);

/* Reverses an input string, one line at a time */
main(){
    char line[MAXLINE];     /* current input line */
    int len;            /* length of current line */

    while ((len = getline(line, MAXLINE)) > 0) {
        char rline[len + 1];        /* one more to fit '\0' character */
        reverse(len, line, rline);
        printf("\n%s\n", rline);
    }

    return 0;
}

/* getline: read a line into s, return length */
int getline(char line[], int maxline){
    int c, i;

    for(i = 0; i < maxline - 1 && ((c=getchar()) != '\n') && (c != EOF); ++i){
        line[i] = c;
    }

    if(c == '\n'){
        line[i] = c;
        ++i;
    }

    line[i] = '\0';            /* terminates the input string */

    return i;
}

/* reverse: reverses an input string of given length */
void reverse(int length, char string[], char revstring[]){
    int i = length - 1, j = 0;

    while(i >= 0){
        revstring[j] = string[i];
        --i;
        ++j;
    }

    revstring[j] = '\0';        /* terminates the reversed string */

}
