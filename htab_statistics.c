// htab_statistics.c
// Řešení IJC-DU2, příklad 2), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

#include "htab_private.h"
#include <stdio.h>

void htab_statistics(const htab_t * t){
  int max = 0,min = 0;
  float sum = 0.0,numList = 0.0;
  for (int i = 0; i < t->arr_size; i++) {
    int length = 0;
    if (t->arr_ptr[i] != NULL) {
      numList++;
      htab_item *item = t->arr_ptr[i];
      do {
        length++;
        item = item->next;
      } while (item->next != NULL);
    }
    if (length < min || min == 0) {
      min = length;
    }
    if (length > max) {
      max = length;
    }
    sum = length + sum;
    t->arr_ptr[i] = NULL;
  }
  fprintf(stderr, "(%d,%d,%f)\n", min, max, sum / numList);
}
