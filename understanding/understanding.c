#include <stdio.h>
#include <string.h>

int main(void) {
    char string[4][5] = { {"this"}, {"is"}, {"a"}, {"test"} };
    char temp[1][100];
    int length = 4;
    int step, i;
    int value = 0;

    printf("\n\n\n\n\n\n\n");

    for (step = 0; step < (length - 1); ++step)
        for (i = 0; i < (length - step - 1); ++i) {
            printf("[0]| %s\n", string[0]);
            printf("[1]| %s\n", string[1]);
            printf("[2]| %s\n", string[2]);
            printf("[3]| %s\n\n", string[3]);

            printf("if(string[i] > string[i + 1]| %s(%lu) > (%lu)%s\n", string[i], strlen(string[i]), strlen(string[i + 1]), string[i + 1]);
            if (strlen(string[i]) > strlen(string[i + 1])) {
                strcpy(temp[0], string[i]);
                strcpy(string[i], string[i + 1]);
                strcpy(string[i + 1], temp[0]);
                printf("\t [%s] ^V [%s]\n", string[i], string[i + 1]);
            }

            printf("is %d < 3 |step: %d\n", step, step);
            value = (length - step - 1);
            printf("is %d < %d |i: %d\n\n", i, value, i);
            printf("*------------------------------------------------------------------------------*\n\n");
        }

    return 0;
}

