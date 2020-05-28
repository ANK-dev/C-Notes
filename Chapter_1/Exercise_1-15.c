#include <stdio.h>

#define LOWER 0.0
#define UPPER 300.0
#define STEP 20.0

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300, floating-point version */

float fahrToCelsius(float fahr);
void printTable(float fahr, float celsius, int header);

main(){
    float fahr, celsius;

    fahr = LOWER;
    printTable(0.0, 0.0, 1);
    while(fahr <= UPPER){
        celsius = fahrToCelsius(fahr);
        printTable(fahr, celsius, 0);
        fahr = fahr + STEP;
    }
}

float fahrToCelsius(float fahr){
   return (5.0 / 9.0) * (fahr - 32.0);
}

void printTable(float fahr, float celsius, int header){
    if(header == 1){
        printf("Fahrenheit To Celsius Conversion Table\n");
        printf("======================================\n\n");
        printf(" °F\t°C\n");
    } else {
        printf("%3.0f %6.1f\n", fahr, celsius);
    }
}
