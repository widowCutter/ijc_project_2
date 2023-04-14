#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1
#define MAX_LENGTH 4096


struct cb_element{
  char *line;
  struct cb_element* next;
};
typedef struct cb_element cbEl_s;

struct cb_buffer{
  cbEl_s *read;
  cbEl_s *write;
};
typedef struct cb_buffer cb_s;


int parseParameters(int argc, char *argv[]){
  int n = 10;
  if (argc == 3 && argv[1][1] == 'n') {
    sscanf(argv[2], "%d", &n);
  }
  return n;
}

cb_s* cb_create(int size){
  cb_s *circBuffer = malloc(sizeof(cb_s));
  cbEl_s *prev_element = malloc(sizeof(cbEl_s));
  cbEl_s *first_element = prev_element;
  for (int i = 1; i < size; i ++) {
    prev_element->next = malloc(sizeof(cbEl_s));
    prev_element->line = malloc(MAX_LENGTH);
    prev_element = prev_element->next;
  }
  prev_element->next = first_element;
  prev_element->line = malloc(MAX_LENGTH);
  circBuffer->read = first_element;
  circBuffer->write = first_element;
  return circBuffer;
}

void debug_cb(cb_s *cb){
  cbEl_s *p_write = cb->write;
  cbEl_s *p_read = cb->read;
  cbEl_s *first = cb->write;
  cb->read = cb->write->next;
  
  
  while (cb->write->next != first) {
    printf("CB:%p, S:%p N:%p\n", (void *)cb->write, cb->write->line,(void *)cb->write->next);
    cb->write = cb->read;
    cb->read = cb->read->next;
  }
    printf("CB:%p, S:%p N:%p\n", (void *)cb->write, cb->write->line,(void *)cb->write->next);
  cb->write = p_write;
  cb->read = p_read;
  return;
}

int cb_put(cb_s *cb, char *line){
  memcpy(cb->write->line, line, 10);
  cb->write = cb->write->next;
  return EXIT_SUCCESS;
}

char *cb_get(cb_s *cb){
  if (cb->read == cb->write) {
    return NULL;
  }
  char *line = cb->read->line;
  cb->read = cb->read->next;
  return line;
}

int cb_free(cb_s *cb){
  cbEl_s *first = cb->write;
  cb->read = cb->write->next;
  
  
  while (cb->write->next != first) {
    free(cb->write->line);
    free(cb->write);
    cb->write = cb->read;
    cb->read = cb->read->next;
  }
  
  free(cb->write->line);
  free(cb->write);
  free(cb);
  
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
  int n = parseParameters(argc, argv);
  
  cb_s *cb = cb_create(n);

  char hello[10] = "Hiii";

  debug_cb(cb);

  cb_put(cb, hello);

  printf("%s\n", cb_get(cb));
  printf("%s\n", cb_get(cb));
  

  cb_free(cb);
  
  printf("tail on %d lines\n", n);
  return EXIT_SUCCESS;
}
