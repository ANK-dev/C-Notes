#include <stdio.h>

#define OUT 0
#define IN 1
#define LENGTH 20
#define BAR_WIDTH 30

/* Counts the length of words and prints a histogram */

main(){
    int c, count, state, len[LENGTH], max;

    count = 0;
    state = OUT;
    max = 0;

    for(int i = 0; i < LENGTH; ++i)
        len[i] = 0;

    printf("Waiting input... Press ^D to send EOF\n");

    //Counts the length of words
    while((c = getchar()) != EOF){
        if(c != ' '){
            state = IN;
            ++count;
        } else if(c == ' ' && state == IN){
            state = OUT;
            if(count < LENGTH){
                ++len[count - 1];
            } else {
                ++len[LENGTH - 1];
            }
            count = 0;
        }
    }


    // Counts the length of the last word in the input
    state = OUT;
    if(count < LENGTH){
        ++len[count - 1];
    } else {
        ++len[LENGTH - 1];
    }

    for(int i = 0; i < LENGTH; ++i){
       if(len[i] > max){
           max = len[i];
       }
    }

    // Prints the histogram
    printf("\n\nHistogram\n");
    for(int i = 1; i <= LENGTH; ++i){
        if(i == LENGTH){
            printf("%2d+ letter words: %4d ", i, len[i - 1]);
        } else {
            printf("%2d  letter words: %4d ", i, len[i - 1]);
        }
        putchar('[');
        for(int j = 0; (j < len[i - 1] * BAR_WIDTH/max); ++j){
            putchar('=');
        }
        putchar(']');
        putchar('\n');
    }
}
