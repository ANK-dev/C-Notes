#include <stdio.h>

/* print Fahrenheit-Celsius table
for fahr = 300, 280, ..., 0, floating-point version */

main(){
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = upper;
    printf("Fahrenheit To Celsius Conversion Table\n");
    printf("======================================\n\n");
    printf(" °F\t°C\n");
    while(fahr >= lower){
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - step;
    }
}
