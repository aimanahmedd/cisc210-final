
#include "project.h"
#include "sense.h"
#include <linux/input.h>
#include <math.h>
#include <stdlib.h>
#include "gyro.h"
#include "humidity_temp.h"


static pi_joystick_t *joystick = NULL;
static pi_framebuffer_t *fb = NULL;

static Point *cursor_pos = NULL;

void open_input(void) {
    if (!joystick) joystick = getJoystickDevice();
    if (!fb) fb = getFrameBuffer();
}

void close_input(void) {
    if (joystick) {
        freeJoystick(joystick);
        joystick = NULL;
    }
    if (fb) {
        freeFrameBuffer(fb);
        fb = NULL;
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
bool detect_shake(void) {
    coordinate_t acc;
    pi_i2c_t* i2c = geti2cDevice();

    if (!i2c) return false;

    if (getAccelData(i2c, &acc) != 0) {
        return false;
    }

    float ax = acc.x;
    float ay = acc.y;
    float az = acc.z;

    float magnitude = sqrtf(ax * ax + ay * ay + az * az);
    return magnitude > 2.5f;
}


