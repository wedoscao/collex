#include "collex_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_free(void *x) { free(x); }

int int_compare(void *x, void *y) {
    int a = *(int *)x;
    int b = *(int *)y;
    return (a > b) - (a < b);
}

int *make_int(int val) {
    int *ptr = malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

void test_list_init_invalid() {
    assert(collex_list_init(sizeof(int), NULL, int_compare) == NULL);
    assert(collex_list_init(sizeof(int), int_free, NULL) == NULL);
    printf("test_list_init_invalid passed\n");
}

void test_list_init_free() {
    collex_list_t *list = collex_list_init(sizeof(int), int_free, int_compare);
    assert(list != NULL);
    assert(list->len == 0);
    assert(collex_list_free(list) == 0);
    printf("test_list_init_free passed\n");
}

void test_list_push_get() {
    collex_list_t *list = collex_list_init(sizeof(int), int_free, int_compare);
    for (int i = 0; i < 5; ++i) {
        int *val = make_int(i * 10);
        assert(collex_list_push(list, val) == 0);
        free(val);
    }
    assert(list->len == 5);
    for (int i = 0; i < 5; ++i) {
        const int *val = (const int *)collex_list_get(list, i);
        assert(val && *val == i * 10);
    }
    collex_list_free(list);
    printf("test_list_push_get passed\n");
}

void test_list_set() {
    collex_list_t *list = collex_list_init(sizeof(int), int_free, int_compare);
    for (int i = 0; i < 3; ++i) {
        int *val = make_int(i);
        collex_list_push(list, val);
        free(val);
    }

    int new_val = 42;
    assert(collex_list_set(list, 1, &new_val) == 0);
    const int *retrieved = collex_list_get(list, 1);
    assert(retrieved && *retrieved == 42);

    collex_list_free(list);
    printf("test_list_set passed\n");
}

void test_list_insert_remove() {
    collex_list_t *list = collex_list_init(sizeof(int), int_free, int_compare);
    for (int i = 0; i < 3; ++i) {
        int *val = make_int(i + 1);
        collex_list_push(list, val);
        free(val);
    }

    int x = 99;
    assert(collex_list_insert(list, 1, &x) == 0);
    assert(list->len == 4);
    const int *val = collex_list_get(list, 1);
    assert(val && *val == 99);

    assert(collex_list_remove(list, 1) == 0);
    val = collex_list_get(list, 1);
    assert(val && *val == 2);

    collex_list_free(list);
    printf("test_list_insert_remove passed\n");
}

void test_list_pop() {
    collex_list_t *list = collex_list_init(sizeof(int), int_free, int_compare);
    for (int i = 0; i < 3; ++i) {
        int *val = make_int(i);
        collex_list_push(list, val);
        free(val);
    }

    int out;
    assert(collex_list_pop(list, &out) == 0);
    assert(out == 2);
    assert(list->len == 2);

    assert(collex_list_pop(list, &out) == 0);
    assert(out == 1);

    assert(collex_list_pop(list, &out) == 0);
    assert(out == 0);

    assert(collex_list_pop(list, &out) == -1);

    collex_list_free(list);
    printf("test_list_pop passed\n");
}

int main(void) {
    test_list_init_invalid();
    test_list_init_free();
    test_list_push_get();
    test_list_set();
    test_list_insert_remove();
    test_list_pop();

    printf("All list tests passed!\n");
    return 0;
}
