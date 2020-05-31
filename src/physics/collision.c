// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../../include/structures/geometry.h"
#include "../../include/physics/collision.h"

bool is_collide(polygon_t* polygon1, polygon_t* polygon2) {
    int numEdgesP1 = polygon1->num_edges;
    int numEdgesP2 = polygon2->num_edges;
    for (int i = 0; i < numEdgesP1; ++i) {
        for (int j = 0; j < numEdgesP2; ++j) {
            if (is_intersect(polygon1->edges[i], polygon2->edges[j])) {
                return true;
            }
        }
    }
    return false;
}

bool is_intersect(line_t* edge1, line_t* edge2) {
    double crossProducts[4] = {0, 0, 0, 0};
    line_t* edgeList[2] = {edge1, edge2};
    for (int edgeId = 0; edgeId < 2; ++edgeId) {
        line_t* selectedEdge = edgeList[edgeId];
        line_t* remainingEdge = edgeList[1 - edgeId];
        point_t* points[2] = {remainingEdge->start, remainingEdge->end};
        for (int i = 0; i < 2; ++i) {
            crossProducts[2 * edgeId + i] =
            compute_crossProduct(selectedEdge, points[i]);
        }
    }
    return give_judgement(crossProducts);
}

bool give_judgement(double* crossProducts) {
    bool is_l1_intersecting_extended_l2 =
    (crossProducts[0] * crossProducts[1]) <= 0;

    bool is_l1_touching_extended_l2 =
    (crossProducts[0] * crossProducts[1] == 0);

    bool is_l2_intersecting_extended_l1 =
    (crossProducts[2] * crossProducts[3]) <= 0;

    bool is_l2_touching_extended_l1 =
    (crossProducts[2] * crossProducts[3] == 0);

    if (is_l1_intersecting_extended_l2 &&
        is_l2_intersecting_extended_l1) {
            if (is_l1_touching_extended_l2 &&
                is_l2_touching_extended_l1) {
                    return false;
                }
            return true;
        }
    return false;
}

double compute_crossProduct(line_t* edge, point_t* point) {
    return ((edge->end->x - edge->start->x) * (edge->start->y - point->y) -
            (edge->end->y - edge->start->y) * (edge->start->x - point->x));
}
