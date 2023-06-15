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
 * @rend: the pointer to renderer that renders the lines.
 *
 * Return: Nothing;
 */
void draw_rays(SDL_Renderer *rend)
{ 
  int casted_grids;
  int map_rx, map_ry, map_position; // Designates on-map equivalents for ray_x, ray_y;
  float ray_x, ray_y, ray_angle, ray_x_offset, ray_y_offset;
  
  /* 
   * defines negative inverse of tangent...
   * (mathfix for setting reference point
   * of player to North instead of the default NorthEast)
   * Also generates negative tan for raycasts towards the 
   * left direction and positive tan for right direction.
   */
  float aTan;

  ray_angle = point_angle;
  aTan = 1/ tan(ray_angle);
  casted_grids = 0;

  if (ray_angle == 0 || ray_angle == PI) // Facing Eastwards/ westwards
  {
    ray_y = point_y;
    ray_x = point_x;
    casted_grids = 8;
  }
  else if (ray_angle > PI) // Facing Northwwards
  {
    ray_y = (((int)point_y >> 6) << 6); // 0.0001 accounts for float imperfections
    ray_x = aTan * (ray_y - point_y) + point_x; // Some trigonometry
    
    // hold constant horizontal and vertical offsets for further gridlines
    ray_y_offset = -64;
    ray_x_offset = (aTan * ray_y_offset);
  }
  else // Facing Southwards
  {
    ray_y = (((int)point_y >> 6) + 1) << 6 ;
    ray_x = aTan * (ray_y - point_y) + point_x; // Some trigonometry
    
    // hold constant horizontal and vertical offsets for further gridlines
    ray_y_offset = 64;
    ray_x_offset = (aTan * ray_y_offset);
 
  }
  
  while(casted_grids < 2)
  {
    map_rx = (int) ray_x >> 6;
    map_ry = (int) ray_y >> 6;

    map_position = map_ry * map_Xgrids + map_rx;

    if (map_position < map_Xgrids * map_Ygrids && map[map_position] == 1) // Touches wall
    {
      casted_grids = 8;
    }
    else // Next grid
    {
      casted_grids++;
      ray_x += ray_x_offset;
      ray_y += ray_y_offset;
    }
  }

  /*
  map_rx = (int) ray_x >> 6;
  map_ry = (int) ray_y >> 6;
*/
  //printf("Angle: %f, Ray Points: x: %f, y: %f, Position: x: %f, y: %f\n", ray_angle,ray_x, ray_y, point_x, point_y);
	SDL_RenderDrawLine(rend, point_x, point_y, ray_x, ray_y);
}


/**
 * display_player - renders the player on the map using position.
 * @rend: the pointer to renderer that renders the player.
 * 
 * Return: Nothing;
 */
void display_player(SDL_Renderer *rend)
{
	SDL_Rect fillRect = { point_x - 5, point_y - 5, 10, 10 };
  SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
  SDL_RenderFillRect(rend, &fillRect);

  //SDL_SetRenderDrawColor(rend, 0xff, 0xff,  0, 0xff);
	SDL_RenderDrawLine(rend, point_x, point_y, (point_x + dpoint_x * 3), (point_y + dpoint_y * 3));
	//SDL_RenderDrawLine(rend, point_x + 5, point_y + 5, (point_x + dpoint_x * 3) + 5, (point_y + dpoint_y * 3) + 5);
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
    point_x = 64.00, point_y = 320.00;
    point_angle = 0.5;
    dpoint_x = cos(point_angle) * 5, dpoint_y = sin(point_angle) * 5;

    return (0);
}
