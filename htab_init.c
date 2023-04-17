#include "htab_private.h"
#include <stdio.h>
#include <stdlib.h>


htab_t *htab_init(const size_t n){
  htab_t *h_table;
  h_table = malloc(sizeof(struct htab));
  h_table->arr_ptr = malloc(sizeof(htab_item) * n);
  h_table->arr_size = n;
  h_table->size = 0;
  return h_table;
};              // konstruktor tabulky
