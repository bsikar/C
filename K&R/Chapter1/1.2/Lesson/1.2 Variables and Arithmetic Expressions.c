#include <stdio.h>

int main(void) {
	int fahr, celsius, lower, upper, step;
	float fahr1, celsius1;

	fahr =  fahr1 = lower = 0;
	upper = 300;
	step = 20;

	while (fahr1 <= upper) {
		celsius1 = 5 * (fahr1 - 32) / 9;
		printf("%3.0f\t%6.2f\n", fahr1, celsius1);
		fahr1 = fahr1 + step;
	}
/*
	while (fahr <= upper) {
		celsius = 5 * (fahr - 32) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}
*/
	return 0;
}
