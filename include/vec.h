/**
 * @file vec.h
 * @brief Generic macro-based dynamic array (vector) for C.
 *
 * This header provides a type-safe, macro-based vector implementation
 * that allows defining and managing dynamic arrays of any type in C.
 */

#ifndef __COLLEX_VEC_H
#define __COLLEX_VEC_H

/**
 * @def Vec(T)
 * @brief Declares a generic vector for type T.
 *
 * This macro expands to a struct containing:
 * - a dynamic array of type T (`data`)
 * - the current length (`len`)
 * - the allocated capacity (`cap`)
 */
#define Vec(T)                                                                 \
    struct {                                                                   \
        T *data;                                                               \
        unsigned int len;                                                      \
        unsigned int cap;                                                      \
    }

/**
 * @def vec_init(vec)
 * @brief Initializes the given vector.
 *
 * Sets the vector’s internal pointer to NULL, and both its length and
 * capacity to 0.
 */
#define vec_init(vec)                                                          \
    do {                                                                       \
        (vec).data = (void *)0;                                                \
        (vec).len = 0;                                                         \
        (vec).cap = 0;                                                         \
    } while (0)

/**
 * @def vec_free(vec)
 * @brief Frees the memory allocated by the vector.
 *
 * Releases the dynamic array inside the vector and resets length and
 * capacity to 0.
 */
#define vec_free(vec)                                                          \
    do {                                                                       \
        void *data = (void *)vec.data;                                         \
        __data_destroy(data);                                                  \
        vec.len = 0;                                                           \
        vec.cap = 0;                                                           \
    } while (0)

/**
 * @def vec_push(vec, value)
 * @brief Appends a value to the end of the vector.
 *
 * If the vector is full, it automatically reallocates to double its
 * capacity.
 */
#define vec_push(vec, value)                                                   \
    do {                                                                       \
        if (vec.len == vec.cap) {                                              \
            __vec_grow((void **)&vec, &vec.cap, sizeof(*vec.data));            \
        }                                                                      \
        vec.data[vec.len++] = value;                                           \
    } while (0)

/**
 * @def vec_get(vec, index, T)
 * @brief Returns the value at the given index in the vector.
 *
 * Performs bounds checking before accessing the internal array.
 *
 * @param vec The vector to access.
 * @param index The index to retrieve.
 * @param T The type of the vector element.
 *
 * @return The value at the specified index.
 */
#define vec_get(vec, index, T)                                                 \
    *(T *)__vec_access(vec.data, vec.len, index, sizeof(T))

/**
 * @brief Destroys the internal dynamic array.
 *
 * @param data Pointer to the memory to be freed.
 */
void __data_destroy(void *data);

/**
 * @brief Grows the capacity of a vector's storage.
 *
 * Doubles the capacity and reallocates the internal buffer.
 *
 * @param vec Pointer to the vector's internal struct pointer.
 * @param cap Pointer to the capacity value to update.
 * @param data_size Size of each element (use sizeof(T)).
 */
void __vec_grow(void **vec, unsigned int *cap, unsigned int data_size);

/**
 * @brief Accesses an element in the vector's internal data array.
 *
 * Performs bounds checking to ensure safety.
 *
 * @param data Pointer to the vector’s internal data.
 * @param len Current length of the vector.
 * @param index Index to access.
 * @param data_size Size of each element in the array.
 *
 * @return Pointer to the element at the given index.
 */
void *__vec_access(void *data, unsigned int len, unsigned int index,
                   unsigned int data_size);
#endif // __COLLEX_VEC_H
