#include "project.h"
#include "sense.h"
#include <stdlib.h>

static pi_framebuffer_t *fb = NULL;
static uint16_t current_color = 0xF81F;  

void open_output(void){
	if (!fb) fb = getFrameBuffer();
}

void draw_pixel(Point pos) {
       fb->bitmap->pixel[pos.y][pos.x] = current_color;
}


void clear_display() {
	clearFrameBuffer(fb, 0x0000);
}

void close_display(){
	clear_display();
	freeFrameBuffer(fb);
}

void set_color(uint16_t color) {
    current_color = color;
}

