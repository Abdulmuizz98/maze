#include "maze.h"
#include "actions.h"
#include "draw_ray_helpers.h"

Point player_point;
float player_angle;
int KEY_A = 4, KEY_D = 7, KEY_W = 26, KEY_S = 22;
int map_Xgrids = 8, map_Ygrids = 8, map_size = 64;

int map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};


/**
 * draw_map - renders the game map.
 * @rend: the pointer to renderer that renders the map.
 *
 * Return: Nothing;
 */
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


/**
 * draw_rays - casts the rays as lines..
 * @rend: the pointer to renderer that renders the ray lines.
 *
 * Return: Nothing;
 */
void draw_rays(SDL_Renderer *rend)
{ 
  int rays;
  Point vertical_point, horizontal_point;
  float distance;
  
  for (rays = 0; rays < 1; rays++)
  {
    horizontal_point = horizontal_ray_point();
    vertical_point = vertical_ray_point();

    // Temporarily save horizontal ray distance... not yet sure it's the shortest.
    distance = linear_distance(player_point.x, player_point.y, horizontal_point.x, horizontal_point.y);
 
    SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
    
    // Take the shortest point as the ray points
    if (distance > linear_distance(player_point.x, player_point.y, vertical_point.x, vertical_point.y))
	    SDL_RenderDrawLine(rend, player_point.x, player_point.y, vertical_point.x, vertical_point.y);
    else 
	    SDL_RenderDrawLine(rend, player_point.x, player_point.y, horizontal_point.x, horizontal_point.y);
  }
}


/**
 * display_player - renders the player on the map using position.
 * @rend: the pointer to renderer that renders the player.
 * 
 * Return: Nothing;
 */
void display_player(SDL_Renderer *rend)
{
	SDL_Rect fillRect = { player_point.x - 5, player_point.y - 5, 10, 10 };
  SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
  SDL_RenderFillRect(rend, &fillRect);

  // Direction pointer
	SDL_RenderDrawLine(rend, player_point.x, player_point.y, (player_point.x + player_point.dx * 3), (player_point.y + player_point.dy * 3));
}


/**
 * poll_events - function that loops through player events and handles them.
 *
 * Return: 1 when player quits or presses ESC,
 * 0 when no further events.;
 */
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
					player_angle -= 0.1;
					if (player_angle < 0)
						player_angle += 2 * PI;
					
					player_point.dx = cos(player_angle) * 5;
					player_point.dy = sin(player_angle) * 5;
				}
				else if (key.keysym.scancode == KEY_D)
				{
					player_angle += 0.1;
					if (player_angle > PI * 2)
						player_angle -= 2 * PI;
					
					player_point.dx = cos(player_angle) * 5;
					player_point.dy = sin(player_angle) * 5;
				}
				else if (key.keysym.scancode == KEY_W)
				{
					player_point.y += player_point.dy;
					player_point.x += player_point.dx;
				}
				else if (key.keysym.scancode == KEY_S)
				{
					player_point.y -= player_point.dy;
					player_point.x -= player_point.dx;
				}
				break;
		}
	}
	return (0);
}


/**
 * init_instance - initialize SDL, a window and attaches renderer.
 * @instance: the pointer to data structure holding window and renderer.
 *
 * Return: 1 if it fails,
 * 0 if successful;
 */
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
    player_angle = 0.5001;
    player_point.x = 64.00, player_point.y = 320.00;
    player_point.dx = cos(player_angle) * 5, player_point.dy = sin(player_angle) * 5;

    return (0);
}
