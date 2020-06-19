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
    int fast_mode = 0;
    int time_steps = 0;

    // Read command line arguments
    args_read = sscanf(argv[1], "%d", &time_steps);
    if (args_read <= 0) {
        fprintf(stderr, "usage: ./braitenberg <time steps> <fast=0|1>\n");
        return 1;
    }

    args_read = sscanf(argv[2], "%d", &fast_mode);
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

    if (fast_mode == 0) {
        // Create time interval structure
        int64_t seconds = 0;
        int64_t nanoseconds = 40 * 1000 * 1000;
        struct timespec interval = {seconds, nanoseconds};

        init_world(&world);
        init_graphics(&world, &bmp);

        // for (int t_step = 0; t_step < time_steps; t_step++) {
        //     move(&robot, &world);
        //     resolve_collision(&robot, &world, &bmp);
        //     update_graphics(&robot, &world, &bmp);
        //     bmp_serialize(&bmp, serialized_bmp);
        //     image_server_set_data(bmp_size, serialized_bmp);
        //     image_server_start("8000");
        //     nanosleep(&interval, NULL);
        // }

        size_t bmp_size = bmp_calculate_size(&bmp);
        uint8_t *serialized_bmp = malloc(bmp_size);
        bmp_serialize(&bmp, serialized_bmp);
        image_server_set_data(bmp_size, serialized_bmp);
        image_server_start("8000");
        sleep(5);

        destroy_world(&world);
        free(bmp.data);
        free(serialized_bmp);

    } else {

    }
    return 0;
}