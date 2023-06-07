#include "actions.h"


float point_x = 300.00, point_y = 300.00;
int KEY_A, KEY_D, KEY_W, KEY_S;

KEY_A = 4;
KEY_D = 7;
KEY_W = 26;
KEY_S = 22;


void draw_stuff(SDL_Renderer *rend)
{ 
  	SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
	SDL_RenderDrawLine(rend, 200, 300, 1000, 300);
}

void display_player(SDL_Renderer *rend)
{
  	/*
	SDL_SetRenderDrawColor(rend, 0, 0xff, 0, 0xff);
	SDL_RenderDrawPoint(rend, point_x, point_y);
	*/

	SDL_Rect fillRect = { point_x, point_y, 10, 10 };
    SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
    SDL_RenderFillRect(rend, &fillRect);


}

int poll_events()
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				//printf("You pressed key: %d\n", key.keysym.scancode);
				/* If "ESC" is pressed */
				if (key.keysym.scancode == 0x29)
					return (1);
				else if (key.keysym.scancode == KEY_A)
				{
					point_x -= 5;
					//printf("%f\n", point_x);
				}
				else if (key.keysym.scancode == KEY_D)
				{
					point_x += 5;
					//printf("%f\n", point_x);
				}
				else if (key.keysym.scancode == KEY_W)
				{
					point_y -= 5;
					//printf("%f\n", point_y);
				}
				else if (key.keysym.scancode == KEY_S)
				{
					point_y += 5;
					//printf("%f\n", point_y);
				}
				break;
		}
	}
	return (0);
}
