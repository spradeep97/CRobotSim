// Copyright 2020 | Pradeep Suresh | University of Michigan

#pragma once
#include "../structures/vector_xy_i32_t.h"
#include "../structures/bmp.h"

// Returns a vector of pixels making up the line
vector_xy_i32_t* rasterize_line(int x0, int y0, int x1, int y1);

// Draws a line between two points on bmp
void draw_line(bitmap_t* bmp,
               int x0, int y0, int x1, int y1,
               color_bgr_t color);
