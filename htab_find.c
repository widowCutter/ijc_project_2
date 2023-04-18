// htab_find.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"
#include <stdio.h>
#include <stdlib.h>

htab_pair_t * htab_find(const htab_t * t, htab_key_t key){
  size_t hash =  htab_hash_function(key);
  htab_item *item = t->arr_ptr[hash % t->arr_size];
  do {
    if (item->pair->key == key) {
      return item->pair;
    }
    item = item->next;
  } while (item->pair->key != key && item->next != NULL);
  return NULL;
}
