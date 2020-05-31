// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include "../include/structures/vector_xy_t.h"

void test_vector_xy_t(void);

int main(void) {
    test_vector_xy_t();
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