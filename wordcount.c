#include "htab.h"
#include "io.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 10


void print_htab(htab_pair_t *t){
  printf("%s\t%d \n",t->key,t->value);
}


int read_buffer(htab_t *t){
  char *word =  malloc(MAX_LENGHT + 1); 
  int read = 0;
  while (read >= 0) {
    read = read_word(word, MAX_LENGHT, stdin);
    if (read > 0) {
      char *word_write = malloc(read + 1);
      strcpy(word_write, word);
      htab_lookup_add(t, word_write)->value ++;
    }
  }
  return 0;
}


int main(int argc, char *argv[])
{
  htab_t *htab = htab_init(2);

  read_buffer(htab);

  
  htab_for_each(htab, print_htab);

  htab_free(htab);

  return 0;
}
