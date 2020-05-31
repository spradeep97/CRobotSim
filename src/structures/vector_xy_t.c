// Copyright 2020 | Pradeep Suresh | University of Michigan
#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/vector_xy_t.h"

void vector_init(vector_xy_t *v) {
    v->cap = VECTOR_INIT_CAPACITY;
    v->data = malloc(sizeof(*v->data) * v->cap);
    v->size = 0;
}

void vector_resize(vector_xy_t *v, int capacity) {
    void *memory = realloc(v->data, sizeof(*v->data) * capacity);
    if (memory) {
        v->data = memory;
        v->cap = capacity;
    } else {
        fprintf(stderr, "Could not reallocate memory to vector_xy_t.\n");
        exit(1);
    }
}

void vector_add(vector_xy_t *v, double x, double y) {
    if (v->cap == v->size) {
        vector_resize(v, v->cap * 2);
    }
    v->data[v->size].x = x;
    v->data[v->size].y = y;
    v->size++;
}

point_t vector_get_min(vector_xy_t *v) {
    point_t min = {0};
    for (int i = 0; i < v->size; i++) {
        if (v->data[i].x < min.x) {
            min.x = v->data[i].x;
        }
        if (v->data[i].y < min.y) {
            min.y = v->data[i].y;
        }
    }
    return min;
}

void print_vec(vector_xy_t *v) {
    for (int i = 0; i < v->size; i++) {
        printf("%.3f|", v->data[i].x);
        printf("%.3f , ", v->data[i].y);
    }
    printf("\n");
}

void vector_free(vector_xy_t *v) {
    free(v->data);
}
