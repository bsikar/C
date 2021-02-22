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

#define MAXLEN  10

int main(void) {
    int i, j, nc, c, longest, word[MAXLEN + 1];
    
    i = j = nc = longest = 0;
    
    for (i = 0; i <= MAXLEN; ++i) {
        word[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n') {
            ++nc;
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            if (nc <= MAXLEN) {
                ++word[nc-1];
            } else {
                ++word[MAXLEN];
            }
            nc = 0;
        }
    }

    printf("\nStatistics:\n");
    for (i = 0; i <= MAXLEN; ++i) {
        if (i != 10 && word[i] == 1) {
            printf("There was %d word with a length of %d.\n", word[i], i+1);
        } else if (i != 10 && word[i] > 1) {
            printf("There were %d words with a length of %d.\n", word[i], i+1);
        } else if (i == 10 && word[i] == 1) {
            printf("There was %d word with a length of %d.\n", word[i], i+1);
        } else if (i == 10 && word[i] > 1) {
            printf("There were %d words with a length of %d.\n", word[i], i+1);
        }
        if (word[i] > longest) {
            longest = word[i];
        }
    }

    printf("\nHorizontal Histogram:\n");
    for (i = 0; i <= MAXLEN; ++i) {
        if (i != MAXLEN) {
            printf("%5d:", i+1);
        } else {
            printf(" < 10:");
        }
        for (j = 0; j < word[i]; ++j) {
            putchar('#');
        }
        putchar('\n');

    }

    printf("\nHorizontal Histogram:\n");
    for (i = 0; i <= MAXLEN; ++i) { 
        if (i != 10 && word[i] > 0) {
            printf("%5d: ", i+1);
            for (j = 0; j < word[i]; ++j) {
                putchar('#');
            }
            putchar('\n');
        } else if (i == 10 && word[i] > 0) {
            printf(" > 10: ");
            for (j = 0; j < word[i]; ++j) {
                putchar('#');
            }
            putchar('\n');
        }
    }

    printf("\nVertical Histogram:\n");
    printf("wd ct:\n");
    for (i = longest; i > 0; --i) {
        printf("%6d | ", i);
        for (j = 0; j <= MAXLEN; ++j) {
            if (word[j] >= i) {
                printf("#  ");
            } else {
                printf("   ");
            }
        }
        putchar('\n');
    }
    printf("wd ln: ");
    for (i = 1; i <= MAXLEN; ++i) {
        printf("%3d", i);
    }
    printf(" >%d\n", MAXLEN);

    printf("\nVertical Histogram:\n");
    printf("wd ct:\n");
    for (i = longest; i > 0; --i) {
        printf("%6d | ", i);
        for (j = 0; j <= MAXLEN; ++j) {
            if (word[j] > 0 && word[j] >= i) {
                printf("#  ");
            } else if (word[j] > 0) {
                printf("   ");
            }
        }
        putchar('\n');
    }
    printf("wd ln: ");
    for (i = 0; i <= MAXLEN; ++i) {
        if( word[i] > 0 && i != MAXLEN) {
            printf("%3d", i+1);
        } else if( word[i] > 0 && i == MAXLEN) {
            printf(" >%d", MAXLEN);
        }
    }
    putchar('\n');

    return 0;
}
