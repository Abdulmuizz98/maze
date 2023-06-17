/**
 *	This header declares application wide globals.
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
/**
 * struct SDL_Instance - Data structure that holds SDL window and renderer.
 * @window: pointer to SDL_Window to initialize.
 * @renderer: pointer to the SDL_Renderer to attach to the window. 
 *
 * Description: Wholesome data structure to hold a window and its
 * associated renderer.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;


/**
 * struct Point - Data structure that holds a cartesian coordinate.
 * @x: x_axis value.
 * @y: y_axis value.
 *
 * Description: Helps hold points on the game like player points, ray pointse etc.
 */
typedef struct Point
{
  float x;
  float y;
  float dx; // x offset
  float dy; // y offset
} Point;


/********** GLOBAL VARIABLES DECLARATION **********/
//extern float point_x, point_y, point_angle, dpoint_y, dpoint_x;
extern Point player_point;
extern float player_angle;
extern int map_Xgrids, map_Ygrids, map_size, map[];


#endif "_MAZE_H_"
