// tail.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Ondřej Přibyl, FIT
// Přeloženo: gcc 12.2.1

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


FILE *parseParameters(int argc, char *argv[], int *n){
  *n = 10;
  FILE *fp = NULL;
  switch (argc) {
    case 2:
      fp = fopen(argv[1], "r");
    break;
    case 4:
      fp = fopen(argv[3], "r");
      __attribute__ ((fallthrough));
    case 3:
      sscanf(argv[2], "%d", n);
    break;
  }
  return fp;
}

cb_s* cb_create(int size){
  cb_s *circBuffer = malloc(sizeof(cb_s));
  cbEl_s *prev_element = malloc(sizeof(cbEl_s));
  cbEl_s *first_element = prev_element;
  for (int i = 0; i < size; i ++) {
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
  if (cb->write->next == cb->read) {
    cb->read = cb->read->next;
  }
  memcpy(cb->write->line, line, strlen(line) + 1);
  cb->write = cb->write->next;
  return EXIT_SUCCESS;
}

char *cb_get(cb_s *cb){
  char *line = cb->read->line;
  cb->read = cb->read->next;
  return line;
}

int cb_free(cb_s *cb){
  cbEl_s *first = cb->write;
  cb->read = cb->write->next;
  
  
  do {
    if (cb->write->line != NULL) {
      free(cb->write->line);
    }
    free(cb->write);
    cb->write = cb->read;
    cb->read = cb->read->next;
  }
  while (cb->write->next != first) ;
  
  free(cb->write->line);
  free(cb->write);
  free(cb);
  
  return EXIT_SUCCESS;
}

int read_buffer(cb_s *cb, FILE *fp){
  int length = 0;
  int c = 0;
  char line[MAX_LENGTH] = {0};
  
  do {
    c = fgetc(fp);
    if (c == '\n') {
      cb_put(cb, line);
      memset(line, 0, MAX_LENGTH);
      length = 0;
    }
    else {
      line[length] = c;
      length++;
      if (length >= MAX_LENGTH - 1) {
        cb_put(cb, line);
        memset(line, 0, MAX_LENGTH);
        length = 0;
        while (c != '\n' && c != EOF) {
          c = fgetc(fp);
        }
      }
    }
  }
  while (c != EOF);
  return EXIT_SUCCESS;
}

void print_cb(cb_s *cb){
  while (cb->read != cb->write) {
    printf("%s\n", cb_get(cb));
  }
}

int main(int argc, char *argv[])
{
  int np;
  int *n = &np;
  
  FILE *fp = parseParameters(argc, argv, n);
  
  cb_s *cb = cb_create(*n);
  
  if (fp == NULL) {
    read_buffer(cb, stdin);
  }
  else {
    read_buffer(cb, fp);
  }
  
  print_cb(cb);

  
  
  cb_free(cb);
  
  return EXIT_SUCCESS;
}
