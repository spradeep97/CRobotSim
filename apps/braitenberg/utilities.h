// Copyright 2020 | Pradeep Suresh | University of Michigan

#pragma once

#include "braitenberg.h"

// Initialize the robot structure
void init_robot(robot_t* robot, pose2d_t start_pose);

// Initialize the lamp structure
void init_lamp(lamp_t* lamp, pose2d_t start_pose);

// Initialize the world structure
void init_world(world_t* world);

// Free all malloced memory for world structure
void destroy_world(world_t* world);

// Initialize the graphics
void init_graphics(world_t* world, bitmap_t* bmp);

// Moves to the next robot pose based on world's current state
void moveTo_nextRobotPose(world_t* world);

// Updates the graphics to reflect latest world state
void update_graphics(world_t* world, bitmap_t* bmp);

// Checks for collision between robot and lamps and resolves it
void resolve_collision(world_t* world);

