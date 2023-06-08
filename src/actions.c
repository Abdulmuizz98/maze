#include "maze.h"
#include "actions.h"

float point_x, point_y, point_angle, dpoint_y, dpoint_x;
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
					point_angle -= 0.1;
					if (point_angle < 0)
						point_angle += 2 * PI;
					
					dpoint_x = cos(point_angle) * 5;
					dpoint_y = sin(point_angle) * 5;
					//printf("%f\n", point_x);
				}
				else if (key.keysym.scancode == KEY_D)
				{
					point_angle += 0.1;
					if (point_angle > PI * 2)
						point_angle -= 2 * PI;
					
					dpoint_x = cos(point_angle) * 5;
					dpoint_y = sin(point_angle) * 5;
					//printf("%f\n", point_x);
				}
				else if (key.keysym.scancode == KEY_W)
				{
					point_y += dpoint_y;
					point_x += dpoint_x;
					//printf("%f\n", point_y);
				}
				else if (key.keysym.scancode == KEY_S)
				{
					point_y -= dpoint_y;
					point_x -= dpoint_x;
					//printf("%f\n", point_y);
				}
				break;
		}
	}
	return (0);
}

int init_instance(SDL_Instance *instance)
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
        return (1);
    }

    // Create a new Window instance
    instance->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    if (instance->window == NULL)
    {
        fprintf(stderr, "Cannot create window: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    // Create a new Renderer instance linked to the window
    instance->renderer = SDL_CreateRenderer(instance->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (instance->renderer == NULL)
    {
        SDL_DestroyWindow(instance->window);
        fprintf(stderr, "Cannot create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    // Initalize the globals...
    point_x = 300.00, point_y = 300.00;
    point_angle = 0.00;
    dpoint_x = cos(point_angle) * 5, dpoint_y = sin(point_angle) * 5;


    return (0);
}

