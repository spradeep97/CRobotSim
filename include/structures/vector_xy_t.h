// Copyright 2020 | Pradeep Suresh | University of Michigan
#pragma once
#include <stdint.h>
#include "./geometry.h"

#define VECTOR_INIT_CAPACITY 4

typedef struct vector {
    point_t *data;
    int size;
    int cap;
} vector_xy_t;

// Allocates some memory and gives that address to v
void vector_init(vector_xy_t *v);

// Resizes the vector to specified capacity
void vector_resize(vector_xy_t *v, int capacity);

// Appends an element to the vector
void vector_add(vector_xy_t *v, double x, double y);

// Returns the minimum element of the vector
point_t vector_get_min(vector_xy_t *v);

// Prints all elements of the vector
void print_vec(vector_xy_t *v);

// Frees the malloced memory
void vector_free(vector_xy_t *v);
