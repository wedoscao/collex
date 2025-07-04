#ifndef __COLLEX_VEC_H
#define __COLLEX_VEC_H
#define Vec(T)                                                                 \
    struct {                                                                   \
        T *data;                                                               \
        unsigned int len;                                                      \
        unsigned int cap;                                                      \
    }

#define vec_init(vec)                                                          \
    do {                                                                       \
        (vec).data = (void *)0;                                                \
        (vec).len = 0;                                                         \
        (vec).cap = 0;                                                         \
    } while (0)

#define vec_free(vec)                                                          \
    do {                                                                       \
        void *data = (void *)vec.data;                                         \
        __data_destroy(data);                                                  \
        vec.len = 0;                                                           \
        vec.cap = 0;                                                           \
    } while (0)

#define vec_push(vec, value)                                                   \
    do {                                                                       \
        if (vec.len == vec.cap) {                                              \
            __vec_grow((void **)&vec, &vec.cap, sizeof(*vec.data));            \
        }                                                                      \
        vec.data[vec.len++] = value;                                           \
    } while (0)

#define vec_get(vec, index, T)                                                 \
    *(T *)__vec_access(vec.data, vec.len, index, sizeof(T))

void __data_destroy(void *data);
void __vec_grow(void **vec, unsigned int *cap, unsigned int dataSize);
void *__vec_access(void *data, unsigned int len, unsigned int index,
                   unsigned int dataSize);

#endif
