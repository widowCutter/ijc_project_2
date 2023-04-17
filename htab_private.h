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
