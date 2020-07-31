/**
 * Exercise 2-9 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * > In a two's complement number system, `x &= (x-1)` deletes the rightmost
 * > 1-bit in `x`. Explain why. Use this observation to write a faster version
 * > of `bitcount`.
 *
 * __ANSWER__: Given `x` == dₙ…d₁1, where each dₖ, k ∈ ℕ / n ≤ k ≤ 0, is a
 * binary digit, `x-1` is equal to dₙ…d₁0. Since all the other terms are
 * unchanged, the bitwise AND (&) of both terms will only affect the different
 * bits, which, in this case, is d₀, resulting in the operation 1 & 0 which is
 * equal to 0.
 *
 * Given `x` == dₙ…dₙ₋ₖ10…0, where each dₖ, k ∈ ℕ / n ≤ k ≤ 0, is a binary
 * digit, `x-1` is equal to dₙ…dₙ₋ₖ00…0. Since all the other terms are
 * unchanged, the bitwise AND (&) of both terms will only affect the different
 * bits, which, in this case, is dₙ₋ₖ₋₁, resulting in the operation 1 & 0 which
 * is equal to 0.
 *
 * _Q.E.D._
 *
 *******************************************************************************
 *
 *
 * bitcount (faster version):  counts the number of 1-bits in `x`
 * --------------------------------------------------------------
 */

#include <stdio.h>
#include <ctype.h>

#define INT_BIN_SIZE 32
#define INT_HEX_SIZE INT_BIN_SIZE / 4
#define PREFIX 2
#define PADDING 7
#define HEX_STRING_LEN (INT_HEX_SIZE + PREFIX)
#define BIN_STRING_LEN (INT_BIN_SIZE + PREFIX)

int bitcount(unsigned x);
char *decToBin(unsigned int dec, char bin[]);
int validateInput(char in[]);
char *getline(char s[]);
int stringToInt(char in[], int in_type, int var);


int main()
{
    int input_type;
    unsigned x = 0, result;
    char input[BIN_STRING_LEN + 1];
    char output[INT_BIN_SIZE + PADDING + 1];

    printf("bitcount\n========\n");
    printf("> counts the number of 1-bits in `x`\n\n");

    /* get the `x` variable */
    do {
        printf("Type the \"x\" variable\n(0b for binary + %d digits, "
               "0x for hexadecimal + %d digits): ", INT_BIN_SIZE, INT_HEX_SIZE);
    } while (( input_type = validateInput(getline(input)) ) == 0);

    x = stringToInt(input, input_type, x);

    /* calculation happens here */
    result = bitcount(x);

    /* displays input and output nicely formated */
    printf("\nx:\tHex: %X\n\tBin: %s\n\n", x, decToBin(x, output));
    printf("Number of 1-bits:\t%d\n", result); 

    return 0;
}

/* this is the function required by the exercise */
int bitcount(unsigned x)
{
    int b = 0;

    while (x != 0) {
        x &= (x-1);
        ++b;
    }
    
    return b;

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