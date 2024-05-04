#include "collisions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 480
#define HEIGHT 320

bool check_collisions(int snake_x, int snake_y) {
    bool ret = true;
    if ((snake_x > WIDTH) || (snake_y > HEIGHT) || (snake_x < 0) || (snake_y < 0) ) {
        printf("Snake out of range\n");
        ret = false;
    }
    return ret;
}