#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;            
  int used;            
  struct chunk *next;  
};

struct chunk *flist = NULL; 

void *malloc(size_t size) {
  if (size == 0) return NULL;

  struct chunk *curr = flist;
  struct chunk *prev = NULL;

  while (curr != NULL) {
    if (curr->size >= size) {
      if (prev != NULL) {
        prev->next = curr->next;
      } else {
        flist = curr->next;
      }

      curr->used = size;
      return (void *)(curr + 1);
    }

    prev = curr;
    curr = curr->next;
  }

  int total_size = sizeof(struct chunk) + size;
  struct chunk *new_chunk = (struct chunk *)sbrk(total_size);
  if (new_chunk == (void *)-1) return NULL;

  new_chunk->size = size;
  new_chunk->used = size;
  new_chunk->next = NULL;

  return (void *)(new_chunk + 1);
}

void free(void *memory) {
  if (memory == NULL) return;

  struct chunk *to_free = ((struct chunk *)memory) - 1;
  to_free->used = 0;
  to_free->next = flist;
  flist = to_free;
}