#include <stdio.h>

#define MAXLINE 1000

int GETLINE_AHH(char line[], int maxline);
void copy(char to[], char from[]);

int main(void) {
	int i, len, max;
	char line[MAXLINE], longest[MAXLINE];
	max = i = 0;
	for( i = 0; i < MAXLINE; ++i) {
		line[i] = 0;
		longest[i] = 0;
	}
	
	while( (len = GETLINE_AHH(line, MAXLINE)) > 0)
		if( len > max) {
			max = len;
			copy(longest, line);
		}
	if( max > 0)
		printf("%s", longest);


	return 0;
}

int GETLINE_AHH(char s[], int lim) {
	int c, i;
	i = c = 0;

	for( i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if( c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy( char to[], char from[]) {
	int i;
	i = 0;
	while( (to[i] = from[i]) != '\0')
		++i;
}
