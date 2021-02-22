#include <stdio.h>

int main(void) {
	int c, i, whiteSpace, other;
	int numOfDigits[10];

	whiteSpace = other = 0;
	for( i = 0; i < 10; ++i)
		numOfDigits[i] = 0;
	while( (c = getchar()) != EOF)
		if( c >= '0' && c <= '9')
			++numOfDigits[c-'0'];
		else if( c == ' ' || c == '\n' || c == '\t')
			++whiteSpace;
		else
			++other;
	printf("digits =");
	for( i = 0; i < 10; ++i)
		printf(" %d", numOfDigits[i]);
	printf(", white space = %d, other = %d\n", whiteSpace, other);

	return 0;
}
