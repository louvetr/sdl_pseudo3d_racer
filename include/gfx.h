#include "common.h"

#define NB_PARTICLES_SMOKE_AVAILABLE	7
#define NB_PARTICLES_SMOKE_DISPLAY		10
#define PARTICLE_SMOKE_SCALE	0.2f
#define PARTICLE_SMOKE_FRAME_DURATION	10

#define NB_PARTICLES_NITRO_AVAILABLE	5
#define NB_PARTICLES_NITRO_DISPLAY		10
#define PARTICLE_NITRO_SCALE	0.2f
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

	//struct car_model_texture cars[CAR_MODEL_LAST]; 
	struct texture cars[CAR_MODEL_LAST][CAR_SPRITE_LAST];

	struct texture bg_mountains;
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
};