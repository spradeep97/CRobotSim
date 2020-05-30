// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/geometry.h"


point_t createPoint(double x, double y) {
    point_t p = {x, y};
    return p;
}

line_t makeLine(point_t* p1, point_t* p2) {
    line_t l = {p1, p2};
    return l;
}

line_t createLine(double x1, double y1, double x2, double y2) {
    point_t p1 = {x1, y1};
    point_t p2 = {x2, y2};
    line_t l = {&p1, &p2};
    return l;
}

polygon_t makePolygon(line_t* edges, int num_edges) {
    polygon_t polygon;
    polygon.num_edges = num_edges;
    for (int i = 0; i < num_edges; ++i) {
        polygon.edges[i] = &edges[i];
    }
    return polygon;
}

polygon_t createPolygon(double* x_vertices, double* y_vertices, int num_edges) {
    // Create N points
    point_t* vertices = calloc(num_edges, sizeof(point_t));
    line_t* edges = calloc(num_edges, sizeof(line_t));
    polygon_t polygon;
    polygon.num_edges = num_edges;
    for (int i = 0; i < num_edges; ++i) {
        int next = (i + 1) % num_edges;
        vertices[i].x = x_vertices[i];
        vertices[i].y = y_vertices[i];
        vertices[next].x = x_vertices[next];
        vertices[next].y = y_vertices[next];
        edges[i].start = &vertices[i];
        edges[i].end = &vertices[next];
        polygon.edges[i] = &edges[i];
    }
    return polygon;
}

void destroyPolygon(polygon_t* polygon) {
    free(polygon->edges[0]->start);
    free(polygon->edges[0]);
}
