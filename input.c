
#include "project.h"
#include "sense.h"
#include <linux/input.h>
#include <math.h>
#include <stdlib.h>
#include "gyro.h"
#include "humidity_temp.h"
#include <signal.h>
#include <stdio.h>

static pi_joystick_t *joystick = NULL;
static Point *cursor_pos = NULL;
pi_i2c_t* i2c = NULL;

void open_input(void) {
    if (!joystick) joystick = getJoystickDevice();
    if (!i2c) i2c = geti2cDevice();
    if (i2c){
    	configureAccelGyro(i2c);
    }

}

void close_input(void) {
    if (joystick) {
        freeJoystick(joystick);
        joystick = NULL;
    }
    if(i2c){
	freei2cDevice(i2c);
	i2c = NULL;
    }

}

static uint16_t colors[] = {
0xF8F0,  // Pink
    0x0000ff,  // blue
    0x8410,  // Gray
    0x0000   // Unlit (off)
};
static int color_index = 0;


static void joystick_callback(unsigned int code) {
    if (!cursor_pos) return;

    switch (code) {
        case KEY_UP:
            if (cursor_pos->y > 0) cursor_pos->y--;
            break;
        case KEY_DOWN:
            if (cursor_pos->y < 7) cursor_pos->y++;
            break;
        case KEY_LEFT:
            if (cursor_pos->x > 0) cursor_pos->x--;
            break;
        case KEY_RIGHT:
            if (cursor_pos->x < 7) cursor_pos->x++;
            break;
	case KEY_ENTER:
	    color_index = (color_index + 1) % (sizeof(colors) / sizeof(colors[0]));
            set_color(colors[color_index]);  
	    break;
        default:
            break;
    }

    draw_pixel(*cursor_pos);
}


void check_input(Point *pos, int delay) {
    cursor_pos = pos;
    if (joystick) {
        pollJoystick(joystick, joystick_callback, delay);
    }
}


float threshold = 1;
float x=0,y=0,z=0;
bool detect_shake(void) {
	coordinate_t data;
        if (getAccelData(i2c,&data)){
            float dx=data.x-x,dy=data.y-y,dz=data.z-z;

	    x = data.x; y = data.y; z = data.z;
            if(dx*dx+dy*dy+dz*dz > threshold) {
                printf("bumped: %f %f %f\n",dx,dy,dz);
		return true;
	    }
	    //printf("nbmped: %f %f %f\n", dx, dy, dz);
	    return false;
        }
	return false;
}

