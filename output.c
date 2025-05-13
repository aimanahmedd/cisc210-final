#include "project.h"
#include "sense.h"
#include <stdlib.h>

static pi_framebuffer_t *fb = NULL;
static uint16_t current_color = 0xF81F;  


void draw_pixel(Point pos) {
    if (!fb) fb = getFrameBuffer();
    fb->bitmap->pixel[pos.y][pos.x] = current_color;
}


void clear_display() {
    if (!fb) fb = getFrameBuffer();

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            fb->bitmap->pixel[y][x] = 0x0000; 
        }
    }
}


void set_color(uint16_t color) {
    current_color = color;
}

