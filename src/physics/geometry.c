// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void translatePolygon(polygon_t* polygon, double x, double y) {
    for (int i = 0; i < polygon->num_edges; ++i) {
        polygon->edges[i]->start->x += x;
        polygon->edges[i]->start->y += y;
    }
}

void rotatePolygon(polygon_t* polygon, double angleInRad) {
    translatePolygon(polygon, -polygon->rotationPoint.x,
                     -polygon->rotationPoint.y);
    for (int i = 0; i < polygon->num_edges; ++i) {
        double old_x = polygon->edges[i]->start->x;
        double old_y = polygon->edges[i]->start->y;
        polygon->edges[i]->start->x =
        old_x * cos(angleInRad) - old_y * sin(angleInRad);
        polygon->edges[i]->start->y =
        old_x * sin(angleInRad) + old_y * cos(angleInRad);
    }
    translatePolygon(polygon, polygon->rotationPoint.x,
                     polygon->rotationPoint.y);
}

void setPolygonRotationCenter(polygon_t* polygon, point_t center) {
    polygon->rotationPoint = center;
}

point_t calculatePolygonCenter(polygon_t* polygon) {
    point_t polygonCenter;
    for (int i = 0; i < polygon->num_edges; ++i) {
        polygonCenter.x += polygon->edges[i]->start->x;
        polygonCenter.y += polygon->edges[i]->start->y;
    }
    polygonCenter.x /= polygon->num_edges;
    polygonCenter.y /= polygon->num_edges;
    return polygonCenter;
}

point_t findMinCoordinate(polygon_t* polygon) {
    point_t minCoordinate = {1000.0, 1000.0};
    for (int i = 0; i < polygon->num_edges; ++i) {
        if (polygon->edges[i]->start->x < minCoordinate.x) {
            minCoordinate.x = polygon->edges[i]->start->x;
        }
        if (polygon->edges[i]->start->y < minCoordinate.y) {
            minCoordinate.y = polygon->edges[i]->start->y;
        }
    }
    return minCoordinate;
}

double findDistance(pose2d_t* pose1, pose2d_t* pose2) {
    double delta_x = pose2->x_position - pose1->x_position;
    double delta_y = pose2->y_position - pose1->y_position;
    double distance = sqrt(delta_x * delta_x + delta_y * delta_y);
    return distance;
}

double findDotProduct(direction_vector_t* vector1,
                      direction_vector_t* vector2) {
    return (vector1->x_component * vector2->x_component +
           vector1->y_component * vector2->y_component);
}

direction_vector_t findDirectionBetween(pose2d_t* pose1, pose2d_t* pose2) {
    direction_vector_t vector;
    vector.x_component = pose2->x_position - pose1->x_position;
    vector.y_component = pose2->y_position - pose1->y_position;
    double length = sqrt(vector.x_component * vector.x_component +
                         vector.y_component * vector.y_component);
    vector.x_component /= length;
    vector.y_component /= length;
    return vector;
}

direction_vector_t findDirectionFromAngle(double angleInRad) {
    direction_vector_t vector;
    vector.x_component = cos(angleInRad);
    vector.y_component = sin(angleInRad);
    return vector;
}
