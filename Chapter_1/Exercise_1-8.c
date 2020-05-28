#include <stdio.h>

/* count blanks, tabs and newlines in input */

main(){
    int c, bl, tab, nl;

    bl = 0, tab = 0, nl = 0;
    printf("Waiting input... Press ^D to send EOF\n");
    while((c = getchar()) != EOF)
        if(c == ' ')
            ++bl;
        else if(c == '\t')
            ++tab;
        else if(c == '\n')
            ++nl;
    printf("Blanks: %d, Tabs, %d, Newlines: %d\n", bl, tab, nl);
}

