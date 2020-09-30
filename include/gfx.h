#include "common.h"

#define NB_PARTICLES_SMOKE_AVAILABLE	7
#define NB_PARTICLES_SMOKE_DISPLAY		10
#define PARTICLE_SMOKE_SCALE	0.4f
#define PARTICLE_SMOKE_FRAME_DURATION	10

#define NB_PARTICLES_NITRO_AVAILABLE	5
#define NB_PARTICLES_NITRO_DISPLAY		10
#define PARTICLE_NITRO_SCALE	0.3f
#define PARTICLE_NITRO_FRAME_DURATION	10

#define NB_SPRITE_BUSH 6

struct texture {
    // width and height
    int w, h;
    // texture
	SDL_Texture *texture;
};

struct particle {
	int pos_x;
	int pos_y;
	int frame; // current frame
	struct texture *t;
};

struct background_layers_x_offset {
	int sky_far;
	int landscape_far;
	int landscape_near;
	int sky_near;
};


// grapĥics of the game
struct game_graphics{
    // image textures
	/*struct texture car_player_rear;
	struct texture car_player_right1;
	struct texture car_player_right2;*/

	struct texture car_side_bg;

	//struct car_model_texture cars[CAR_MODEL_LAST]; 
	struct texture cars[CAR_MODEL_LAST][CAR_SPRITE_LAST];
	struct texture cars_side[CAR_MODEL_LAST];
	struct texture cars_stats[CAR_MODEL_LAST];

	struct texture bg_landscape_far;
	struct texture bg_sky_near;
	struct texture bg_sky_far;
	struct background_layers_x_offset layers_x_offset;

	struct texture scene_tree_oak;
	struct texture scene_tree_willow;
	struct texture scene_tree_pine;
	struct texture scene_cabin;
	
	struct texture scene_start_lane;
	
	struct texture scene_fence;
	struct texture scene_grass;
	struct texture scene_barn;
	struct texture scene_windmill;
	struct texture scene_well;
	
	struct texture scene_bushes[NB_SPRITE_BUSH];
	struct texture scene_bush_flower;

	// scene castle
	struct texture scene_wall;
	struct texture scene_tower;
	struct texture scene_gargamel;

	// scene egypt
	struct texture scene_dune_01;
	struct texture scene_dune_02;
	struct texture scene_dune_03;
	struct texture scene_egypt_column;
	struct texture scene_egypt_temple;
	struct texture scene_ram_statue;

	// scene greece
	struct texture scene_column_01;
	struct texture scene_column_02;
	struct texture scene_column_03;
	struct texture scene_delphi;
	struct texture scene_temple;

	// scene fork
	struct texture scene_big_rock;
	struct texture scene_rock_01;
	struct texture scene_rock_02;
	struct texture scene_rock_03;
	struct texture scene_rock_04;
	struct texture scene_rock_05;
	struct texture scene_cactus_01;
	struct texture scene_cactus_02;
	struct texture scene_cactus_03;
	struct texture scene_cactus_04;
	struct texture scene_desert_grass_01;
	struct texture scene_desert_grass_02;

	// scene city
	struct texture scene_tunnel_a_bright;	
	struct texture scene_tunnel_a_dark;	
	struct texture scene_building_01;	
	struct texture scene_building_02;	
	struct texture scene_building_03;	

	// scene spooky
	struct texture scene_vault;	
	struct texture scene_grave_01;	
	struct texture scene_grave_02;	
	struct texture scene_grave_03;	
	struct texture scene_grave_fence;	
	struct texture scene_tree_spooky;

	// scene fun fair
	struct texture scene_circus;	
	struct texture scene_rollercoaster;	
	struct texture scene_greatwheel;	
	struct texture scene_carousel;	
	
	// scene seaside
	struct texture scene_maoi;
	struct texture scene_buoy;
	struct texture scene_tree_palm;
	struct texture scene_boat_speed;
	struct texture scene_beach_cabin;
	struct texture scene_beach_umbrella;
	struct texture scene_billboard_beach;
	
	// scene frost
	struct texture scene_igloo;
	struct texture scene_snow_inn;
	struct texture scene_snowman;
	struct texture scene_lantern;
	struct texture scene_bench;
	struct texture scene_tree_pine_snow;
	struct texture scene_tree_dead_snow;

	//struct texture font_game_speed_title;
	struct texture font_game_speed_value;
	struct texture font_game_speed_unit;
	//struct texture font_game_position_title;
	struct texture font_game_position_value;
	struct texture font_game_position_unit;
	struct texture font_game_lap_title;
	struct texture font_game_lap_value;
	/*struct texture font_game_laptime_title;
	struct texture font_game_laptime_value;
	struct texture font_game_laptime_unit;*/
	
	struct texture font_race_anim;
	struct texture font_race_anim_2;
	struct texture font_race_anim_3;

	struct texture t_smoke[NB_PARTICLES_SMOKE_AVAILABLE];
	struct texture t_nitro[NB_PARTICLES_NITRO_AVAILABLE];

	/* particles */
	struct particle part_smoke[NB_PARTICLES_SMOKE_DISPLAY];
	struct particle part_nitro[NB_PARTICLES_NITRO_DISPLAY];

	struct texture track_thumbnail[TRACK_LAST];

	struct texture gui_settings;
	struct texture gui_credit;
	struct texture gui_exit;
	struct texture gui_prev;
	struct texture gui_play;
	struct texture gui_up;
	struct texture gui_down;
	struct texture gui_pause;
	struct texture gui_lock;

	struct texture gui_case;
	struct texture gui_accel;
	struct texture gui_brake;
	struct texture gui_left;
	struct texture gui_right;
};


