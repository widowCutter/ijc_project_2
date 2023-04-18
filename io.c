// io.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_word(char *s, int max, FILE *f){
  char format[100]; 
  sprintf(format, "%%\%ds", max);
  if (fscanf(f, format, s) <= 0) {
    return EOF;
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
