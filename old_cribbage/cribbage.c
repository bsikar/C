#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_NAME_LENGTH 20
#define MAX_ANSWER_LENGTH 10
#define MAX_SUITE_LENGTH 8
#define HAND_COUNT 6
#define CRIB_COUNT 4
#define DECK_COUNT 52
#define DISCARD_COUNT 2
#define MAX_POINTS 121

void clear(void);
void get_name(char [], int);
void cut_for_crib(int *);
void print_cut_for_crib(int, int);
void get_hand(int [], int []);
void bubble_sort(int [], int);
void print_hand(char [], int [], int, int);
void print_crib(char [], char [], int [], int);
void discard_2(char [], int [], int [], int, int);
void get_cut(int [], int *, char [], char [], int *, int *, int);
void autocount(int [], int, int *);
int chicken_dinner(char [], int);
void stage_2(char [], char [], int [], int [], int [], int, int [], int *, int *, int *);

int main(void) {
    char name1[MAX_NAME_LENGTH + 1] = "", name2[MAX_NAME_LENGTH + 1] = "";
    int name1Hand[HAND_COUNT] = {0}, name2Hand[HAND_COUNT] = {0};
    int usedCards[DECK_COUNT] = {0}, crib[CRIB_COUNT] = {0}, cribTracker = 0, cut = 0;
    int name1Score = 0, name2Score = 0;
    srand(time(NULL));

    get_name(name1, 1);
    get_name(name2, 2);

    cut_for_crib(&cribTracker);

    while (name1Score < MAX_POINTS && name2Score < MAX_POINTS) {
        get_hand(name1Hand, usedCards);
        get_hand(name2Hand, usedCards);

        discard_2(name1, name1Hand, crib, 1, cribTracker);
        discard_2(name2, name2Hand, crib, 2, cribTracker);
        get_cut(usedCards, &cut, name1, name2, &name1Score, &name2Score, cribTracker);

        // stage_1();
        stage_2(name1, name2, name1Hand, name2Hand, crib, cut, usedCards, &name1Score, &name2Score, &cribTracker);
    }

    return 0;
}

void clear(void) {
    system("clear");
}

void get_name(char name[], int playerNumber) {
    char answer[MAX_ANSWER_LENGTH + 1] = "";
    char character = '\0';
    int characterCount = 0;
    memset(name, 0, MAX_NAME_LENGTH + 1);
    memset(answer, 0, MAX_ANSWER_LENGTH + 1);

    clear();

    printf("what is your name player %d?\ninput: ", playerNumber);
    while ((character = getchar()) != '\n') {
        if (characterCount < MAX_NAME_LENGTH) {
            name[characterCount++] = character;
        }
    }

    characterCount = 0;
    printf("you entered: %s\nis this name correct? [Y/n] ", name);
    while ((character = getchar()) != '\n') {
        if (characterCount < MAX_ANSWER_LENGTH) {
            answer[characterCount++] = character;
        }
    }

    if (!(!strlen(answer) || strncasecmp(answer, "y", 1) == 0)) {
        get_name(name, playerNumber);
    }

    clear();
}

void cut_for_crib(int *cribTracker) {
    int cut1 = rand() % DECK_COUNT, cut2 = rand() % DECK_COUNT;

    if (cut1 > cut2) {
        *cribTracker = 2;
    } else if (cut1 < cut2) {
        *cribTracker = 1;
    } else {
        cut_for_crib(cribTracker);
    }
}

void print_cut_for_crib(int playerNumber, int cribTracker) {
    if (cribTracker == playerNumber) {
        printf("\nIt is your crib\n\n");
    } else {
        printf("\nIt is not your crib\n\n");
    }
}

void get_hand(int hand[], int usedCards[]) {
    int count = 0, card = 0;

    while (count != HAND_COUNT) {
        card = rand() % DECK_COUNT;
        if (usedCards[card] != 1) {
            ++usedCards[card];
            hand[count++] = card;
        }
    }
}

void bubble_sort(int hand[], int arraySize) {
    int temp = 0;

    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = 0; j < arraySize - i - 1; j++) {
            if (hand[j] > hand[j+1]) {
                    temp = hand[j];
                    hand[j] = hand[j+1];
                    hand[j+1] = temp;
            }
        }
    }
}

void print_hand(char name[], int hand[], int playerNumber, int cribTracker) {
    char suite[MAX_SUITE_LENGTH + 1] = "";

    bubble_sort(hand, HAND_COUNT);

    printf("* %s's Hand *\n", name);
    print_cut_for_crib(playerNumber, cribTracker);

    for (int i = 0; i < HAND_COUNT; ++i) {
        switch (hand[i] % 4) {
        case 0:
            strcpy(suite,"diamonds");
            break;
        case 1:
            strcpy(suite, "hearts");
            break;
        case 2:
            strcpy(suite, "clubs");
            break;
        case 3:
            strcpy(suite, "spades");
            break;
        }
        switch (hand[i] / 4) {
        case 0:
            printf("[%d] Ace of %s\n", i, suite);
            break;
        case 10:
            printf("[%d] Jack of %s\n", i, suite);
            break;
        case 11:
            printf("[%d] Queen of %s\n", i, suite);
            break;
        case 12:
            printf("[%d] King of %s\n", i, suite);
            break;
        case 50:
            break;
        default:
            printf("[%d] %d of %s\n", i, (hand[i] / 4)+1, suite);
            break;
        }
    }
}

void print_crib(char name1[], char name2[], int crib[], int cribTracker) {
    char suite[MAX_SUITE_LENGTH + 1] = "";

    bubble_sort(crib, CRIB_COUNT);

    if (cribTracker == 1) {
        printf("* %s's Crib *\n\n", name1);
    } else {
        printf("* %s's Crib *\n\n", name2);
    }
    for (int i = 0; i < CRIB_COUNT; ++i) {
        switch (crib[i] % 4) {
        case 0:
            strcpy(suite,"diamonds");
            break;
        case 1:
            strcpy(suite, "hearts");
            break;
        case 2:
            strcpy(suite, "clubs");
            break;
        case 3:
            strcpy(suite, "spades");
            break;
        }
        switch (crib[i] / 4) {
        case 0:
            printf("[%d] Ace of %s\n", i, suite);
            break;
        case 10:
            printf("[%d] Jack of %s\n", i, suite);
            break;
        case 11:
            printf("[%d] Queen of %s\n", i, suite);
            break;
        case 12:
            printf("[%d] King of %s\n", i, suite);
            break;
        default:
            printf("[%d] %d of %s\n", i, (crib[i] / 4)+1, suite);
            break;
        }
    }
}

void discard_2(char name[], int hand[], int crib[], int playerNumber, int cribTracker) {
    int character = '\0';
    int discardCards[DISCARD_COUNT] = {0}, discardCount = 0;

    print_hand(name, hand, playerNumber, cribTracker);
    printf("\nselect 2 cards to be placed in the crib [from 0 - 5]\n[for example type \"02\" to discard cards 0 and 2]\n\t: ");

    while ((character = getchar()) && discardCount != DISCARD_COUNT) {
        if (character >= '0' && character <= '5') {
            if (discardCount == 1 && character != discardCards[0]) {
                ++discardCount;
                if (crib[1] == 0) {
                    crib[1] = hand[character - 48];
                    hand[character - 48] = 200;
                } else {
                    crib[3] = hand[character - 48];
                    hand[character - 48] = 200;
                }
            } else if (discardCount == 0) {
                ++discardCount;
                if (crib[0] == 0) {
                    crib[0] = hand[character - 48];
                    hand[character - 48] = 200;
                } else {
                    crib[2] = hand[character - 48];
                    hand[character - 48] = 200;
                }
            }
        } else if (character == '\n') {
            printf("\nselect 2 cards to be placed in the crib [from 0 - 5]\n[for example type \"0 2\" to discard cards 0 and 2]\n\t: ");
        }
    }
    clear();

}

void get_cut(int usedCards[], int *cut, char name1[], char name2[], int *name1Score, int *name2Score, int cribTracker) {
    int card = rand() % DECK_COUNT;
    char suite[MAX_SUITE_LENGTH + 1] = "";

    if (usedCards[card] == 0 && (card / 4) == 10 && cribTracker == 1) {
        *name1Score += 2;
        printf("%s (the dealer/the person who has the crib) cut a Jack. +2 points for knobs\n%s's score = %d and %s's score = %d\n", name1, name1, *name1Score, name2, *name2Score);
    } else if (usedCards[card] == 0 && (card / 4) == 10 && cribTracker == 2) {
        name2Score += 2;
        printf("%s (the dealer/the person who has the crib) cut a Jack. +2 points for knobs\n%s's score = %d and %s's score = %d\n", name2, name2, *name2Score, name1, *name1Score);
    }
    if (usedCards[card] == 0) {
        *cut = card;

        switch (card % 4) {
        case 0:
            strcpy(suite,"diamonds");
            break;
        case 1:
            strcpy(suite, "hearts");
            break;
        case 2:
            strcpy(suite, "clubs");
            break;
        case 3:
            strcpy(suite, "spades");
            break;
        }
        switch (card / 4) {
        case 0:
            printf("Ace of %s\n", suite);
            break;
        case 10:
            printf("Jack of %s\n", suite);
            break;
        case 11:
            printf("Queen of %s\n", suite);
            break;
        case 12:
            printf("King of %s\n", suite);
            break;
        default:
            printf("%d of %s\n", (card / 4)+1, suite);
            break;
        }
    }
}

void autocount(int hand[], int cut, int *score) {
    // TODO
}

int chicken_dinner(char name[], int score) {
    if (score >= MAX_POINTS) {
        printf("congrats, %s! You won!\n", name);
    } else {
        return 1;
    }

    return 0;
}

void stage_2(char name1[], char name2[], int name1Hand[], int name2Hand[], int crib[], int cut, int usedCards[], int *name1Score, int *name2Score, int *cribTracker) {
    if (*cribTracker == 1) {
        autocount(name1Hand, cut, name1Score);
        autocount(crib, cut, name1Score);
        if (chicken_dinner(name1, *name1Score) == 1) {
            autocount(name2Hand, cut, name2Score);
        }
    }else {
        autocount(name2Hand, cut, name2Score);
        autocount(crib, cut, name2Score);
        if (chicken_dinner(name2, *name2Score) == 1) {
            autocount(name1Hand, cut, name1Score);
        }
    }

    if (*cribTracker == 2) {
        *cribTracker = 1;
    } else {
        *cribTracker = 2;
    }
    for (int i = 0; i < DECK_COUNT; ++i) {
        usedCards[i] = 0;
    }
    printf("test\n");
}

