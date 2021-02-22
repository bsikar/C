#include <stdio.h>

#define HELLO_WORLD "Hello World!"

void hello_world(void);

int main(void) {
    hello_world();

    return 0;
}

void hello_world(void) {
    puts(HELLO_WORLD);
}
