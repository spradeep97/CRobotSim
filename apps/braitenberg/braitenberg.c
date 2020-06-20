// Copyright 2020 | Pradeep Suresh | University of Michigan

#include "braitenberg.h"
#include "utilities.h"

color_bgr_t white = {255, 255, 255};
color_bgr_t black = {0, 0, 0};

color_bgr_t blue = {255, 0, 0};
color_bgr_t green = {0, 255, 0};
color_bgr_t red = {0, 0, 255};

color_bgr_t yellow = {0, 255, 255};
color_bgr_t sky_blue = {255, 255, 0};
color_bgr_t pink = {255, 0, 255};

int main(int argc, char *argv[]) {
    int args_read = 0;
    int time_steps = 0;

    // Read command line arguments
    args_read = sscanf(argv[1], "%d", &time_steps);
    if (args_read <= 0) {
        fprintf(stderr, "usage: ./braitenberg <time steps> <fast=0|1>\n");
        return 1;
    }

    // Instantiate world
    world_t world = {0};

    // Instantiate a bitmap
    bitmap_t bmp = {0};
    gx_create_bmp(&bmp, 640, 480);
    gx_clear(&bmp, black);

    // Create time interval structure
    int64_t seconds = 0;
    int64_t nanoseconds = 40 * 1000 * 1000;
    struct timespec interval = {seconds, nanoseconds};

    // Initialize world and graphics
    init_world(&world);
    init_graphics(&world, &bmp);

    // Create space in memory for bitmap's contents
    size_t bmp_size = bmp_calculate_size(&bmp);
    uint8_t *serialized_bmp = malloc(bmp_size);

    // Main loop
    for (int t_step = 0; t_step < time_steps; t_step++) {
        moveTo_nextRobotPose(&world);
        resolve_collision(&world);
        update_graphics(&world, &bmp);
        bmp_serialize(&bmp, serialized_bmp);
        image_server_set_data(bmp_size, serialized_bmp);
        image_server_start("8000");
        nanosleep(&interval, NULL);
    }

    // Free all malloced memory
    destroy_world(&world);
    free(bmp.data);
    free(serialized_bmp);

    return 0;
}
