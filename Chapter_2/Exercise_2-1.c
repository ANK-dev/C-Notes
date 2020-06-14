/**
 * Exercise 2-1 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * variable range - print ranges of `char`, `short`, `int`, `long`, and `float`
 * ----------------------------------------------------------------------------
 * 
 * Didn't bother to calculate the values manually, sorry ¯\_(ツ)_/¯.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("<limits.h> values\n"\
           "=================\n\n");

    printf(             "\t\t  {     size: %lu byte(s)\n"\
           "   `char` range\t  {   signed: %20d <= n <= %20d\n"\
                        "\t\t  { unsigned: %20d <= n <= %20d\n\n",
           sizeof(char), CHAR_MIN, CHAR_MAX, 0, UCHAR_MAX);

    printf(             "\t\t  {     size: %lu byte(s)\n"\
           "  `short` range\t  {   signed: %20d <= n <= %20d\n"\
                        "\t\t  { unsigned: %20d <= n <= %20d\n\n",
           sizeof(short), SHRT_MIN, SHRT_MAX, 0, USHRT_MAX);

    printf(             "\t\t  {     size: %lu byte(s)\n"\
           "`integer` range\t  {   signed: %20d <= n <= %20d\n"\
                        "\t\t  { unsigned: %20d <= n <= %20u\n\n",
           sizeof(int), INT_MIN, INT_MAX, 0, UINT_MAX);

    printf(             "\t\t  {     size: %lu byte(s)\n"
           "   `long` range\t  {   signed: %20ld <= n <= %20ld\n"
                        "\t\t  { unsigned: %20d <= n <= %20lu\n\n",
           sizeof(long), LONG_MIN, LONG_MAX, 0, ULONG_MAX);

    printf("<float.h> values\n"
           "================\n\n");
    
    printf(                 "\t\t\t{ size: %lu byte(s)\n"
           "        `float` range\t{  MIN: %E\n"
                            "\t\t\t{  MAX: %E\n\n",
           sizeof(float), FLT_MIN, FLT_MAX);

    printf(                 "\t\t\t{ size: %lu byte(s)\n"
           "       `double` range\t{  MIN: %E\n"
                            "\t\t\t{  MAX: %E\n\n",
           sizeof(double), DBL_MIN, DBL_MAX);

    printf(                 "\t\t\t{ size: %lu byte(s)\n"
           "  `long double` range\t{  MIN: %LE\n"
                            "\t\t\t{  MAX: %LE\n\n",
           sizeof(long double), LDBL_MIN, LDBL_MAX);


    return 0;
}