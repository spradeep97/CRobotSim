// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include "../include/structures/geometry.h"

#define M_PI 3.141592653589793238462

void test_findDistance();
void test_findDotProduct();
void test_findDirectionBetween();
void test_findDirectionFromAngle();

int main(void) {
    test_findDirectionFromAngle();
    return 0;
}

void test_findDistance(void) {
    pose2d_t pose1 = {0, 0, 0};
    pose2d_t pose2 = {-4, 3, 0};
    double distance = findDistance(&pose1, &pose2);
    printf("Distance : %f\n", distance);
}

void test_findDotProduct(void) {
    direction_vector_t vector1 = {1, 0};
    direction_vector_t vector2 = {-1, 0};
    double dotProduct = findDotProduct(&vector1, &vector2);
    printf("Dot Product : %f\n", dotProduct);
}

void test_findDirectionBetween(void) {
    pose2d_t pose1 = {0, 0, 0};
    pose2d_t pose2 = {-4, 3, 0};
    direction_vector_t vector = findDirectionBetween(&pose1, &pose2);
    printf("x:%f | y:%f\n", vector.x_component, vector.y_component);
}

void test_findDirectionFromAngle(void) {
    direction_vector_t vector = findDirectionFromAngle(M_PI / 4);
    printf("x:%f | y:%f\n", vector.x_component, vector.y_component);
}