#include <stdio.h>

#define VAR1 10
#define VAR2 "test"
const int var1 = 10;

int main(void) {
    printf("%d\n", VAR1);
    printf("%d\n", var1);
    printf("%s\n", VAR2);
}
