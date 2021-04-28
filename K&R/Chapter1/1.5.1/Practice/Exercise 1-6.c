#include <stdio.h>

int main(void) {
    int c = getchar();

    for (;;) {
        if( c == EOF) {
            puts("0");
            break;
        } else if( c != EOF) {
            puts("1");
            break;
        }
    }

    return 0;
}
