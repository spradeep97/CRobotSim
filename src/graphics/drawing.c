// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include <math.h>
#include "../../include/structures/vector_xy_i32_t.h"
#include "../../include/graphics/drawing.h"
#include "../../include/graphics/graphics.h"
#include "../../include/structures/geometry.h"

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

vector_xy_i32_t* rasterize_polygon(polygon_t* polygon) {
    vector_xy_i32_t* round_polygon = malloc(sizeof(*round_polygon));
    vector_xy_i32_init(round_polygon);

    point_t minCoordinate = findMinCoordinate(polygon);

    // Rounding the Polygon
    int32_t rounded_x = 0, rounded_y = 0;
    double epsilon = 1E-6;

    for (int i = 0; i < polygon->num_edges; ++i) {
        double vertex_x = polygon->edges[i]->start->x;
        double vertex_y = polygon->edges[i]->start->y;

        if (vertex_x == minCoordinate.x) {
            rounded_x = ceil(vertex_x);
        } else {
            rounded_x = floor(vertex_x - epsilon);
        }

        if (vertex_y == minCoordinate.y) {
            rounded_y = ceil(vertex_y);
        } else {
            rounded_y = floor(vertex_y - epsilon);
        }

        vector_xy_i32_add(round_polygon, rounded_x, rounded_y);
    }

    return round_polygon;
}

void draw_unfilled_polygon(bitmap_t* bmp,
                           polygon_t* polygon,
                           color_bgr_t color) {
    vector_xy_i32_t* round_polygon = rasterize_polygon(polygon);
    for (int i = 0; i < round_polygon->size; ++i) {
        int32_t x0 = round_polygon->data[i].x;
        int32_t y0 = round_polygon->data[i].y;
        int32_t x1 = round_polygon->data[(i + 1) % round_polygon->size].x;
        int32_t y1 = round_polygon->data[(i + 1) % round_polygon->size].y;

        draw_line(bmp, x0, y0, x1, y1, color);
    }
    vector_xy_i32_free(round_polygon);
    free(round_polygon);
}

void draw_filled_polygon(bitmap_t* bmp,
                         polygon_t* polygon,
                         color_bgr_t color) {
    vector_xy_i32_t* round_polygon = rasterize_polygon(polygon);
    int num_edges = polygon->num_edges;
    int* x_left = malloc(bmp->height * sizeof(int));
    int* x_right = malloc(bmp->height * sizeof(int));

    // Fill x_left and x_right with -1
    for (int i = 0; i < bmp->height; ++i) {
        x_left[i] = -1;
        x_right[i] = -1;
    }

    int y_min = 10000, y_max = -1;
    for (int edgeId = 0; edgeId < num_edges; ++edgeId) {
        int32_t x0 = round_polygon->data[edgeId].x;
        int32_t y0 = round_polygon->data[edgeId].y;
        int32_t x1 = round_polygon->data[(edgeId + 1) % round_polygon->size].x;
        int32_t y1 = round_polygon->data[(edgeId + 1) % round_polygon->size].y;

        vector_xy_i32_t* rasterizedEdge = rasterize_line(x0, y0, x1, y1);
        for (int pointId = 0; pointId < rasterizedEdge->size; ++pointId) {
            int x = rasterizedEdge->data[pointId].x;
            int y = rasterizedEdge->data[pointId].y;
            if (x_left[y] == -1) {
                x_left[y] = x;
                x_right[y] = x;
            } else {
                if (x_left[y] > x) {
                    x_left[y] = x;
                }
                if (x_right[y] < x) {
                    x_right[y] = x;
                }
            }

            if (y_min > y) {
                y_min = y;
            }
            if (y_max < y) {
                y_max = y;
            }
        }

        for (int height = y_min; height <= y_max; ++height) {
            draw_line(bmp, x_left[height], height, x_right[height], height,
                      color);
        }

        gx_set_pixels(bmp, rasterizedEdge, color);
        vector_xy_i32_free(rasterizedEdge);
        free(rasterizedEdge);
    }

    free(x_left);
    free(x_right);
    vector_xy_i32_free(round_polygon);
    free(round_polygon);
}