#include "actions.h"


float point_x = 300.00, point_y = 300.00;
int KEY_A = 4, KEY_D = 7, KEY_W = 26, KEY_S = 22;
int map_Xgrids = 8, map_Ygrids = 8, map_size = 64;

int map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void draw_map(SDL_Renderer *rend)
{
	int x, y, sized_x, sized_y, index;
	SDL_Rect fillRect;

	// The size (width and height) of each grid will always be thesame
	fillRect.w = fillRect.h = map_size - 1;
	
	for (y = 0; y < map_Ygrids; y++)
	{
		for (x = 0; x < map_Xgrids; x++)
		{
			index = y * map_Xgrids + x;

			// Set Rendering color for walls or space 
			if (map[index] == 1)
				SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
			else 
				SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xff);
			
			// Scale grid indexes to size
			sized_x = x * map_size;
			sized_y = y * map_size;

			// Display grid as a filled rectangle
			fillRect.x = sized_x;
			fillRect.y = sized_y;
    		
			SDL_RenderFillRect(rend, &fillRect);
		}
	}
}


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
