#include "maze.h"
#include "helpers.h"


/**
 * draw_thick_point - Entry point.
 * @x - 
 * @y -
 *
 * Return: Nothing;
 */
/*
void draw_thick_point(int x, int y, int weight)
{

}


/**
 * draw_thick_line - Entry point.
 * @x1 - 
 * @y1 - 
 * @x2 - 
 * @y2 -
 *
 * Return: Nothing.
 */
 /*
void draw_thick_line(SDL_Renderer *rend, float x1, float y1, float x2, float y2, int weight)
{
  
  int i;

  for (i = 0; i < 5; i++)
    SDL_RenderDrawLine(rend, x1 + i, y1, x2 + i, y2);
}
*/

/**
 * draw_stuff - test something is rendered..
 * @rend: the pointer to renderer that renders the map.
 *
 * Return: Nothing;
 */
void draw_stuff(SDL_Renderer *rend)
{ 
  SDL_SetRenderDrawColor(rend, 0xff, 0, 0, 0xff);
	SDL_RenderDrawLine(rend, 200, 300, 1000, 300);
}

