#include <stdio.h>

int main(void) {
    printf("Hello, World\n");

/*will result in an error.
 *  printf("hello, World
 *  ");
 */

    printf("Hello, ");
    printf("World");
    printf("\n");

    return 0;
}
