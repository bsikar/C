#include <stdio.h>

int main(void) {
/*
*	long nc;
*	nc = 0;
*
*	while(getchar() != EOF)
*		++nc;
*	printf("%1d\n", nc);
*
*	return 0;
*/
	double nc;

	for(nc = 0; getchar() != EOF; ++nc)
		;
	printf("%.0f\n", nc);

	return 0;
}
