#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL.h>
#include <stdio.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);

#endif
