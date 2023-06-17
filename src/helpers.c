#include "maze.h"
#include "helpers.h"


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
