// Copyright 2020 | Pradeep Suresh | University of Michigan
#pragma once

#include "./pixel_t.h"

#define VECTOR_INIT_CAPACITY 4

typedef struct vector_xy_i32 {
    pixel_t *data;
    int size;
    int cap;
} vector_xy_i32_t;

// Allocates some memory and gives that address to v
void vector_xy_i32_init(vector_xy_i32_t *v);

// Resizes the vector to specified capacity
void vector_xy_i32_resize(vector_xy_i32_t *v, int capacity);

// Appends an element to the vector
void vector_xy_i32_add(vector_xy_i32_t *v, int32_t x, int32_t y);

// Clears all the elements to zero value
void vector_xy_i32_clear(vector_xy_i32_t *v);

// Appends an element to the vector
void vector_xy_i32_print(vector_xy_i32_t *v);

// Frees the malloced memory
void vector_xy_i32_free(vector_xy_i32_t *v);
