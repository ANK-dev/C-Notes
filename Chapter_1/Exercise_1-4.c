#include <stdio.h>

/* print Celsius-Fahrenheit table
for celsius = 0, 20, ..., 300, floating-point version */

main(){
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("Celsius To Fahrenheit Conversion Table\n");
    printf("======================================\n\n");
    printf(" °C\t°F\n");
    while(celsius <= upper){
        fahr = (9.0 / 5.0 * celsius) + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
