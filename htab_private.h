// htab_private.h
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab.h"

typedef struct htab_item{
  struct htab_item *next;
  htab_pair_t *pair;
} htab_item;

typedef struct htab{
  unsigned size;
  unsigned arr_size;
  htab_item **arr_ptr;
}htab;    
