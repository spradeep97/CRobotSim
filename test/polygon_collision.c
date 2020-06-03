// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include "../include/physics/collision.h"

#define M_PI 3.141592653589793238462

void test_compute_crossProduct(void);
void test_is_collide(void);
void test_is_contain(void);
void test_translatePolygon(void);
void test_rotatePolygon(void);
void test_findMinCoordinate(void);

int main(void) {
    // test_is_collide();
    // test_is_contain();
    // test_translatePolygon();
    // test_rotatePolygon();
    test_findMinCoordinate();
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

    destroyPolygon(&square);
    destroyPolygon(&square2);
}

void test_is_contain(void) {
    double v_x[4] = {-1.0, -1.0, 1.0, 1.0};
    double v_y[4] = {-1.0, 1.0, 1.0, -1.0};
    double v2_x[4] = {-1.5, -1.5, 0.5, 0.5};
    double v2_y[4] = {-2.0, 2.0, 2.0, -2.0};

    polygon_t square = createPolygon(v_x, v_y, 4);

    polygon_t square2 = createPolygon(v2_x, v2_y, 4);

    printf("containment:%d\n", is_polygon_contained(&square, &square2));

    destroyPolygon(&square);
    destroyPolygon(&square2);
}

void test_translatePolygon(void) {
    double v_x[4] = {-1.0, -1.0, 1.0, 1.0};
    double v_y[4] = {-1.0, 1.0, 1.0, -1.0};
    polygon_t square = createPolygon(v_x, v_y, 4);
    translatePolygon(&square, 10, 10);
}

void test_rotatePolygon(void) {
    double v_x[4] = {-1.0, -1.0, 1.0, 1.0};
    double v_y[4] = {-1.0, 1.0, 1.0, -1.0};
    polygon_t square = createPolygon(v_x, v_y, 4);

    point_t polygonCenter = calculatePolygonCenter(&square);
    point_t rightBottomCorner = {1, -1};
    setPolygonRotationCenter(&square, rightBottomCorner);
    rotatePolygon(&square, M_PI / 2);
}

void test_findMinCoordinate(void) {
    double v_x[4] = {-1.0, -1.0, 1.0, 1.0};
    double v_y[4] = {-1.0, 1.0, 1.0, -1.0};
    polygon_t square = createPolygon(v_x, v_y, 4);

    point_t minCoordinate = findMinCoordinate(&square);
    printf("x_min:%f | y_min:%f\n", minCoordinate.x, minCoordinate.y);
}
