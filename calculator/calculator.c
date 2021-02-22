#include <stdio.h>

int main(void) {
	int number1 = 30;
	int number2 = 10;
	int result = number1 + number2;
	int* a = &result;
	printf("%d", *a);

	return 0;
}

