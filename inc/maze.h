/**
 *	This header file defines application wide globals.
 *
 */


#ifndef _MAZE_H_
#define _MAZE_H_


/********** INCLUDES **********/
#include <math.h>
#include <SDL.h>
#include <stdio.h>


/********** MACROS **********/
#define PI 3.14159265359


/********** STRUCTURES **********/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;


/********** GLOBAL VARIABLES DECLARATION **********/
extern float point_x, point_y, point_angle, dpoint_y, dpoint_x;


#endif "_MAZE_H_"
