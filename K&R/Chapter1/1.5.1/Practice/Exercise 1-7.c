#include <stdio.h>

int main(void) {
    int c = getchar();

    for (;;) {
        if (c == EOF) {
            printf("%d\n", EOF);
            break;
        } else {
            puts("not EOF");
            break;
        }
    }

    return 0;
}
