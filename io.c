#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_word(char *s, int max, FILE *f){
  char format[100]; 
  sprintf(format, "%%\%ds", max);
  if (fscanf(f, format, s) <= 0) {
    return -1;
  }
  int word_length = strlen(s);
  if (word_length >= max) {
    int c;
    do {
    c = fgetc(f);
    } while (!isspace(c));
  }
  return word_length;
}
