#include "htab.h"
#include "htab_private.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct htab_pair *htab_lookup_add(struct htab *t, htab_key_t key){
  size_t hash =  htab_hash_function(key);
  htab_item *item;
  if (t->arr_ptr[hash % t->arr_size] == NULL) {
    t->arr_ptr[hash % t->arr_size] = malloc(sizeof(struct htab_item));
    item = t->arr_ptr[hash % t->arr_size];
    item->pair = malloc(sizeof(struct htab_pair));
    if (item->pair == NULL) {
      return NULL;
    }
    item->pair->value = 0;
    item->pair->key = key;
  return item->pair;
  }
  else {
    item = t->arr_ptr[hash % t->arr_size];
    do {
      if (strcmp(item->pair->key, key) == 0) {
        return item->pair;
      }
      else if (item->next != NULL){
        item = item->next;
      }
      else {
        break;
      };
    } while (1);
  }
  
  item->next = malloc(sizeof(struct htab_item));
  if (item->next == NULL) {
    return NULL;
  }
  item = item->next;
  
  item->pair = malloc(sizeof(struct htab_pair));
  if (item->pair == NULL) {
    return NULL;
  }
  item->pair->value = 0;
  item->pair->key = key;
  return item->pair;
}
