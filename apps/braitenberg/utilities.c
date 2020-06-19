// Copyright 2020 | Pradeep Suresh | University of Michigan
#include "utilities.h"

color_bgr_t white;
color_bgr_t black;

color_bgr_t blue;
color_bgr_t green;
color_bgr_t red;

color_bgr_t yellow;
color_bgr_t sky_blue;
color_bgr_t pink;

void init_robot(robot_t* robot, pose2d_t start_pose) {
    robot->pose = start_pose;

    robot->eye_left = findDirectionFromAngle(-M_PI / 3);
    robot->eye_right = findDirectionFromAngle(M_PI / 3);

    robot->shape = createTriangle(4.0 / 3.0, 28);
    rotatePolygon(&robot->shape, robot->pose.angleInRad);
    translatePolygon(&robot->shape,
                     robot->pose.x_position,
                     robot->pose.y_position);

    robot->center.x = robot->pose.x_position;
    robot->center.y = robot->pose.y_position;
    setPolygonRotationCenter(&robot->shape, robot->center);

    robot->color = green;
    robot->max_speed = 12;
    robot->wheel_base = 80;
}

void init_lamp(lamp_t* lamp, pose2d_t start_pose) {
    lamp->pose = start_pose;

    lamp->shape = createRectangle(12, 12);
    rotatePolygon(&lamp->shape, lamp->pose.angleInRad);
    translatePolygon(&lamp->shape,
                        lamp->pose.x_position,
                        lamp->pose.y_position);

    lamp->center.x = lamp->pose.x_position;
    lamp->center.y = lamp->pose.y_position;
    setPolygonRotationCenter(&lamp->shape, lamp->center);

    lamp->color = yellow;
    lamp->intensity = 100000;
}

void init_world(world_t* world) {
    world->n_lamps = NUM_LAMPS;

    pose2d_t robot_start_pos = {320, 240, 0};

    init_robot(&world->robot[0], robot_start_pos);

    pose2d_t lamp_start_pos[NUM_LAMPS] = {{124.1, 224.1, M_PI / 4},
                                          {349.1, 99.1, M_PI / 4},
                                          {449.1, 349.1, M_PI / 4}};

    for (int i = 0; i < world->n_lamps; ++i) {
        init_lamp(&world->lamp[i], lamp_start_pos[i]);
    }
}

void destroy_world(world_t* world) {
    destroyPolygon(&world->robot[0].shape);

    for (int i = 0; i < world->n_lamps; ++i) {
        destroyPolygon(&world->lamp[i].shape);
    }
}

void init_graphics(world_t* world, bitmap_t* bmp) {
    for (int i = 0; i < world->n_lamps; ++i) {
        draw_filled_polygon(bmp, &world->lamp[i].shape, world->lamp[i].color);
    }
    draw_filled_polygon(bmp, &world->robot[0].shape, world->robot[0].color);
}
