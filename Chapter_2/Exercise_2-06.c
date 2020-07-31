/**
 * Exercise 2-6 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * setbits:  returns an `x` int with `n` bits at position `p` set to the
 *           rightmost `n` bits of an `y` int
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INT_BIN_SIZE 32
#define INT_HEX_SIZE INT_BIN_SIZE / 4
#define PREFIX 2
#define PADDING 7
#define HEX_STRING_LEN (INT_HEX_SIZE + PREFIX)
#define BIN_STRING_LEN (INT_BIN_SIZE + PREFIX)

unsigned setbits(unsigned int x, int p, int n, unsigned int y);
char *decToBin(unsigned int dec, char bin[]);
int validateInput(char in[]);
char *getline(char s[]);
int stringToInt(char in[], int in_type, int var);

int main()
{
    char output[INT_BIN_SIZE + PADDING + 1];
    char input[BIN_STRING_LEN + 1];
    int input_type, p, n;
    unsigned int x = 0, y = 0, result;
    
    printf("setbits\n=======\n\n");
    printf("> returns an `x` int with `n` bits at position `p` set to the "
           "rightmost `n` bits of an `y` int\n\n");
    
    /* get the `x` variable */
    do {
        printf("Type the \"x\" variable\n(0b for binary + %d digits, "
            "0x for hexadecimal + %d digits): ", INT_BIN_SIZE, INT_HEX_SIZE);
    } while (( input_type = validateInput(getline(input)) ) == 0);
    
    x = stringToInt(input, input_type, x);

    /* get the `y` variable */
    do {
        printf("\nType the \"y\" variable\n(0b for binary + %d digits, "
            "0x for hexadecimal + %d digits): ", INT_BIN_SIZE, INT_HEX_SIZE);
    } while (( input_type = validateInput(getline(input)) ) == 0);
    
    y = stringToInt(input, input_type, y);

    /* get the `p` index of `x` */
    do {
        printf("\nType the position \"p\" (0...%d): ", INT_BIN_SIZE - 1);
    } while ( ( p = atoi(getline(input)) ) < 0 || p > INT_BIN_SIZE - 1);

    /* get the `n` number of bits to replace from `x` */
    do {
        printf("\nType the number of bits \"n\" (0...%d): ", p + 1);
    } while ( ( n = atoi(getline(input)) ) < 0 || n > p + 1);

    /* calculation happens here */
    result = setbits(x, p, n, y);

    /* displays input and output nicely formated */
    printf("\nx:\tHex: %X\n\tBin: %s\n\n", x, decToBin(x, output));
    printf("y:\tHex: %X\n\tBin: %s\n\n", y, decToBin(y, output));
    printf("Result:\tHex: %X\n\tBin: %s\n", result, decToBin(result, output));
    return 0;
}

/* this is the function required by the exercise */
unsigned setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int x_mask = ~0 << (p + 1) | ~(~0 << (p - n + 1));
    unsigned int y_mask = ~(~0 << n);
    y = (y & y_mask) << (p - n + 1);
    x = x & x_mask;
    return x | y;
}

/* converts an integer into a binary string; returns pointer to resulting array 
 */
char *decToBin(unsigned int dec, char bin[])
{
    int p;
    for (p = INT_BIN_SIZE + PADDING; p >= 0; --p) {
        /* every 5th char should be a space */
        if ( (p + 1) % 5 == 0) bin[p--] = ' ';
        bin[p] = dec % 2 + '0';
        dec /= 2;
    }
    return bin;
}

/* gets input from user; returns pointer to resulting array */
char *getline(char s[])
{
    int c, i = 0;

    while ( (c = getchar()) != EOF && c != '\n' ) {
        if (i <= BIN_STRING_LEN) s[i++] = c;
    }

    if (c == EOF) putchar('\n');
    
    s[i] = '\0';

    return s;
}

/* determines if the input string is in hex or binary format */
int validateInput(char in[])
{
    if (in[0] == '0') {

        if (in[1] == 'x' || in[1] == 'X') {
            int i;
            for (i = 0; in[i + 2] != '\0'; ++i)
                ;
            /* if 8 digits return 16 == hex */
            return i == INT_HEX_SIZE ? 16 : 0;

        } else if (in[1] == 'b' || in['1'] == 'B') {
            int i;
            for (i = 0; in[i + 2] != '\0'; ++i)
                ;
            /* if 32 digits return 2 == bin */
            return i == INT_BIN_SIZE ? 2 : 0;
        }

    } else if (in[0] == '\0') {
        return -1;
    }

    return 0; /* 0 == invalid input */
}

/* converts the input string into an integer for processing */
int stringToInt(char in[], int in_type, int var)
{
    int p;
    var = 0;
    switch (in_type) {

        case 2:
            for (p = 2; p < BIN_STRING_LEN; ++p) {
                
                if ( isdigit(in[BIN_STRING_LEN + 1 - p]) ) {
                    /* in[33]*2^0 + in[32]*2^1 + in[31]*2^2 + ... */
                    var += (in[BIN_STRING_LEN + 1 - p] - '0') * (1 << (p - 2));
                }

            }

            break;
    
        case 16:
            for (p = 2; p < HEX_STRING_LEN; ++p) {

                if ( isdigit(in[HEX_STRING_LEN + 1 - p]) ) {

                    /* in[9]*16^0 + in[8]*16^1 + in[7]*16^2 + ... */
                    var += (in[HEX_STRING_LEN + 1 - p] - '0') 
                           * (1 << (p - 2) * 4);

                } else {

                    /* in[9]*16^0 + in[8]*16^1 + in[7]*16^2 + ... */
                    var += ( tolower(in[HEX_STRING_LEN + 1 - p]) - 'a' + 10 ) 
                           * (1 << (p - 2) * 4);

                }

            }

            break;
        
    }

    return var;

}