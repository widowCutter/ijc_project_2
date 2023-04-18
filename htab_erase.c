// htab_erase.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"
#include <stdio.h>
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
        if (prev_item != NULL) {
          prev_item->next = item->next;
        }
        else {
          t->arr_ptr[hash % t->arr_size] = item->next;
        }
        free((void*)item->pair->key);
        free(item->pair);
        return true;
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
