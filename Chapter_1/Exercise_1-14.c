#include <stdio.h>

#define OUT 0
#define IN 1
#define LENGTH 128          //Number of characters in the ASCII table
#define BAR_WIDTH 30

/* Counts the frequency of characters and prints a histogram */

main(){
    int c, count, state, len[LENGTH], max;

    count = 0;
    state = OUT;
    max = 0;

    for(int i = 0; i < LENGTH; ++i)
        len[i] = 0;

    printf("Waiting input... Press ^D to send EOF\n");

    //Counts the frequency of characters
    while((c = getchar()) != EOF){
        ++len[c];
    }

    for(int i = 0; i < LENGTH; ++i){
       if(len[i] > max){
           max = len[i];
       }
    }

    // Prints the histogram
    printf("\n\nHistogram\n");
    for(int i = 0; i < LENGTH; ++i){
        printf("Character %03d - %c: %4d ", i, i, len[i]);
        putchar('[');
        for(int j = 0; (j < len[i] * BAR_WIDTH/max); ++j){
            putchar('=');
        }
        putchar(']');
        putchar('\n');
    }
}
