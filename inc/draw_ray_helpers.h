/**
 *	This header contains helper functions for casting rays.
 *
 */


#ifndef _DRAW_RAY_HELPERS_H_
#define _DRAW_RAY_HELPERS_H_


/********** DECLARATIONS **********/
float linear_distance(float x1, float y1, float x2, float y2);
Point vertical_ray_point();
Point horizontal_ray_point();
Point find_wall(Point initial_point, int casted_grids, int is_horizontal);


#endif "_DRAW_RAY_HELPERS_H_"
