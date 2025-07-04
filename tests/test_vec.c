#include "../include/vec.h"
#include <stdio.h>
#include <stdlib.h>

#define panic(format, ...)                                                     \
    do {                                                                       \
        fprintf(stderr, format, __VA_ARGS__);                                  \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

int main() {
    Vec(int) vec;
    vec_init(vec);

    for (unsigned int i = 0; i < 10; i++) {
        vec_push(vec, i);
    }

    for (unsigned int i = 0; i < vec.len; i++) {
        int x = vec_get(vec, i, int);
        if (x != i) {
            panic("%d != %d\n", x, i);
        }
    }
    printf("test_vec succeeded\n");

    vec_free(vec);
    return 0;
}
