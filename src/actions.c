#include "actions.h"

void draw_stuff(SDL_Renderer *rend)
{
	SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0);
	SDL_RenderDrawLine(rend, 10, 10, 100, 100);
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
				/* If "ESC" is pressed */
				if (key.keysym.scancode == 0x29)
					return (1);
				break;
		}
	}
	return (0);
}
