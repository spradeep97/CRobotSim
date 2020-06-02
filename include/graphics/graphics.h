// Copyright 2020 | Pradeep Suresh | University of Michigan
#pragma once

#include "../structures/bmp.h"
#include "../structures/pixel_t.h"
#include "../structures/vector_xy_i32_t.h"

// Creates a (WxH) bitmap variable  and allocates memory to the data field
void gx_create_bmp(bitmap_t* bmp, int width, int height);

// Sets the specified pixel to specified color
void gx_set_pixel(bitmap_t* bmp, pixel_t* pixel, color_bgr_t color);

// Sets a vector of pixels to specified color
void gx_set_pixels(bitmap_t* bmp, vector_xy_i32_t* pixels, color_bgr_t color);

// Clears the bitmap file with specified background color
void gx_clear(bitmap_t* bmp, color_bgr_t color);
