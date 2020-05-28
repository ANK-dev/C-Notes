#include <stdio.h>

/* copies input to output, making tabs, backspaces, and backlashes visible */

main(){
    int c;

    printf("Waiting input... Press ^D to send EOF\n");
    while((c = getchar()) != EOF){
        if(c == '\t'){
            putchar('\\');
            putchar('t');
        } else if(c == '\b'){
            putchar('\\');
            putchar('b');
        } else if(c == '\\'){
            putchar('\\');
            putchar('\\');
        } else {
            putchar(c);
        }
    }
}
