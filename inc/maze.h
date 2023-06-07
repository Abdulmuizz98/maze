#ifndef _MAZE_H_
#define _MAZE_H_

/**** INCLUDES ****/
#include <SDL.h>
#include <stdio.h>


/**** STRUCTURES ****/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;


/**** DECLARATIONS ****/
int init_instance(SDL_Instance *);


#endif "_MAZE_H_"
