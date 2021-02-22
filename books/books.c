#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void mv(char file[500], char dir[550]);

int main(void) {
  int character, newCharacter, newDigit, lineNumber, lineCounter;
  char firstLetter[2] = "";
  char nickName[50] = "";
  char fullName[500] = "";
  char temp[550] = "";
  struct stat nb;
  newCharacter = newDigit = lineNumber = lineCounter = 0;
  char automate[] =
      "for x in {1..12295}; do var=$(cat /dev/urandom | tr -dc '_a-zA-Z0-9' | "
      "fold -w 32 | head -n 1); dd if=/dev/urandom bs=1 count=1 of=$var; done; "
      "ls | grep -v code | grep -v books > books";
  char cleanup[] = "rm books code";
  system(automate);
  FILE *file = fopen("books", "r");
  while ((character = fgetc(file)) != EOF)
    if (character == '\n')
      ++lineCounter;
  fclose(file);
  file = fopen("books", "r");
  while ((character = fgetc(file)) != EOF)
    if (isalpha(character)) {
      ++newCharacter;
      if (newCharacter == 1 && newDigit == 0) {
        firstLetter[0] = character;
        nickName[0] = character = fullName[0] = character;
        if (stat(firstLetter, &nb) != 0)
          mkdir(firstLetter, 0777);
      } else if (newDigit == 0)
        nickName[newCharacter - 1] = character = fullName[newCharacter - 1] =
            character;
      else
        fullName[newCharacter + newDigit - 1] = character;
    } else if (isdigit(character)) {
      ++newDigit;
      if (newCharacter == 0)
        nickName[newDigit - 1] = character = fullName[newDigit - 1] = character;

      else
        fullName[newCharacter + newDigit - 1] = character;

    } else if (character != ' ' && character != '\t' && character != '\n')
      if (newCharacter == 0) {
        ++newDigit;
        nickName[newDigit - 1] = character = fullName[newDigit - 1] = character;
      } else if (newDigit == 0) {
        ++newCharacter;
        nickName[newCharacter - 1] = character = fullName[newCharacter - 1] =
            character;
      } else {
        ++newCharacter;
        fullName[newCharacter + newDigit - 1] = character;
      }
    else {
      if (isalpha(firstLetter[0])) {
        strcat(temp, firstLetter);
        strcat(temp, "/");
        strcat(temp, nickName);
      } else
        strcat(temp, nickName);
      if (stat(temp, &nb) != 0)
        mkdir(temp, 0777);
      mv(fullName, temp);
      memset(&nickName[0], 0, sizeof(nickName));
      memset(&fullName[0], 0, sizeof(fullName));
      memset(&temp[0], 0, sizeof(temp));
      newCharacter = newDigit = 0;
      ++lineNumber;
      printf("%d/%d\n", lineNumber, lineCounter);
    }
  fclose(file);
  puts("\ndone");
  system(cleanup);
  return 0;
}

void mv(char file[500], char dir[550]) {
  char mv[200] = "mv ";
  strcat(mv, file);
  strcat(mv, " ");
  strcat(mv, dir);
  system(mv);
}
