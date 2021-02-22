#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ISALPHA(C) ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') ? 1 : 0)

int main(int argc, char **argv) {
    srand(time(NULL));
    for (int i = 1; i < argc; ++i) {
        int length = strlen(argv[i]);
        for (int o = 1; o < length-1; ++o) {
	    if (o != length-2 && ISALPHA(argv[i][o])) { 
		    const char temp = argv[i][o];
		    argv[i][o] = argv[i][o+1];
		    argv[i][o+1] = temp;
	        }
        }
	    printf("%s ", argv[i]);
    }
    putchar('\n');

    return 0;
}
