// htab_size.h
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"


size_t htab_size(const htab_t * t){
  return t->size;
}
