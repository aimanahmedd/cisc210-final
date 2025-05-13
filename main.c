#include "project.h"
#include <unistd.h>
#include <stdio.h>

int main() {
    Point position = {3, 3};

    open_input();
    clear_display();
    draw_pixel(position);

  while (true) {
        check_input(&position, 100);

        if (detect_shake()) {
            clear_display();
            printf("Shake detected! Screen cleared.\n");
        }

        usleep(50000);
    }

    close_input();
    return 0;
}

