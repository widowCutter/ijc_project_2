// htab_free.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t * t){
  htab_clear(t);
  free(t->arr_ptr);
  free(t);
}

