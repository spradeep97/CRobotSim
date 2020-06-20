// Copyright 2020 | Pradeep Suresh | University of Michigan

#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../../include/graphics/drawing.h"
#include "../../include/graphics/graphics.h"
#include "../../include/graphics/image_server.h"
#include "../../include/graphics/shapes.h"

#include "../../include/physics/collision.h"

#include "../../include/structures/bmp.h"
#include "../../include/structures/geometry.h"
#include "../../include/structures/vector_xy_i32_t.h"
#include "../../include/structures/vector_xy_t.h"

#define NUM_LAMPS 3
#define NUM_ROBOTS 1
// #define M_PI 3.141592653589793238462


typedef struct robot {
    pose2d_t pose;
    direction_vector_t eye_left;
    direction_vector_t eye_right;
    polygon_t shape;
    point_t center;
    color_bgr_t color;
    int max_speed;
    double wheel_base;
} robot_t;

typedef struct lamp {
    pose2d_t pose;
    polygon_t shape;
    point_t center;
    color_bgr_t color;
    double intensity;
} lamp_t;

typedef struct world {
    int n_lamps;
    lamp_t lamp[NUM_LAMPS];
    robot_t robot[NUM_ROBOTS];
} world_t;
