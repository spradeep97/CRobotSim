// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <math.h>
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

void moveTo_nextRobotPose(world_t* world) {

    robot_t* robot = &world->robot[0];

    double move_left = 0;
    double move_right = 0;

    // Calculate the amount by which left and right wheels need to move
    for (int i = 0; i < world->n_lamps; i++) {
        double lampToRobotDistance = findDistance(&world->lamp[i].pose,
                                                  &robot->pose);

        double squaredDistance = lampToRobotDistance * lampToRobotDistance;

        direction_vector_t lampToRobotDirection =
        findDirectionBetween(&robot->pose, &world->lamp[i].pose);

        robot->eye_left = findDirectionFromAngle(robot->pose.angleInRad
                                                 - M_PI / 3);
        robot->eye_right = findDirectionFromAngle(robot->pose.angleInRad
                                                  + M_PI / 3);

        double constantMultiplier = world->lamp[i].intensity / squaredDistance;

        move_left +=
        fmax(0.0, findDotProduct(&lampToRobotDirection, &robot->eye_right)) *
        constantMultiplier;

        move_right +=
        fmax(0.0, findDotProduct(&lampToRobotDirection, &robot->eye_left)) *
        constantMultiplier;
    }

    move_left = fmin(robot->max_speed, move_left);
    move_right = fmin(robot->max_speed, move_right);

    // Set rotation point before updating pose
    robot->center.x = robot->pose.x_position;
    robot->center.y = robot->pose.y_position;
    setPolygonRotationCenter(&robot->shape, robot->center);

    // Update pose based on move_left and move_right
    double deltaRotation = (move_left - move_right) / robot->wheel_base;
    robot->pose.angleInRad += deltaRotation;
    double move_forward = (move_left + move_right) / 2;
    double move_forwardInX = move_forward * cos(robot->pose.angleInRad);
    double move_forwardInY = move_forward * sin(robot->pose.angleInRad);
    robot->pose.x_position += move_forwardInX;
    robot->pose.y_position += move_forwardInY;

    // Move to new robot pose
    rotatePolygon(&robot->shape, deltaRotation);
    translatePolygon(&robot->shape, move_forwardInX, move_forwardInY);
}

void update_graphics(world_t* world, bitmap_t* bmp) {
    gx_clear(bmp, black);
    for (int i = 0; i < world->n_lamps; ++i) {
        draw_filled_polygon(bmp, &world->lamp[i].shape, yellow);
    }
    draw_filled_polygon(bmp, &world->robot[0].shape, green);
}

void resolve_collision(world_t* world) {
    double distanceToMove = 0.5;
    for (int i = 0; i < world->n_lamps; ++i) {
        while (is_collide(&world->robot[0].shape, &world->lamp[i].shape)) {
            // Move robot away from lamp
            direction_vector_t lampToRobotDirection =
            findDirectionBetween(&world->robot[0].pose, &world->lamp[i].pose);

            // Set rotation point before updating pose
            world->robot[0].center.x = world->robot[0].pose.x_position;
            world->robot[0].center.y = world->robot[0].pose.y_position;
            setPolygonRotationCenter(&world->robot[0].shape,
                                     world->robot[0].center);

            // Update pose
            double move_BackwardInX = distanceToMove *
                                      lampToRobotDirection.x_component;

            double move_BackwardInY = distanceToMove *
                                      lampToRobotDirection.y_component;

            world->robot[0].pose.x_position -= move_BackwardInX;

            world->robot[0].pose.y_position -= move_BackwardInY;

            // Move robot to new pose
            translatePolygon(&world->robot[0].shape,
                             -move_BackwardInX,
                             -move_BackwardInY);
        }
    }
}