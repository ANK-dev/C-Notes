#include <stdio.h>

/* prints input one word per line */

main(){
    int c;

    printf("Waiting input... Press ^D for EOL\n");
    while((c = getchar()) != EOF){
        if(c == ' '){
            putchar('\n');
        } else {
            putchar(c);
        }
    }
}
