// htab_clear.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"
#include <stdlib.h>

void htab_clear(htab_t * t){    // ruší všechny záznamy
  for (int i = 0; i < t->arr_size; i++) {
    if (t->arr_ptr[i] != NULL) {
      htab_item *item = t->arr_ptr[i];
      htab_item *next_item;
      do {
        next_item = item->next;
        free((void *)item->pair->key);
        free(item->pair);
        free(item);
        item = next_item;
      } while (next_item != NULL);
    }
    t->arr_ptr[i] = NULL;
  }
}
