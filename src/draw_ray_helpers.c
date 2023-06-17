#include "maze.h"
#include "draw_ray_helpers.h"


/**
 * linear_distance - Calculates the distance between 2 coordinates.
 * @x1 - the x-axis value of the first point
 * @y1 - the y-axis value of the first point
 * @x2 - the x-axis value of the second point
 * @y2 - the y-axis value of the second point
 *
 * Return: The distance between the points.
 */
float linear_distance(float x1, float y1, float x2, float y2)
{
  return (sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)));
}


/**
 * vertical_ray_point - Gets the point where a vertical ray ends.
 *
 * Return: The point where the vertical ray ends.
 */
Point vertical_ray_point()
{
  int casted_grids = 0;
    
  float ray_angle = player_angle;
  float aTan = tan(ray_angle); // holds tan and Reciprocal of tan for verical and horizontal casts resp.
   
  Point ray_point, initial_point;
    

  if (ray_angle == PI/2  || ray_angle == 3 * PI / 2) // Facing Northwards/ Southwards
  { 
    initial_point.y = player_point.y;
    initial_point.x = player_point.x;
    casted_grids = 8;
  }
  else if (ray_angle > PI/ 2 && ray_angle < 3 * PI / 2) // Facing Westwards
  {
    initial_point.x = (((int)player_point.x >> 6) << 6);
    initial_point.y = aTan * (initial_point.x - player_point.x) + player_point.y; // Some trigonometry
    
    // hold constant horizontal and vertical offsets for further gridlines
    initial_point.dx = -64;
    initial_point.dy = (aTan * initial_point.dx);
  }
  else // Facing Eastwards
  {
    initial_point.x = (((int)player_point.x >> 6) + 1) << 6 ;
    initial_point.y = aTan * (initial_point.x - player_point.x) + player_point.y; // Some trigonometry
    
    // hold constant horizontal and vertical offsets for further gridlines
    initial_point.dx = 64;
    initial_point.dy = (aTan * initial_point.dx);
  }
  
  ray_point = find_wall(initial_point, casted_grids, 0);
  return (ray_point);
}


/**
 * horizontal_ray_point - Gets the point where an horizontal ray ends.
 *
 * Return: The point where the horizontal ray ends.
 */
Point horizontal_ray_point()
{
  int casted_grids = 0;
    
  float ray_angle = player_angle;
  float aTan = 1 / tan(ray_angle); // holds tan and Reciprocal of tan for verical and horizontal casts resp.
   
  Point ray_point, initial_point;

  if (ray_angle == 0 || ray_angle == PI) // Facing Eastwards/ westwards
  {
    initial_point.y = player_point.y;
    initial_point.x = player_point.x;
    casted_grids = 8;
  }
  else if (ray_angle > PI) // Facing Northwwards
  {
    initial_point.y = (((int)player_point.y >> 6) << 6);
    initial_point.x = aTan * (initial_point.y - player_point.y) + player_point.x; // Some trigonometry
    
    // Hold constant horizontal and vertical offsets for further gridlines
    initial_point.dy = -64;
    initial_point.dx = (aTan * initial_point.dy);
  }
  else // Facing Southwards
  {
    initial_point.y = (((int)player_point.y >> 6) + 1) << 6 ;
    initial_point.x = aTan * (initial_point.y - player_point.y) + player_point.x; // Some trigonometry
    
    // hold constant horizontal and vertical offsets for further gridlines
    initial_point.dy = 64;
    initial_point.dx = (aTan * initial_point.dy);
  }
    
  ray_point = find_wall(initial_point, casted_grids, 1);
  return (ray_point);
}


/**
 * find_wall - Gets the point where a vertical ray ends.
 * @initial_point: The point on the first grid line (reference point)
 * @casted_grids: number of grids further to find the walli, or cast a  grid (if no wall).
 * @is_horizontal: 0 if vertical, otherwise it's horizontal.
 *
 * Return: The point where the verticl ray ends.
 */
Point find_wall(Point initial_point, int casted_grids, int is_horizontal)
{
  Point wall_point;
  int main_side, other_side, map_rx, map_ry;  // Designates on-map equivalents for ray_x, ray_y;

  wall_point = initial_point;

  while(casted_grids < 8)
  {
    map_rx = (int) wall_point.x >> 6;
    map_ry = (int) wall_point.y >> 6;

    main_side = map_ry * map_Xgrids + map_rx;
    other_side = (is_horizontal) ? main_side - 8 : main_side - 1;

    if (main_side < map_Xgrids * map_Ygrids && (map[main_side] == 1 || map[other_side] == 1) ) // Touches wall
    {
      casted_grids = 8;
    }
    else // Next grid
    {
      casted_grids++;
      wall_point.x += wall_point.dx;
      wall_point.y += wall_point.dy;
    }
  }

  return (wall_point);
}
