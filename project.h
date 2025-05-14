#include <stdbool.h>
#include <stdint.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "sense.h"

void set_color(uint16_t color);

typedef struct {
    int x;
    int y;
} Point;

void open_input(void);
void close_input(void);
void check_input(Point *pos, int delay);
bool detect_shake(void);
void open_output(void);
void close_display(void);

void draw_pixel(Point pos);
void clear_display(void);


