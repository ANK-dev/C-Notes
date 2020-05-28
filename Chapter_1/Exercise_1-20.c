#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
#define N 8             /* number of spaces equivalent to a tab */

/* detab: replaces tabs with appropriate number of spaces */

void tabToSpaces(int column_width, char string[], int length, char new_string[]);
int getline(char line[], int maxline);

main(){
    char line[MAXLINE];
    char new_line[MAXLINE];
    int len;

    printf("Waiting input... Press ^D to send EOF\n");
    while ((len = getline(line, MAXLINE)) > 0){
        tabToSpaces(N, line, len, new_line);
        printf("\n%s\n", new_line);
    }
}

int getline(char line[], int maxline){
    int c, i;

    for (i = 0; i < maxline - 1 && ((c=getchar()) != '\n') && (c != EOF); ++i){
        line[i] = c;
    }

    if (c == '\n'){
        line[i] = c;
        ++i;
    }

    line[i] = '\0';            /* terminates the input string */

    return i;
}

void tabToSpaces(int column_width, char string[], int length, char new_string[]){
    int i, j = 0;       /* i, j: indexes for string and new_string arrays, respectively */
    int tab_current_column;

    for (i = 0; i < length; ++i){

        /***********************************************************************
           The width of a tab is the difference between the current column and
           the next tabstop; this way, the relative column of a given tab     
           (tab_current_column) is the remainder of the division (%) of the   
           current absolute column (j) by the width of each tabstop (N).      
                                                                              
           In the following example, a tab is indicated by "~".               
                                                                              
           For a tab width N = 8:                                             
                                                                              
                    Column      000000000011111111112222222222333333          
                                012345678901234567890123456789012345          
                    Tabstops    |       |~~~~~~~|       |       |             
                                There is a~~~~~~tab in this sentence          
                                          ^    ^                              
                                        TAB    TAB                            
                                   COLUMN 2    COLUMN 7                       
                                                                              
         ***********************************************************************/

        tab_current_column = j % N;         /* each tabstop begins at a multiple of N columns */

        if (string[i] == '\t'){

            int k;

            for (k = 0; k < (N - tab_current_column); ++k){     /* index for tab = N spaces */

                new_string[j + k] = ' ';
            }

            j = j + k;                  /* new_string index is advanced by 'k' number of spaces */

        } else {
            new_string[j] = string[i];
            ++j;
        }

    }

    new_string[j] = '\0';       /* terminates the new_string */

}