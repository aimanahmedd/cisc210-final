#include <stdbool.h>
#include <stdint.h>

void set_color(uint16_t color);

typedef struct {
    int x;
    int y;
} Point;

void open_input(void);
void close_input(void);
void check_input(Point *pos, int delay);
bool detect_shake(void);

void draw_pixel(Point pos);
void clear_display(void);


