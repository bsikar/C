#include <stdio.h>

int main(void) {
	int c, i, character[128];
	c = i = 0;
	for( i = 0; i < 128; ++i)
		character[i] = 0;
	
	while( (c = getchar()) != EOF)
		if( c != ' ' && c != '\t' && c != '\n')
			++character[c];
	
	for( i = 0; i < 128; ++i)
		if( character[i] > 0)
			printf("%c: %d\n", i, character[i]);
	
	return 0;
}
