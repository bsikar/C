#include <stdio.h>

char *is_odd(int number);

int main(void) {
	printf("%s\n", is_odd(24));

	return 0;
}

char *is_odd(int number) {
	if ((number % 2) == 0)
		return "even";
	else
		return "odd";
}

