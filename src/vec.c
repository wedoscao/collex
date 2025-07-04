#include "../include/vec.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPAPACITY 1

void __data_destroy(void *data) { free(data); }

void __vec_grow(void **vec, unsigned int *cap, unsigned int data_size) {
    size_t new_cap = (*vec == NULL) ? INITIAL_CAPAPACITY : (*cap * 2);
    void *new_data = realloc(*vec, data_size * new_cap);
    if (!new_data) {
        fprintf(stderr, "reallocate data error\n");
        exit(EXIT_FAILURE);
    }
    *vec = new_data;
    *cap = new_cap;
}

void *__vec_access(void *data, unsigned int len, unsigned int index,
                   unsigned int data_size) {
    if (index >= len) {
        fprintf(stderr, "indexing out of bound error\n");
        exit(EXIT_FAILURE);
    }

    return (char *)data + index * data_size;
}
