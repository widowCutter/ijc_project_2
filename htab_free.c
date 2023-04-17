#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t * t){
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
  }
  free(t);
}

