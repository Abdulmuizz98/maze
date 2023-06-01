#include "maze.h"
#include "actions.h"


int main(void)
{
	SDL_Instance instance;
	int status;

	status = init_instance(&instance);
	//status = init();
	
	printf("%d\n", status);
	//status = SDL_SetRenderDrawColor(instance.renderer, 255, 255, 0 , 100);
	if (instance.renderer == NULL)
		printf("renderer is still NULL\n");
	if (instance.window == NULL)
		printf("window is still NULL\n");

	
	/**
	 * C will always be amazing.
	 * This is an infinite loop.
	 * Each loop represents a frame.
 	 */
	while("C is amazing!")
	{
		// Clear the renderer
		status = SDL_SetRenderDrawColor(instance.renderer, 255, 255, 0 , 100);
		SDL_RenderClear(instance.renderer);
		if (poll_events() == 1)
			break;
		// Draw some stuff here
		draw_stuff(instance.renderer);
		
		// Flush the renderer
		SDL_RenderPresent(instance.renderer);
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
