#include <stdio.h>

#define IN	1
#define OUT	0

int main(void) {
	int c, state, lines, words, characters;
	state = OUT;
	lines = words = characters = 0;

	while( (c = getchar()) != EOF) {
		++characters;
		if( c == '\n')
			++lines;
		if( c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if( state == OUT) {
			state = IN;
			++words;
		}
	}
	printf("%d %d %d\n", lines, words, characters);
	
	return 0;
}
