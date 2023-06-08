/**
 * 	This header contains the declaration of in-game action functions.
 *
 */


#ifndef _ACTIONS_H_
#define _ACTIONS_H_


/********** DECLARATIONS **********/
int init_instance(SDL_Instance *);
void display_player(SDL_Renderer *); 
void draw_stuff(SDL_Renderer *);
int poll_events(void);


#endif "_ACTIONS_H_"
