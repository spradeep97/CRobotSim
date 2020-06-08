// Copyright 2020 | Pradeep Suresh | University of Michigan

#include "../../include/structures/geometry.h"
#include "../../include/graphics/shapes.h"

polygon_t createRectangle(double length, double width) {
    double x_left = -length / 2.0;
    double x_right = length / 2.0;
    double y_top = - width / 2.0;
    double y_bottom = width / 2.0;

    double v_x[4] = {x_left, x_left, x_right, x_right};
    double v_y[4] = {y_bottom, y_top, y_top, y_bottom};

    return createPolygon(v_x, v_y, 4);
}

polygon_t createTriangle(double ratio, double height) {
    double x_left = - height / 2.0;
    double x_right = height / 2.0;
    double y_top = - height / (ratio * 2.0);
    double y_bottom = height / (ratio * 2.0);

    double v_x[3] = {x_left, x_left, x_right};
    double v_y[3] = {y_bottom, y_top, 0};

    return createPolygon(v_x, v_y, 3);
}