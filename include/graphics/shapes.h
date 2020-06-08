// Copyright 2020 | Pradeep Suresh | University of Michigan

#pragma once
#include "../structures/geometry.h"

// Returns a rectangle of given dimensions centered at (0,0)
polygon_t createRectangle(double length, double width);

// Returns a triangle of given height-to-width ratio and given height
// pointed along the x axis
polygon_t createTriangle(double ratio, double height);
