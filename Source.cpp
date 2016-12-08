//libraries
#include <stdio.h>
//for sqrt (square root)
#include <math.h>
#include "allegro5/allegro.h"
//use image addon for loading images, dialog boxes, and primitive shapes
#include <allegro5/allegro_image.h>


//global variable for display
ALLEGRO_DISPLAY* display = NULL; //ALLEGRO_DISPLAY is a "user defined type" in Allegro. * shows a pointer

								 //initialzie Allegro components
void InitAllegro(int W, int H)
{

	//initialize allegro
	if (!al_init())
	{
		printf("failed to initialize allegro!\n");
	}

	//initialize display screen
	display = al_create_display(W, H);
	if (!display)
	{
		printf("failed to create display!\n");
		exit(0);
	}
	else
	{
		printf("ok");
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//initialize keyboard
	if (!al_install_keyboard())
	{
		printf("failed to install keyboard!\n");
		exit(0);
	}

	//initialize image addon
	if (!al_init_image_addon())
	{
		printf("failed to initialize image addon!\n");
		exit(0);
	}

}

//End and clean up Allegro components
void EndAllegro()
{
	al_destroy_display(display);
}


//main function
void main()
{
	///////////////////////////////////
	// INITIALIZE
	///////////////////////////////////

	//initialize allegro
	int sw = 640;
	int sh = 480;
	InitAllegro(sw, sh);

	//use a temporart target bitmap and lock it so put-pixel is fast
	ALLEGRO_BITMAP* bmp = al_create_bitmap(640, 480);
	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	al_set_target_bitmap(bmp);
	al_lock_bitmap(bmp, al_get_bitmap_format(bmp), ALLEGRO_LOCK_READWRITE);


	//clear screen
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//doall the drawings
	for (int x = 0; x < 640; x++)
	{
		//formula for calculating the parameters of a line (y=m*x+b) 
		//based on two points on that line x1/y1 and x2/y2
		//m = (y1-y2)/(x1-x2)
		//b = y1 � m*x1
		//range of X
		int x1 = 0;
		int x2 = 640;
		//range of Y (in this case Y represents red component of gradient)
		//we use float so the calculations are done in float
		float y1 = 10;
		float y2 = 200;
		float m = (y2 - y1) / (x2 - x1);
		float b = y1 - m * x1;

		//	int r = 255 * x / 600;
		int r = m*x + b;
		//g = b = 0;

		for (int y = 0; y < 480; y++)
		{
			al_put_pixel(x, y, al_map_rgb(r, 0, 0));
		}

		//int y1 = x;
		//al_put_pixel(x, y1, al_map_rgb(255, 0, 0));

		//int y2 = 2 * x + 7;
		//al_put_pixel(x, y2, al_map_rgb(0, 255, 0));
		//
		//int y3 = x * x;
		//al_put_pixel(x, y3, al_map_rgb(255, 255, 255));
	}

	//unlock the target and flip display
	al_set_target_bitmap(target);
	al_unlock_bitmap(bmp);
	al_draw_bitmap(bmp, 0, 0, 0);
	al_flip_display();

	//stay in a loop and wait
	ALLEGRO_KEYBOARD_STATE key_state;
	while (true)
	{
		al_get_keyboard_state(&key_state);
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
		{
			exit(0);
		}



	}

}