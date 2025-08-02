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
int X,Y;
//  PixelArray[Y-AXIS][X-AXIS]

// MATH

double complexModulus(double x,double y){
	return pow(pow(x,2)+pow(y,2),0.5);
}

void iteratorComplex(double complex seed,double x,double y){
	double complex z = (XAXISSIZE * (((2*x)-(SCREENWIDTH))/SCREENWIDTH)) + (YAXISSIZE * (((2*y)-(SCREENHEIGHT))/SCREENHEIGHT)) * I;
	for(int i = 0;i < 5;i++){
		z = cpow(z,2) + seed;
	}
	if(complexModulus(creal(z),cimag(z)) > 2){
		PixelArray[(int)y][(int)x] = BLUE;
	} else {
		PixelArray[(int)y][(int)x] = BLACK;
	}
	return;
}

int main(){
	double complex seed = (-1) + 0*I;
	for(double y = 0;y < SCREENHEIGHT;y++){
		for(double x = 0;x < SCREENWIDTH;x++){
			iteratorComplex(seed,x,y);
		}
	}
	

	al_init();
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* disp = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	al_register_event_source(queue, al_get_display_event_source(disp));
	ALLEGRO_EVENT event;
	// Draw Stuff
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(float y = 0;y < SCREENHEIGHT;y++){
		for(float x = 0;x < SCREENWIDTH;x++){
			if(PixelArray[(int)y][(int)x] == BLUE){
				al_draw_pixel(x,y,al_map_rgb(0,0,255));
			}
		}
	}
	al_flip_display();
	while(1){
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			al_destroy_display(disp);
			al_destroy_event_queue(queue);
			break;
		}
	}
	return 0;
}