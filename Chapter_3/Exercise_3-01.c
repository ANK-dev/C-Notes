/**
 * Exercise 3-1 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1]
 * ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 3
#define ARRAY_LENGTH 10

int binsearch(int x, int v[], int n);
int binsearchNew(int x, int v[], int n);
char *getline(char s[]);

int main()
{
    int num_array[] = {13, 15, 29, 32, 38, 40, 41, 49, 78, 89};
    int target, res_pos;
    char input[MAX_DIGITS + 1];

    printf("binsearch\n=========\n");
    printf("> find x in v[0] <= v[1] <= ... <= v[n-1] \n\n");

    printf("Please type the target number to be found (%d digits max): ",
           MAX_DIGITS); 

    target = atoi(getline(input));

    printf("binsearch (default) \t- Result: ");
    res_pos = binsearch(target, num_array, ARRAY_LENGTH);
    if (res_pos == -1) {
        printf("%d not found in array\n", target);
    } else {
        printf("Found %d in array at position %d\n", target, res_pos);
    }
    
    printf("binsearch (new) \t- Result: ");
    res_pos = binsearchNew(target, num_array, ARRAY_LENGTH);
    if (res_pos == -1) {
        printf("%d not found in array\n", target);
    } else {
        printf("Found %d in array at position %d\n", target, res_pos);
    }
    
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else      /* found match */
            return mid;
    }
    return -1;    /* no match */
}

int binsearchNew(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low+high) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return (x == v[low]) ? low : - 1;
}

char *getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i < MAX_DIGITS) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';

    return s;
}