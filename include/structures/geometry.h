// Copyright 2020 | Pradeep Suresh | University of Michigan
#ifndef STRUCTURES_GEOMETRY_H_
#define STRUCTURES_GEOMETRY_H_

#define MAX_NUM_VERTICES 16

/* --- STRUCTURE DEFINITIONS --- */

typedef struct point {
    double x, y;
} point_t;

typedef struct line {
    point_t* start;
    point_t* end;
} line_t;

typedef struct polygon {
    int num_edges;
    line_t* edges[MAX_NUM_VERTICES];
    point_t rotationPoint;
} polygon_t;

/* --- STRUCTURE INITIALIZERS --- */

// creates a point from x and y co-ordinates
point_t createPoint(double x, double y);

// creates a line from two point_t values
line_t makeLine(point_t* p1, point_t* p2);

// creates a line from 4 co-ordinates
line_t createLine(double x1, double y1, double x2, double y2);

// creates a polygon from an array of line_t values
// \param: num_edges cannot be more than MAX_NUM_VERTICES
polygon_t makePolygon(line_t* edges, int num_edges);

// creates a polygon from arrays of vertices' x and y co-ordinates
polygon_t createPolygon(double* vertices_x, double* vertices_y, int num_edges);

// frees the memory allocated in createPolygon
void destroyPolygon(polygon_t* polygon);

/* --- GEOMETRIC OPERATIONS --- */

// translates the polygon by specified amounts in x and y directions
void translatePolygon(polygon_t* polygon, double x, double y);

// calculates center of a regular polygon
point_t calculatePolygonCenter(polygon_t* polygon);

// explicitly sets the point about which polygon would be rotated
void setPolygonRotationCenter(polygon_t* polygon, point_t center);

// rotates all points of the polygon about its rotation center
void rotatePolygon(polygon_t* polygon, double angleInRad);

point_t findMinCoordinate(polygon_t* polygon);

#endif  // STRUCTURES_GEOMETRY_H_
