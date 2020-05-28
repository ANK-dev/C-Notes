#include <stdio.h>

/* copies input to output, replacing multiple spaces by a single one */

main(){
    int c, bl = 0;

    printf("Waiting input... Press ^D to send EOF\n");
    while((c = getchar()) != EOF){
        if(c == ' '){
            ++bl;
            if(bl == 1){
                putchar(c);
            }
        } else {
            bl = 0;
            putchar(c);
        }
    }
}
