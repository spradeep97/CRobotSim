// Copyright 2020 | Pradeep Suresh | University of Michigan
#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/vector_xy_i32_t.h"

void vector_xy_i32_init(vector_xy_i32_t *v) {
    v->cap = VECTOR_INIT_CAPACITY;
    v->data = malloc(sizeof(*v->data) * v->cap);
    v->size = 0;
}

void vector_xy_i32_resize(vector_xy_i32_t *v, int capacity) {
    void *memory = realloc(v->data, sizeof(*v->data) * capacity);
    if (memory) {
        v->data = memory;
        v->cap = capacity;
    } else {
        fprintf(stderr, "Could not reallocate memory to vector_xy_i32_t.\n");
        exit(1);
    }
}

void vector_xy_i32_add(vector_xy_i32_t *v, int32_t x, int32_t y) {
    if (v->cap == v->size) {
        vector_xy_i32_resize(v, v->cap * 2);
    }
    v->data[v->size].x = x;
    v->data[v->size].y = y;
    v->size++;
}

void vector_xy_i32_clear(vector_xy_i32_t *v) {
    for (int i = 0; i < v->size; i++) {
        v->data[i].x = 0;
        v->data[i].y = 0;
    }
}

void vector_xy_i32_print(vector_xy_i32_t *v) {
    for (int i = 0; i < v->size; i++) {
        printf("%d|", v->data[i].x);
        printf("%d , ", v->data[i].y);
    }
    printf("\n");
}

void vector_xy_i32_free(vector_xy_i32_t *v) {
    free(v->data);
    // free(v);
}
