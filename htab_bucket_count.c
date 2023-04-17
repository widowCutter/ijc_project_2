// htab_bucket_count.c
// Řešení IJC-DU2, příklad 2), 15.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab.h"

struct htab{
  unsigned size;
  unsigned arr_size;
  htab_pair_t *arr_ptr;
};    

size_t htab_bucket_count(const htab_t * t){
  return t->arr_size;
}
