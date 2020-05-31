// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include "../include/structures/vector_xy_t.h"
#include "../include/structures/vector_xy_i32_t.h"

void test_vector_xy_t(void);
void test_vector_xy_i32_t(void);

int main(void) {
    test_vector_xy_t();
    test_vector_xy_i32_t();
}

void test_vector_xy_t(void) {
    vector_xy_t vector_A;
    vector_init(&vector_A);
    vector_add(&vector_A, 1.0, 2.0);
    vector_add(&vector_A, 3.0, 4.0);
    printf("VectorA:\n");
    print_vec(&vector_A);
    vector_free(&vector_A);
}

void test_vector_xy_i32_t(void) {
    vector_xy_i32_t vector_B;
    vector_xy_i32_init(&vector_B);
    vector_xy_i32_add(&vector_B, 1, 2);
    vector_xy_i32_add(&vector_B, 3, 4);
    printf("VectorB:\n");
    vector_xy_i32_print(&vector_B);
    vector_xy_i32_free(&vector_B);
}