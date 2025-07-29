#include "collex_list.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

collex_list_t *collex_list_init(size_t mem_size, void (*free)(void *), int (*compare)(void *, void *)) {
    if (!free || !compare) {
        return NULL;
    }

    collex_list_t *list = malloc(sizeof(collex_list_t));
    if (!list) {
        return NULL;
    }

    list->len = 0;
    list->mem_size = mem_size;
    list->sentinel = NULL;
    list->free = free;
    list->compare = compare;
    return list;
}

int collex_list_free(collex_list_t *list) {
    if (!list) {
        return 0;
    }

    if (!list->free) {
        return -1;
    }

    collex_list_node_t *curr_node = list->sentinel;
    while (curr_node) {
        collex_list_node_t *next_node = curr_node->next;
        list->free(curr_node->value);
        free(curr_node);
        curr_node = next_node;
    }

    free(list);

    return 0;
};

const void *collex_list_get(collex_list_t *list, size_t index) {
    if (!list) {
        return NULL;
    }

    if (index >= list->len) {
        return NULL;
    }

    collex_list_node_t *target = list->sentinel;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    return target->value;
};

int collex_list_set(collex_list_t *list, size_t index, const void *value) {
    if (!list) {
        return -1;
    }

    if (index >= list->len) {
        return -1;
    }

    collex_list_node_t *target = list->sentinel;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    if (!target->value) {
        return -1;
    }
    memcpy(target->value, value, list->mem_size);

    return 0;
};

int collex_list_push(collex_list_t *list, const void *value) {
    if (!list || !value) {
        return -1;
    }

    collex_list_node_t *new_node = malloc(sizeof(collex_list_node_t));
    if (!new_node) {
        return -1;
    }
    new_node->value = malloc(list->mem_size);
    if (!new_node->value) {
        free(new_node);
        return -1;
    }
    memcpy(new_node->value, value, list->mem_size);
    new_node->next = NULL;

    if (!list->sentinel) {
        new_node->prev = NULL;
        list->sentinel = new_node;
    } else {
        collex_list_node_t *last = list->sentinel;
        while (last->next) {
            last = last->next;
        }

        last->next = new_node;
        new_node->prev = last;
    }

    list->len++;
    return 0;
};

int collex_list_pop(collex_list_t *list, void *buffer) {
    if (!list || !buffer) {
        return -1;
    }

    if (list->len == 0) {
        return -1;
    }

    collex_list_node_t *last = list->sentinel;
    while (last->next) {
        last = last->next;
    }
    memcpy(buffer, last->value, list->mem_size);

    if (last->prev) {
        last->prev->next = NULL;
    } else {
        list->sentinel = NULL;
    }

    list->free(last->value);
    free(last);

    list->len--;
    return 0;
};

int collex_list_insert(collex_list_t *list, size_t index, const void *value) {
    if (!list || !value) {
        return -1;
    }

    if (index == list->len) {
        if (collex_list_push(list, value) == -1) {
            return -1;
        };
        return 0;
    }

    if (index > list->len) {
        return -1;
    }

    collex_list_node_t *target = list->sentinel;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    collex_list_node_t *new_node = malloc(sizeof(collex_list_node_t));
    if (!new_node) {
        return -1;
    }

    new_node->value = malloc(list->mem_size);
    if (!new_node->value) {
        free(new_node);
        return -1;
    }
    memcpy(new_node->value, value, list->mem_size);

    new_node->prev = target->prev;
    new_node->next = target;

    if (target->prev) {
        target->prev->next = new_node;
    } else {
        list->sentinel = new_node;
    }

    target->prev = new_node;

    list->len++;
    return 0;
};

int collex_list_remove(collex_list_t *list, size_t index) {
    if (!list) {
        return -1;
    }

    if (index >= list->len) {
        return -1;
    }

    collex_list_node_t *target = list->sentinel;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }

    if (target->prev) {
        target->prev->next = target->next;
    } else {
        list->sentinel = target->next;
    }

    if (target->next) {
        target->next->prev = target->prev;
    }

    list->free(target->value);
    free(target);
    list->len--;
    return 0;
};
