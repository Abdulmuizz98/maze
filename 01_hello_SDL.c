#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[]){
	SDL_Window* window = NULL;

	//surface is just a 2D image loaded froma  file or can be image inside of a window.
	SDL_Surface* screenSurface = NULL;


	//Initialize SDL - You can't call any SDK funx without init SDL first.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)// Only passed video flag since all we need
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else{
		//Create Window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINES, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL){

			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else{
			
		}
	}

}
