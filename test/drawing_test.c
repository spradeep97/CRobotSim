// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include <unistd.h>
#include "../include/structures/bmp.h"
#include "../include/graphics/image_server.h"
#include "../include/graphics/colors.h"
#include "../include/graphics/drawing.h"
#include "../include/graphics/graphics.h"
#include "../include/physics/collision.h"

#define M_PI 3.141592653589793238462

void test_straight_line(bitmap_t* bmp);
void test_unfilled_polygon(bitmap_t* bmp);
void test_filled_polygon(bitmap_t* bmp);

int main(void) {
    bitmap_t bmp = {0};
    gx_create_bmp(&bmp, 640, 480);
    gx_clear(&bmp, white);

    // Insert test code here //
    test_filled_polygon(&bmp);
    // Test code ends //

    size_t bmp_size = bmp_calculate_size(&bmp);
    uint8_t *serialized_bmp = malloc(bmp_size);
    bmp_serialize(&bmp, serialized_bmp);

    image_server_set_data(bmp_size, serialized_bmp);
    image_server_start("8000");
    sleep(5);

    // free all malloced memory
    free(bmp.data);
    free(serialized_bmp);
    return 0;
}

void test_straight_line(bitmap_t* bmp) {
    draw_line(bmp, 100, 100, 150, 100, black);
}

void test_unfilled_polygon(bitmap_t* bmp) {
    double v_x[4] = {10.0, 150.0, 150.0, 10.0};
    double v_y[4] = {10.0, 10.0, 150.0, 150.0};
    polygon_t square = createPolygon(v_x, v_y, 4);
    draw_unfilled_polygon(bmp, &square, black);
    destroyPolygon(&square);
}

void test_filled_polygon(bitmap_t* bmp) {
    double v_x[4] = {100.0, 150.0, 150.0, 10.0};
    double v_y[4] = {10.0, 10.0, 150.0, 150.0};
    polygon_t square = createPolygon(v_x, v_y, 4);
    point_t center = {102.5, 80};
    setPolygonRotationCenter(&square, center);
    rotatePolygon(&square, 1 * M_PI / 4);
    draw_filled_polygon(bmp, &square, black);
    destroyPolygon(&square);
}
