#include <stdio.h>

int main(void) {
    int blanks, tabs, newLines, c;
    blanks = tabs = newLines = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        } else if (c == '\t') {
            ++tabs;
        } else if (c == '\n') {
            ++newLines;
        }
    }

    printf("%s %d %s %d %s %d %s\n", "There were", blanks, "blanks,", tabs, "tabs, and", newLines, "new lines.");

    return 0;
}
