#include <stdio.h>
#include <string.h>

#include "vector.h"

/* 
 * implementation of c++/rust like vectors in c
 * using a double void pointer, we can get the illusion of an
 * array that can vary in size as fits
 *
 *          size => length of the vector
 *      capacity => maximum available memory of the vector
 *  element size => how big is one unit of data (size of type being stored)
 *
 *  NOTE(05/11/22): this implementation is complete. please DO NOT touch it under *ANY* circumstances
 *  
 *  while it is technically possible to store multiple types within one vector,
 *  it would entail keeping track of the element size when removing and adding data,
 *  so i simply opt not to
 */

vector_s create_vector(size_t element_size) {
    vector_s vec;
    vec.size = 0;
    vec.element_size = element_size;
    vec.capacity = VECTOR_INIT_CAPACITY;
    vec.data = malloc(element_size * vec.capacity);
    
    // printf("created new vector with size, element size and capacity: %zu, %zu, %zu\n", vec.size, vec.element_size, vec.capacity);

    return vec;
}

void vector_resize(vector_s* vec, size_t new_capacity) {
    if(new_capacity == 0) {
        printf("vector_resize(): cant resize vector with a capacity of zero\n");
        return;
    }

    size_t new_data_size = vec->element_size * new_capacity;
    void** new_data = realloc(vec->data, new_data_size);

    // printf("new size %zu, new capacity %zu\n", new_data_size, new_capacity);
    
    if(new_data == NULL) {
        printf("vector_resize(): couldnt resize vector\n");
        return;
    }

    vec->capacity = new_capacity;
    vec->data = new_data;
}

void* vector_get(vector_s* vec, int index) {
    if(vec == NULL) { 
        printf("invalid vector pointer\n");
        return NULL;
    }

    if(index > vec->size || index < 0) {
        printf("index out of bounds!\n");
        return NULL;
    }

    return vec->data[index];
}

void vector_add(vector_s* vec, void* new_data) {
    if(vec == NULL) { 
        printf("vector_add(): invalid vector pointer\n");
        return;
    }

    vector_resize(vec, vec->capacity + 1);
    vec->size++;
    void* dest = vec->data + vec->size * vec->element_size;
    memcpy(dest, new_data, vec->element_size);
}


void vector_remove(vector_s* vec, int index) {
    if(vec == NULL) { 
        printf("vector_remove(): invalid vector pointer\n");
        return;
    }

    if(index > vec->size || index < 0) {
        printf("vector_remove(): index out of bounds!\n");
        return;
    }

    vec->data[index] = NULL;

    for(int i = index; i < vec->size; i ++) {
        vec->data[i] = vec->data[i + 1];
        vec->data[i + 1] = NULL;
    }

    vec->size--;

    if(vec->size < 0) {
        vec->size = 0;
        return;
    }

    vector_resize(vec, vec->capacity - 1);
}

void vector_free(vector_s* vec) {
    if(vec == NULL) {
        printf("vector_free(): invalid vector pointer\n");
        return;
    }

    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
}
