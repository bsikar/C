#include <stdio.h>

int main(void) {
    float fahr, celsius;
    int  upper, step;

    fahr = 0;
    upper = 300;
    step = 20;

    puts("Celsius to Fahrenheit table");
    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("%6.2f %5.0f\n", celsius, fahr);
        fahr = fahr + step;
    }

    return 0;
}
