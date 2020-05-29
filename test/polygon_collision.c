// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include "../include/physics/collision.h"

void test_compute_crossProduct(void);
void test_is_collide(void);

int main(void) {
    test_is_collide();
}

void test_compute_crossProduct(void) {
    point_t p1 = createPoint(0.0, 0.0);
    line_t l = createLine(-0.5, -0.5, 0.5, -0.5);
    printf("collsion:%f\n", compute_crossProduct(&l, &p1));
}

void test_is_collide(void) {
    double v_x[3] = {-1.0, 0.0, 1.0};
    double v_y[3] = {-1.0, 1.0, -1.0};
    double v2_x[4] = {0.0, 0.0, 1.0, 1.0};
    double v2_y[4] = {0.0, 1.0, 1.0, 0.0};

    polygon_t square = createPolygon(v_x, v_y, 3);

    polygon_t square2 = createPolygon(v2_x, v2_y, 4);

    printf("collision:%d\n", is_collide(&square, &square2));
}