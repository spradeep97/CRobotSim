// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include "../../include/structures/pixel_t.h"
#include "../../include/structures/vector_xy_i32_t.h"
#include "../../include/graphics/graphics.h"
#include "../../include/structures/bmp.h"

void gx_create_bmp(bitmap_t* bmp, int width, int height) {
    bmp->width = width;
    bmp->height = height;
    bmp->data = calloc(bmp->width * bmp->height, sizeof(color_bgr_t));
}

void gx_set_pixel(bitmap_t* bmp, pixel_t* pixel, color_bgr_t color) {
    if (pixel->x >= 0 && pixel->y >= 0) {
        bmp->data[bmp->width * bmp->height -
                  bmp->width - pixel->y * bmp->width + pixel->x] = color;
    }
}

void gx_set_pixels(bitmap_t* bmp, vector_xy_i32_t* pixels, color_bgr_t color) {
    for (int i = 0; i < pixels->size; i++) {
        gx_set_pixel(bmp, &pixels->data[i], color);
    }
}

void gx_clear(bitmap_t* bmp, color_bgr_t color) {
    for (int row = 0; row < bmp->height; row++) {
        for (int col = 0; col < bmp->width; col++) {
            bmp->data[row * bmp->width + col] = color;
        }
    }
}
