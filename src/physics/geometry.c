// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
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

    for (int i = 0; i < num_edges; ++i) {
        vertices[i] = createPoint(x_vertices[i], y_vertices[i]);
    }

    // Create edges from points
    line_t* edges = calloc(num_edges, sizeof(line_t));
    for (int i = 0; i < num_edges; ++i) {
        edges[i] = makeLine(&vertices[i], &vertices[(i + 1) % 4]);
    }

    // Create polygon from edges
    polygon_t polygon = makePolygon(edges, num_edges);

    return polygon;
}
