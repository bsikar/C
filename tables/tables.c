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

