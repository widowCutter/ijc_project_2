
#include "htab_private.h"
#include <stdlib.h>


bool htab_erase(htab_t * t, htab_key_t key){
  size_t hash =  htab_hash_function(key);
  htab_item *item;
  htab_item *prev_item = NULL;
  if (t->arr_ptr[hash % t->arr_size] == NULL) {
    return false;
  }
  else {
    item = t->arr_ptr[hash % t->arr_size];
    do {
      if (strcmp(item->pair->key, key) == 0) {
        return item->pair;
        // Remove
      }
      else if (item->next != NULL){
        prev_item = item;
        item = item->next;
      }
      else {
        break;
      };
    } while (1);
  }
  
  return false;
}    // ruší zadaný záznam
