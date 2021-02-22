#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	srand(time(NULL));
	int number1 = 0, number2 = 0, answer = 0;
	float numberWrong = 0, totalNumber = 0;
	
	system("clear");
	
	puts("press enter to start and press ctrl + d to stop");
	while (getchar() != EOF) {
		number1 =  (rand() % (12 - 3 + 1)) + 3;
		number2 =  (rand() % (12 - 3 + 1)) + 3;
		++totalNumber;

		printf("%d * %d\t: ", number1, number2);
		scanf("%d", &answer);
		
		if (answer != number1 * number2) {
			printf("%d * %d = %d, not %d\n", number1, number2, number1 * number2, answer);
			++numberWrong;
		}
	
	}

	printf("you got %.0f / %.0f : %.3f%%\n", numberWrong, totalNumber, ((numberWrong - totalNumber) / totalNumber));

	return 0;
}

