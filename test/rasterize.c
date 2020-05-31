// Copyright 2020 | Pradeep Suresh | University of Michigan

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/structures/bmp.h"
#include "../include/graphics/image_server.h"
#include "../include/graphics/colors.h"

#define M_PI 3.141592653589793238462

int main(void) {
    bitmap_t bmp = {0};
    bmp.width = 640;
    bmp.height = 480;
    bmp.data = calloc(bmp.width * bmp.height, sizeof(color_bgr_t));

    for (int row = 0; row < bmp.height; row++) {
        for (int col = 0; col < bmp.width; col++) {
            bmp.data[row * bmp.width + col] = sky_blue;
        }
    }

    size_t bmp_size = bmp_calculate_size(&bmp);
    uint8_t *serialized_bmp = malloc(bmp_size);
    bmp_serialize(&bmp, serialized_bmp);

    image_server_set_data(bmp_size, serialized_bmp);
    image_server_start("8000");
    sleep(5);
    // free all malloced memory
    free(bmp.data);
    free(serialized_bmp);
    return 0;
}
