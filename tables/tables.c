#include <stdio.h>
#include <stdlib.h>

void printing_function(void);
const char *print_function(void);
char *function(void);

int main(void) {
    char string1[] = "test";
    char string2[5] = "test\0";

    printf("test\n");
    printf("%s\n", string1);
    printf("%s\n", string2);
    puts("test");
    putchar('t');
    putchar('e');
    putchar('s');
    putchar('t');
    putchar('\n');
    system("echo test");
    printing_function();
    const char* variable = print_function();
    printf("%s\n", variable);
    printf("%s\n", function());

    printf("I love");
    printf(" Israel\n");

    printf("%c%c%c%c%c", 116,101,115,116,13);

    return 0;
}

void printing_function(void) {
    char string1[] = "test";
    char string2[5] = "test\0";

    printf("test\n");
    printf("%s\n", string1);
    printf("%s\n", string2);
    puts("test");
    putchar('t');
    putchar('e');
    putchar('s');
    putchar('t');
    putchar('\n');
    system("echo test");
    const char* variable = print_function();
    printf("%s\n", variable);
    printf("%s\n", function());
}

const char *print_function(void) {
    return "test";
}

char *function(void) {
    return "test";
}

