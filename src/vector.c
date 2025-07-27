#include "collex_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int reallocate(collex_vector_t *vector, size_t n_member) {
    void *new_buffer = realloc(vector->buffer, n_member * vector->elem_size);
    if (!new_buffer) {
        return -1;
    }
    vector->buffer = new_buffer;
    vector->cap = n_member;
    return 0;
}

collex_vector_t *collex_vector_init(size_t elem_size, int (*cmp)(void *, void *)) {
    if (elem_size == 0) {
        return NULL;
    }

    collex_vector_t *vector = malloc(sizeof(collex_vector_t));
    if (!vector) {
        return NULL;
    }

    vector->elem_size = elem_size;
    vector->cap = __COLLEX_VECTOR_INIT_CAP_;
    vector->len = 0;
    vector->cmp = cmp;

    vector->buffer = calloc(vector->cap, elem_size);
    if (!vector->buffer) {
        free(vector);
        return NULL;
    }
    return vector;
}

void collex_vector_free(collex_vector_t *vector) {
    if (!vector) {
        return;
    }

    free(vector->buffer);
    vector->buffer = NULL;

    free(vector);
}

int collex_vector_push(collex_vector_t *vector, const void *value) {
    if (vector->len == vector->cap) {
        if (reallocate(vector, vector->cap ? vector->cap * 2 : 1) == -1) {
            return -1;
        }
    }

    void *target = (char *)vector->buffer + (vector->len * vector->elem_size);
    memcpy(target, value, vector->elem_size);
    vector->len++;
    return 0;
}

int collex_vector_pop(collex_vector_t *vector, void *buffer) {
    if (!vector || vector->len == 0) {
        return -1;
    }

    void *src = (char *)vector->buffer + (vector->len - 1) * vector->elem_size;

    if (buffer) {
        memcpy(buffer, src, vector->elem_size);
    }

    vector->len--;

    return 0;
}

const void *collex_vector_get(collex_vector_t *vector, size_t index) {
    if (!vector || index >= vector->len) {
        return NULL;
    }
    void *target = (char *)vector->buffer + (index * vector->elem_size);
    return target;
}

int collex_vector_set(collex_vector_t *vector, size_t index, const void *value) {
    if (!vector || index >= vector->len) {
        return -1;
    }
    void *target = (char *)vector->buffer + (index * vector->elem_size);
    memcpy(target, value, vector->elem_size);
    return 0;
}

int collex_vector_insert(collex_vector_t *vector, size_t index, const void *value) {
    if (!vector || index > vector->len) {
        return -1;
    }
    if (vector->len == vector->cap) {
        if (reallocate(vector, vector->cap ? vector->cap * 2 : 1) == -1) {
            return -1;
        }
    }
    void *start = (char *)vector->buffer + index * vector->elem_size;
    if (index < vector->len) {
        void *end = (char *)vector->buffer + (index + 1) * vector->elem_size;
        memmove(end, start, (vector->len - index) * vector->elem_size);
    }
    memcpy(start, value, vector->elem_size);
    vector->len++;
    return 0;
}

int collex_vector_remove(collex_vector_t *vector, size_t index) {
    if (!vector || index >= vector->len) {
        return -1;
    }
    void *src = (char *)vector->buffer + (index + 1) * vector->elem_size;
    void *dest = (char *)vector->buffer + index * vector->elem_size;
    memmove(dest, src, (vector->len - index - 1) * vector->elem_size);
    vector->len--;
    return 0;
}
