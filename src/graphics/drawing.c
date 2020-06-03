// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include "../../include/structures/vector_xy_i32_t.h"
#include "../../include/graphics/drawing.h"
#include "../../include/graphics/graphics.h"

vector_xy_i32_t* rasterize_line(int x0, int y0, int x1, int y1) {
    vector_xy_i32_t *line = malloc(sizeof(*line));
    vector_xy_i32_init(line);

    // Bresenham's Algorithm
    int dx, sx, dy, sy, err, e2;
    dx = abs(x1 - x0);
    sx = x0 < x1 ? 1 : -1;
    dy = -abs(y1 - y0);
    sy = y0 < y1 ? 1 : -1;
    err = dx + dy;

    vector_xy_i32_add(line, x0, y0);
    while (1) {
        if (x0 == x1 && y0 == y1) {
            break;
        }
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
        vector_xy_i32_add(line, x0, y0);
    }

    return line;
}

void draw_line(bitmap_t* bmp,
               int x0, int y0, int x1, int y1,
               color_bgr_t color) {
    vector_xy_i32_t* pixels = rasterize_line(x0, y0, x1, y1);
    gx_set_pixels(bmp, pixels, color);
    vector_xy_i32_free(pixels);
    free(pixels);
}
