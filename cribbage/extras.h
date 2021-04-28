#ifndef EXTRAS
#define EXTRAS

#define NAME_MAX     22
#define DECK_COUNT   52
#define HAND_COUNT   6
#define PLAYER_COUNT 2
#define CRIB_COUNT   4

static const char *help =
  "--help  -h     show this information\n"
  "------------------------------------\n"
  "This is a basic cribbage game coded in C.\n"
  "Yes it is shit. Shut up!";

static const char *deck[] = {
    "Ace of Clubs", "Ace of Diamonds", "Ace of Hearts", "Ace of Spades",
    "Two of Clubs", "Two of Diamonds", "Two of Hearts", "Two of Spades",
    "Three of Clubs", "Three of Diamonds", "Three of Hearts", "Three of Spades",
    "Four of Clubs", "Four of Diamonds", "Four of Hearts", "Four of Spades",
    "Five of Clubs", "Five of Diamonds", "Five of Hearts", "Five of Spades",
    "Six of Clubs", "Six of Diamonds", "Six of Hearts", "Six of Spades",
    "Seven of Clubs", "Seven of Diamonds", "Seven of Hearts", "Seven of Spades",
    "Eight of Clubs", "Eight of Diamonds", "Eight of Hearts", "Eight of Spades",
    "Nine of Clubs", "Nine of Diamonds", "Nine of Hearts", "Nine of Spades",
    "Ten of Clubs", "Ten of Diamonds", "Ten of Hearts", "Ten of Spades",
    "Jack of Clubs", "Jack of Diamonds", "Jack of Hearts", "Jack of Spades",
    "Queen of Clubs", "Queen of Diamonds", "Queen of Hearts", "Queen of Spades",
    "King of Clubs", "King of Diamonds", "King of Hearts", "King of Spades", ""};

int usedCards[DECK_COUNT] = {0}, crib[CRIB_COUNT] = {0}, cut = 0;

struct player {
  char name[NAME_MAX];
  int hand[HAND_COUNT], crib;
} player[2];

#endif
