#include "project.h"
#include <unistd.h>
#include <stdio.h>

int run = 1;
void interrupt_handler(int sig){
	run = 0;
}


int main() {

	Point position = {3, 3};
	
	signal(SIGINT, interrupt_handler);
    	open_input();
	open_output();

	while(run){
		check_input(&position, 1);
		draw_pixel(position);

		if(detect_shake()){
			clear_display();
		}
	}


    	clear_display();    
    	close_input();
    	close_display();
    	return 0;
}

