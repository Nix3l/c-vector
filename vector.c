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
 *
 *  NOTE(05/11/22): this implementation is complete. please DO NOT touch it under *ANY* circumstances
 *  NOTE(14/11/22): ok NOW this implementation is complete. please for the love of god DO NOT TOUCH UNDER **ANY** CIRCUMSTANCES
 *  
 */

vector_s create_vector() {
    vector_s vec;
    vec.size = 0;
    vec.capacity = VECTOR_INIT_CAPACITY;
    vec.data = malloc(sizeof(void*) * vec.capacity);

    return vec;
}

void vector_resize(vector_s* vec, size_t new_capacity) {
    if(new_capacity == 0) {
        printf("vector_resize(): cant resize vector with a capacity of zero\n");
        return;
    }

    void** new_data = realloc(vec->data, sizeof(void*) * new_capacity);
    
    if(new_data == NULL) {
        printf("vector_resize(): couldnt resize vector\n");
        return;
    }

    vec->capacity = new_capacity;
    vec->data = new_data;
}

void* vector_get(vector_s* vec, size_t index) {
    if(vec == NULL) { 
        printf("invalid vector pointer\n");
        return NULL;
    }

    if(index >= vec->size || index < 0) {
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
    vec->data[vec->size++] = new_data;
}


void vector_remove(vector_s* vec, size_t index) {
    if(vec == NULL) { 
        printf("vector_remove(): invalid vector pointer\n");
        return;
    }

    if(index >= vec->size || index < 0) {
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
