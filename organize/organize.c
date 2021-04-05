/* MIT License
 *
 * Copyright (c) 2021 Brighton Sikarskie
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

    for (i = 0; i < MAXLENGTH; ++i) {
        for (step = 0; step < MAXLENGTH; ++step) {
            lineContents[i][step] = '\0';
        }
    }

    /* get input file */
    FILE* inputFile = fopen(argv[1], "r");

    /* get strings of input file */
    while ((character = fgetc(inputFile)) != EOF) {
        if (character == '\n') {
            characterCount = 0;
            ++lineNumber;
        } else {
            lineContents[lineNumber][characterCount] = character;
            ++characterCount;
        }
    }

    /* bubble sort? */
    for (step = 0; step < (lineNumber - 1); ++step) {
        for (i = 0; i < (lineNumber - step - 1); ++i) {
            if (strlen(lineContents[i]) > strlen(lineContents[i + 1])) {
                strcpy(temp[0], lineContents[i]);
                strcpy(lineContents[i], lineContents[i + 1]);
                strcpy(lineContents[i + 1], temp[0]);
            }
        }
    }

    fclose(inputFile);

    /* make output file from result of the bubble sort */
    for (i = 0; i < lineNumber; ++i) {
        fputs(lineContents[i], outputFile);
        fputs("\n", outputFile);
    }

    fclose(outputFile);

    return 0;
}

