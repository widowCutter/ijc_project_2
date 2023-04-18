// wordcount.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab.h"
#include "io.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 255


void print_htab(htab_pair_t *t){
  printf("%s\t%d \n",t->key,t->value);
}


int read_buffer(htab_t *t){
  bool wasLongWord = false;
  char *word =  malloc(MAX_LENGHT + 1); 
  int read = 0;
  while (read >= 0) {
    read = read_word(word, MAX_LENGHT, stdin);
    if (read > 0) {
      char *word_write = malloc(read + 1);
      strcpy(word_write, word);
      htab_lookup_add(t, word_write)->value ++;
    }
    if (read >= MAX_LENGHT && !wasLongWord) {
      fprintf(stderr, "Input contains words longer than defined max lenght(%d)\n",MAX_LENGHT);
    }
  }
  return 0;
}


int main(int argc, char *argv[])
{

  // Velikost hashmap odvozena od priblizneho cisla bezne pouzivanych anglickych slov 
  // vynasobenych cislem 1.3
  htab_t *htab = htab_init(45503);

  read_buffer(htab);
  
  htab_for_each(htab, print_htab);

  #ifdef STATISTICS
  htab_statistics(htab);
  #endif /* ifdef  STATISTICS */

  htab_free(htab);

  return 0;
}
