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
#include <time.h>

int main(void) {
    srand(time(NULL));
    int number1 = 0, number2 = 0, answer = 0;
    float numberWrong = 0, totalNumber = 0;

    system("clear");

    puts("press enter to start and press ctrl + d to stop");
    while (getchar() != EOF) {
        number1 =  (rand() % (12 - 3 + 1)) + 3;
        number2 =  (rand() % (12 - 3 + 1)) + 3;
        ++totalNumber;

        printf("%d * %d\t: ", number1, number2);
        scanf("%d", &answer);

        if (answer != number1 * number2) {
            printf("%d * %d = %d, not %d\n", number1, number2, number1 * number2, answer);
            ++numberWrong;
        }

    }

    printf("you got %.0f / %.0f : %.3f%%\n", numberWrong, totalNumber, ((numberWrong - totalNumber) / totalNumber));

    return 0;
}

