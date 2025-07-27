/**
 *  @file collex_vector.h
 *  @brief A generic vector struct with utility functions.
 *
 *  Copyright 2025, Sang H. Cao, All Rights Reserved
 *
 *  @author Sang H. Cao
 */
#ifndef __COLLEX_VECTOR_
#define __COLLEX_VECTOR_
#define __COLLEX_VECTOR_INIT_CAP_ 4

#include <stddef.h>

/**
 * @brief A generic dynamic array (vector) structure.
 *
 * This structure represents a resizable array of elements of any type.
 * It stores element data in a contiguous memory buffer and grows automatically
 * when new elements are added beyond its current capacity.
 */
typedef struct {
    void *buffer;
    size_t len;
    size_t cap;
    size_t elem_size;

    /**
     *  @brief Comparison function for elements in the vector.
     *  @param x Pointer to the first element.
     *  @param y Pointer to the second element.
     *  @return -1 if *x < *y, 0 if *x == *y, 1 if *x > *y.
     */
    int (*cmp)(void *x, void *y);
} collex_vector_t;

/**
 *  @brief Initializes a new vector.
 *  @param elem_size Size of element.
 *  @param cmp Pointer to the comparison function for elements in vector.
 *  @return Pointer to a newly allocated vector instance or NULL on failure.
 */
collex_vector_t *collex_vector_init(size_t elem_size, int (*cmp)(void *, void *));

/**
 *  @brief Frees all resources associated with the vector.
 *  @param vector Pointer to the vector instance.
 */
void collex_vector_free(collex_vector_t *vector);

/**
 *  @brief Pushes a new element into the vector.
 *  @param vector Pointer to the vector instance.
 *  @param value Pointer to the element to be added.
 *  @return 0 on success or -1 if memory allocation fails.
 */
int collex_vector_push(collex_vector_t *vector, const void *value);

/**
 *  @brief Pops the last element from the vector.
 *  @param vector Pointer to the vector instance.
 *  @param buffer Pointer to the memory where the popped element will be stored.
 *  @return 0 on success or -1 if the vector is empty.
 */
int collex_vector_pop(collex_vector_t *vector, void *buffer);

/**
 *  @brief Retrieves the pointer to element at a specific index in the vector.
 *  The returned pointer should be cast to the appropriate type before use.
 *  @param vector Pointer to the vector instance.
 *  @param index Index of the element (0-based).
 *  @return Pointer to the retrieved element or NULL if the index is out of range.
 */
const void *collex_vector_get(collex_vector_t *vector, size_t index);

/**
 *  @brief Replaces the element at the specified index in the vector.
 *  @param vector Pointer to the vector instance.
 *  @param index Position where the new element will be set (0-based).
 *  @param value Pointer to the element to be set.
 *  @return 0 on success or -1 if the index is out of range.
 */
int collex_vector_set(collex_vector_t *vector, size_t index, const void *value);

/**
 *  @brief Inserts a new element at the specified index in the vector.
 *  @param vector Pointer to the vector instance.
 *  @param index Position where the new element will be inserted (0-based).
 *  @param value Pointer to the element to insert.
 *  @return 0 on success or -1 if the index is out of range or memory allocation fails.
 */
int collex_vector_insert(collex_vector_t *vector, size_t index, const void *value);

/**
 *  @brief Removes the element at the specified index from the vector.
 *  @param vector Pointer to the vector instance.
 *  @param index Position where the element will be removed (0-based).
 *  @return 0 on success or -1 if the index is out of range.
 */
int collex_vector_remove(collex_vector_t *vector, size_t index);

#endif
