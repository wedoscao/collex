#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int int_cmp(void *x, void *y) {
    int a = *(int *)x;
    int b = *(int *)y;
    return (a > b) - (a < b);
}

void test_vector_init_free() {
    collex_vector_t *vec = collex_vector_init(sizeof(int), int_cmp);
    assert(vec != NULL);
    assert(vec->len == 0);
    assert(vec->cap > 0);
    collex_vector_free(vec);
    printf("test_vector_init_free passed\n");
}

void test_vector_push_get() {
    collex_vector_t *vec = collex_vector_init(sizeof(int), int_cmp);
    int x = 10;
    assert(collex_vector_push(vec, &x) == 0);
    assert(vec->len == 1);
    const int *val = collex_vector_get(vec, 0);
    assert(val != NULL && *val == 10);
    collex_vector_free(vec);
    printf("test_vector_push_get passed\n");
}

void test_vector_pop() {
    collex_vector_t *vec = collex_vector_init(sizeof(int), int_cmp);
    int x = 20, y;
    collex_vector_push(vec, &x);
    assert(collex_vector_pop(vec, &y) == 0);
    assert(y == 20);
    assert(vec->len == 0);
    assert(collex_vector_pop(vec, &y) == -1);
    collex_vector_free(vec);
    printf("test_vector_pop passed\n");
}

void test_vector_set() {
    collex_vector_t *vec = collex_vector_init(sizeof(int), int_cmp);
    int a = 5, b = 15;
    collex_vector_push(vec, &a);
    assert(collex_vector_set(vec, 0, &b) == 0);
    const int *val = collex_vector_get(vec, 0);
    assert(val && *val == 15);
    assert(collex_vector_set(vec, 5, &b) == -1);
    collex_vector_free(vec);
    printf("test_vector_set passed\n");
}

void test_vector_insert_remove() {
    collex_vector_t *vec = collex_vector_init(sizeof(int), int_cmp);
    int a = 1, b = 2, c = 3;
    collex_vector_push(vec, &a);
    collex_vector_push(vec, &c);
    assert(collex_vector_insert(vec, 1, &b) == 0);
    assert(vec->len == 3);
    const int *val1 = collex_vector_get(vec, 1);
    assert(val1 && *val1 == 2);
    assert(collex_vector_remove(vec, 1) == 0);
    const int *val2 = collex_vector_get(vec, 1);
    assert(val2 && *val2 == 3);
    assert(collex_vector_remove(vec, 10) == -1);
    collex_vector_free(vec);
    printf("test_vector_insert_remove passed\n");
}

int main() {
    test_vector_init_free();
    test_vector_push_get();
    test_vector_pop();
    test_vector_set();
    test_vector_insert_remove();
    printf("All vector tests passed!\n");
    return 0;
}
