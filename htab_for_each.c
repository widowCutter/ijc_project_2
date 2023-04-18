// htab_for_each.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
  for (int i = 0; i < t->arr_size; i++) {
    htab_item *item = t->arr_ptr[i];
    while (item != NULL) {
      f(item->pair);
      item = item->next;
    }
  }
}

