#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

int main(void) {
    int character = 0, characterCount = 0;
    char inputString[MAX_STRING_LENGTH + 1] = "\n";

    while (strcmp(inputString, "exit") != 0) {
        memset(inputString, 0, MAX_STRING_LENGTH + 1);
        while ((character = getchar()) != '\n') {
            if (characterCount < MAX_STRING_LENGTH) {
                inputString[characterCount++] = character;
                for (int i = 0; i < MAX_STRING_LENGTH && inputString[i] != '\0'; ++i) {
                    if (inputString[i] == 'l' && inputString[i+1] == 'b' && inputString[i+3] == 's') {
                        puts("lbs was said");
                    }
                }
            }
        }
    }

    return 0;
}

