// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/structures/bmp.h"
#include "../include/graphics/image_server.h"
#include "../include/graphics/colors.h"
#include "../include/graphics/graphics.h"
#include "../include/structures/pixel_t.h"

#define M_PI 3.141592653589793238462

void test_set_pixel(bitmap_t* bmp);
void test_set_pixels(bitmap_t* bmp);

int main(void) {
    bitmap_t bmp = {0};
    gx_create_bmp(&bmp, 640, 480);
    gx_clear(&bmp, white);

    // Insert test code here //
    test_set_pixels(&bmp);
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

void test_set_pixel(bitmap_t* bmp) {
    pixel_t mid_pixel = {320, 240};
    gx_set_pixel(bmp, &mid_pixel, red);
}

void test_set_pixels(bitmap_t* bmp) {
    vector_xy_i32_t pixels = {0};
    vector_xy_i32_init(&pixels);
    for (int i = 0; i < 100; ++i) {
        vector_xy_i32_add(&pixels, i, i);
    }
    gx_set_pixels(bmp, &pixels, red);
    vector_xy_i32_free(&pixels);
}