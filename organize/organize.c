#include <stdio.h>
#include <string.h>
#define MAXLENGTH 1000

int main (int argc, char **argv) {
	FILE* outputFile = fopen("outputFile", "w+");
	char lineContents[MAXLENGTH][MAXLENGTH];
	int lineNumber = 0;
	int characterCount = 0;
	char character;
	char temp[1][MAXLENGTH];
	int step, i;
	
	for( i = 0; i < MAXLENGTH; ++i)
		for( step = 0; step < MAXLENGTH; ++step)
			lineContents[i][step] = '\0';

	/* get input file */
	FILE* inputFile = fopen(argv[1], "r");
	
	/* get strings of input file */
	while( (character = fgetc(inputFile)) != EOF) {
		if( character == '\n') {
			characterCount = 0;
			++lineNumber;
		}
		else {
			lineContents[lineNumber][characterCount] = character;
			++characterCount;
		}
	}

	/* bubble sort? */
	for( step = 0; step < (lineNumber - 1); ++step)
		for( i = 0; i < (lineNumber - step - 1); ++i)
			if( strlen(lineContents[i]) > strlen(lineContents[i + 1])) {
				strcpy(temp[0], lineContents[i]);
				strcpy(lineContents[i], lineContents[i + 1]);
				strcpy(lineContents[i + 1], temp[0]);
			}

	fclose(inputFile);

	/* make output file from result of the bubble sort */
	for( i = 0; i < lineNumber; ++i) {
		fputs(lineContents[i], outputFile);
		fputs("\n", outputFile);
	}

	fclose(outputFile);

	return 0;
}

