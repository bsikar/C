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
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "extras.h"

void getNames(void);
void bubbleSort(int *, int);
void getHands(void);
void getDiscards(void);

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc > 1) {
        if (strcmp(argv[1], "--help") && strcmp(argv[1], "-h")) {
            puts("try with '--help'");
            return 1;
        } else {
            puts(help);
            return 0;
        }
    }

    getNames();
    getHands();
    getDiscards();

    return 0;
}

void getNames(void) {
    char answer[4] = {0};

    for (int i = 0; i < PLAYER_COUNT; ++i) {
        for (;;) {
            // get user input
            printf("Enter your name: ");
            fgets(player[i].name, NAME_MAX, stdin);
            // clear input buffer
            stdin = freopen(NULL, "r", stdin);
            // remove \n from name
            player[i].name[strcspn(player[i].name, "\n")] = '\0';

            // verify that the entered name is correct
            printf("You entered '%s'\n", player[i].name);
            printf("Are you sure? [Y/n]: ");
            fgets(answer, 4, stdin);
            stdin = freopen(NULL, "r", stdin);
            answer[strcspn(answer, "\n")] = '\0';
            // if the user entered y, yes, or nothing than rerun user input
            if (strcasecmp(answer, "y") || strcasecmp(answer, "yes") || strcmp(answer, "")) {
                break;
            }
        }
    }
    // set who gets the crib
    int winner = rand() % PLAYER_COUNT;
    player[0].crib = winner;
    player[1].crib = !winner;
}

void bubbleSort(int *input, int size) {
    int temp = 0;
    for (int o = 0; o < size - 1; ++o) {
        for (int j = 0; j < size - o - 1; ++j) {
            if (input[j] > input[j+1]) {
                temp = input[j];
                input[j] = input[j+1];
                input[j+1] = temp;
            }
        }
    }
}

void getHands(void) {
    // fill a hand for each player
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        int card = 0, count = 0;
        while (count != HAND_COUNT) {
            card = rand() % DECK_COUNT;
            if (!usedCards[card]) {
                ++usedCards[card];
                player[i].hand[count++] = card;
            }
        }
        // bubble sort the hand
        bubbleSort(player[i].hand, HAND_COUNT);
    }
    // give the crib to the other player
    player[0].crib = !player[0].crib;
    player[1].crib = !player[1].crib;
}

void getDiscards(void) {
    int c, prevC;
    // discard 2 cards per each player
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        for (int o = 1; o <= HAND_COUNT; ++o) {
            printf("%s: Card %d: %s\n", player[i].name, o, deck[player[i].hand[o-1]]);
        }
        printf("It is %s's crib\nWhat two cards do you want to discard: ", (player[0].crib)?player[0].name:player[1].name);

        int count = 0;
        while ((c = getchar()) && count != 2) {
            const size_t index = (c - '0') - 1;
            // make sure they only enter a number 1 -> 6
            if (c >= '1' && c <= '6') {
                // make sure they don't enter the same number more than once
                if (count == 0) {
                    prevC = c;
                    // The (2 * i) is here since this while loop will be ran 2 times
                    crib[(2 * i) + count++] = player[i].hand[index];
                    // The = 52 is to make the player.hand[index] == ""
                    player[i].hand[index] = DECK_COUNT;
                } else if (c != prevC) {
                    crib[(2 * i) + count++] = player[i].hand[index];
                    player[i].hand[index] = DECK_COUNT;
                }
            }
        }
    }
    // bubble sort crib
    bubbleSort(crib, CRIB_COUNT);

    // get cut
    c = rand() % DECK_COUNT;
    while (usedCards[c]) {
        c = rand() % DECK_COUNT;
    }
    cut = c;
    ++usedCards[cut];
}
