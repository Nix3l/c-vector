#include <stdlib.h>

#ifndef VECTOR_HEADER_FILE_H
#define VECTOR_HEADER_FILE_H

#define VECTOR_INIT_CAPACITY 8
#define VECTOR_GROWTH_RATE 2
#define VECTOR_SHRINK_RATE (1/2)

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
    size_t element_size;
} vector_s;

vector_s create_vector(size_t element_size);
void* vector_get(vector_s* vec, int index);
void vector_add(vector_s* vec, void* data);
void vector_remove(vector_s* vec, int index);
void vector_free(vector_s* vec);

#endif
