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
