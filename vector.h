#include <stdlib.h>

#ifndef VECTOR_HEADER_FILE_H
#define VECTOR_HEADER_FILE_H

#define VECTOR_INIT_CAPACITY 8

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
} vector_s;

vector_s create_vector();
void* vector_get(vector_s* vec, size_t index);
void vector_add(vector_s* vec, void* data);
void vector_remove(vector_s* vec, size_t index);
void vector_free(vector_s* vec);

#endif
