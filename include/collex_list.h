/**
 *  @file collex_list.h
 *  @brief A generic linked list struct with utility functions.
 *
 *  Copyright 2025, Sang H. Cao, All Rights Reserved
 *
 *  @author Sang H. Cao
 */
#ifndef __COLLEX_LIST_
#define __COLLEX_LIST_

#include <stddef.h>

/**
 * @brief A node in a doubly linked list.
 *
 * Represents a single element in the list, storing a pointer to the value
 * and links to the previous and next nodes. This structure enables
 * bidirectional traversal of the list.
 */
typedef struct collex_list_node {
    void *value;
    struct collex_list_node *prev, *next;
} collex_list_node_t;

/**
 * @brief A generic doubly linked list structure.
 *
 * This structure represents a dynamically sized, bidirectionally linked list
 * capable of storing elements of any type using `void *` pointers. It supports
 * custom element deallocation and comparison through user-defined functions.
 */
typedef struct {
    size_t len;
    size_t mem_size;
    collex_list_node_t *sentinel;

    /**
     * @brief A function pointer used to free individual elements in the list.
     * @param value Pointer to the value to be freed.
     */
    void (*free)(void *value);

    /**
     *  @brief Comparison function for elements in the linked list.
     *  @param x Pointer to the first element.
     *  @param y Pointer to the second element.
     *  @return -1 if *x < *y, 0 if *x == *y, 1 if *x > *y.
     */
    int (*compare)(void *x, void *y);
} collex_list_t;

/**
 * @brief Initializes a new empty doubly linked list with custom behavior.
 * @param mem_size Size of member.
 * @param free Function pointer used to free individual node values. Must not be NULL.
 * @param compare Function pointer used to compare two elements. Must not be NULL.
 * @return Pointer to a new list instance, or NULL on allocation failure.
 */
collex_list_t *collex_list_init(size_t mem_size, void (*free)(void *value), int (*compare)(void *x, void *y));

/**
 * @brief Frees all memory used by the list and its elements.
 * @param list Pointer to the list to be freed.
 * @return 0 on success, -1 if the list's free function is NULL.
 */
int collex_list_free(collex_list_t *list);

/**
 * @brief Retrieves the value at a specific index.
 * @param list Pointer to the list.
 * @param index Index of the element to retrieve.
 * @return Pointer to the value at the given index, or NULL if index is invalid.
 */
const void *collex_list_get(collex_list_t *list, size_t index);

/**
 * @brief Replaces the value at a specific index with a new one.
 * @param list Pointer to the list.
 * @param index Index of the element to replace.
 * @param value Pointer to the new value.
 * @return 0 on success, -1 if the index is out of bounds or input is invalid.
 */
int collex_list_set(collex_list_t *list, size_t index, const void *value);

/**
 * @brief Appends a new element to the end of the list.
 * @param list Pointer to the list.
 * @param value Pointer to the value to insert.
 * @return 0 on success, -1 on failure (e.g., NULL input or allocation failure).
 */
int collex_list_push(collex_list_t *list, const void *value);

/**
 * @brief Removes and returns the last element in the list.
 * @param list Pointer to the list.
 * @param buffer Pointer to the memory where the popped element will be stored.
 * @return Pointer to the removed value, or NULL if the list is empty or invalid.
 */
int collex_list_pop(collex_list_t *list, void *buffer);

/**
 * @brief Inserts a new element at a specific index.
 * @param list Pointer to the list.
 * @param index Index at which to insert the new element.
 * @param value Pointer to the value to insert.
 * @return 0 on success, -1 if index is out of bounds or on allocation failure.
 */
int collex_list_insert(collex_list_t *list, size_t index, const void *value);

/**
 * @brief Removes the element at a specific index.
 * @param list Pointer to the list.
 * @param index Index of the element to remove.
 * @return 0 on success, -1 if the index is out of bounds or the list is invalid.
 */
int collex_list_remove(collex_list_t *list, size_t index);

#endif
