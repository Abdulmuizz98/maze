#include "main.h"

int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
        return(1);
    }
    /* Create a new Window instance */
    instance->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1260, 720, 0);
    if (instance->window = NULL)
    {
        fprintf(stderr, "Cannot create window: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
    /* Create a new Renderer instance linked to the window */
    instance->renderer = SDL_CreateRenderer(instance->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (instance->renderer = NULL)
    {
        SDL_DestroyWindow(instance->window);
        fprintf(stderr, "Cannot create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
    return (0);
}