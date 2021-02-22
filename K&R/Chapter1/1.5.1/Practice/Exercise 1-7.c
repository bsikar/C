#include <stdio.h>

int main(void) {
	int c;

	c = getchar();
	
	while(1)
		if(c == EOF) {
			printf("%d\n", EOF);
			break;
		}
		else {
			puts("not EOF");
			break;
		}

	return 0;
}
