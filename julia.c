#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <allegro5/allegro5.h>

#define BLACK 0
#define BLUE 1
#define SCREENHEIGHT 1800
#define SCREENWIDTH 1800
#define XAXISSIZE 4
#define YAXISSIZE 4

int PixelArray[SCREENHEIGHT][SCREENWIDTH];
int reversing;
//  PixelArray[Y-AXIS][X-AXIS]

// MATH

double complexModulus(double x,double y){
	return pow(pow(x,2)+pow(y,2),0.5);
}

void iteratorComplex(double complex seed,double x,double y){
	double complex z = (XAXISSIZE * (((2*x)-(SCREENWIDTH))/SCREENWIDTH)) + (YAXISSIZE * (((2*y)-(SCREENHEIGHT))/SCREENHEIGHT)) * I;
	for(int i = 0;i < 25;i++){
		z = cpow(z,2) + seed;
	}
	double mod = complexModulus(creal(z),cimag(z));
	if(mod < 2){
		PixelArray[(int)y][(int)x] = BLACK;
	} else if (mod < 25){
		PixelArray[(int)y][(int)x] = mod;
	} else if (mod < 100){
		PixelArray[(int)y][(int)x] = mod*(-1);
	} else {
		PixelArray[(int)y][(int)x] = BLUE;
	}
	return;
}

int main(int argc,char **argv){
	reversing = 1;
	double complex seed = (strtod(argv[1],NULL)) + strtod(argv[2],NULL)*I;
	for(double y = 0;y < SCREENHEIGHT;y++){
		for(double x = 0;x < SCREENWIDTH;x++){
			iteratorComplex(seed,x,y);
		}
	}
	
	al_init();
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	ALLEGRO_EVENT event;
	// Draw Stuff
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(float y = 0;y < SCREENHEIGHT;y++){
		for(float x = 0;x < SCREENWIDTH;x++){
			if(PixelArray[(int)y][(int)x] == BLUE){
				al_draw_pixel(x,y,al_map_rgb(0,0,255));
			} else if(PixelArray[(int)y][(int)x] < 0) {
				al_draw_pixel(x,y,al_map_rgb(0,PixelArray[(int)y][(int)x]*(-1),0));
			} else if(PixelArray[(int)y][(int)x] != 0){
				al_draw_pixel(x,y,al_map_rgb(PixelArray[(int)y][(int)x],0,0));
			} 
			fflush(stdout);
		}
	}
	al_flip_display();
	al_start_timer(timer);
	while(1){
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			al_destroy_display(disp);
			al_destroy_event_queue(queue);
			al_destroy_timer(timer);
			break;
		}
	}
	return 0;
}