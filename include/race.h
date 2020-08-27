#ifndef RACE_H
#define RACE_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "common.h"



enum player_sprite_orientation {
 	PLAYER_SPRITE_HARD_LEFT,
 	PLAYER_SPRITE_LIGHT_LEFT,
 	PLAYER_SPRITE_STRAIGHT,
 	PLAYER_SPRITE_LIGHT_RIGHT,
 	PLAYER_SPRITE_HARD_RIGHT
};


struct player_car
{
	// player x offset from center of road (-1 to 1 to
	// stay independent of roadWidth)
	float player_x;
	// position of player car in the world
	int player_y;
	// player relative z distance from camera (computed)
	int player_z;
	// current camera Z position (add playerZ to get player's absolute Z
	// position)
	int position;
	// current speed
	float speed;
	// top speed (ensure we can't move more than 1 segment in
	// a single frame to make collision detection easier)
	float max_speed;
	// acceleration rate - tuned until it 'felt' right
	float accel;
	// top speed under nitro
	float max_speed_nitro;
	// acceleration rate under nitro
	float accel_nitro;
	// number of nitro of player	
	int nb_nitro;
	// number of frames in nitro state
	int nitro_nb_frame;
	// deceleration rate when braking
	float breaking;
	// 'natural' deceleration rate when neither accelerating, nor braking
	float decel;
	// off road deceleration is somewhere in between
	float off_road_decel;
	// limit when off road deceleration no longer applies (e.g.
	// you can always go at least this speed even when off road)
	float off_road_limit;
	// centrifugal force applying to player in curves
	float centrifugal;
	// index of the current player segment in segments array
	int player_segment;
	int player_segment_prev;
	int player_segment_prev_prev;

	// player car sprite values
	int player_sprite_x;
	int player_sprite_y;
	int player_sprite_w;
	int player_sprite_h;
	int player_max_x;
	int player_max_y;

	// distance travelled by the player
	int player_distance_ran;

	// player position
	int player_place;
	// collision related
	float collision_dst_x;

	enum player_sprite_orientation car_orientation_cur;
	enum player_sprite_orientation car_orientation_prev;
	int same_car_orientation_in_frame;

	enum car_sprite_idx car_player_sprite_idx;
	enum car_model_type car_player_model;	
	SDL_RendererFlip car_player_flip;

};

#endif