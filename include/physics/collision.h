// Copyright 2020 | Pradeep Suresh | University of Michigan

#ifndef PHYSICS_COLLISION_H_
#define PHYSICS_COLLISION_H_

#include <stdbool.h>
#include "../structures/geometry.h"

// checks whether two given polygons are in collision or not
bool is_collide(polygon_t* polygon1, polygon_t* polygon2);

// checks whether two given lines are intersecting or not
bool is_intersect(line_t* edge1, line_t* edge2);

// checks whether two lines are intersecting based on
// the cross product information between various
// combinations of points and lines
bool give_judgement(double* crossProducts);

// computes cross product between line and a point
double compute_crossProduct(line_t* edge, point_t* point);

// checks if a point lies within a polygon
bool is_point_contained(polygon_t* polygon1, point_t* point);

// checks if one of the polygons is completely contained within the other
bool is_polygon_contained(polygon_t* polygon1, polygon_t* polygon2);

#endif  // PHYSICS_COLLISION_H_
