#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "common.h"
#include "race.h"
#include "track.h"
#include "sound.h"
#include "gfx.h"


/////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FPS 30
#define MS_PER_SEC 1000




#define SOFACHROME_FONT "./media/font/GeneraleStation-Regular.otf"



//#define PLAYER_Y (SCREEN_HEIGHT - 30)

#define LANE_WIDTH 700
#define ROAD_SEGMENT_LENGTH 200

#define RUMBLE_LENGTH 3

#define PLAYER_CAR_SCALE_FALCON 1.f
#define PLAYER_CAR_SCALE_LOTUS 1.f
#define PLAYER_CAR_SCALE_IMPREZIA 0.66f
#define PLAYER_CAR_SCALE_NSX 0.8f
#define PLAYER_CAR_SCALE_TRUENO 1.f
#define PLAYER_CAR_SCALE_TT 1.f
#define PLAYER_CAR_SCALE_VIPER 1.f
#define PLAYER_CAR_SCALE_HART 1.f
#define PLAYER_CAR_SCALE_DELTA 1.f
#define PLAYER_CAR_SCALE_LANCER 1.f

#define AI_CAR_SCALE_FALCON 0.4f
#define AI_CAR_SCALE_LOTUS 0.4f
#define AI_CAR_SCALE_IMPREZIA 0.33f
#define AI_CAR_SCALE_NSX 0.4f
#define AI_CAR_SCALE_TRUENO 0.4f
#define AI_CAR_SCALE_TT 0.4f
#define AI_CAR_SCALE_VIPER 0.4f
#define AI_CAR_SCALE_HART 0.4f
#define AI_CAR_SCALE_DELTA 0.4f
#define AI_CAR_SCALE_LANCER 0.4f

#define NB_AI_CARS 19
//#define NB_AI_CARS 1
#define AI_SEGMENTS_SPACING 20

#define START_ANIM_DURATION	5

#define CAMERA_HEIGHT_RACE 1000
#define CAMERA_HEIGHT_START 10000


#define MAX_SCENE_SPRITE_PER_SEG 40
 

/////////////////////////////////////////////////////////////////
// enums
/////////////////////////////////////////////////////////////////

enum game_status {
	GAME_STATE_UNKNOWN = 0,
	GAME_STATE_TITLE,
	GAME_STATE_CREDIT,
	GAME_STATE_GAME,
	GAME_STATE_MENU_MAIN,
	GAME_STATE_MENU_SELECT_TRACK,
	GAME_STATE_MENU_SELECT_CAR,
	GAME_STATE_MENU_OPTION,
	GAME_STATE_RACE,
	GAME_STATE_RACE_ANIM_START,
	GAME_STATE_RACE_ANIM_END,
	GAME_STATE_RACE_COLLISION_SCENE,
	GAME_STATE_RACE_NITRO,
	GAME_STATE_PAUSE,
	GAME_STATE_GAMEOVER,
	GAME_STATE_QUIT
};

enum input_action {
    ACTION_NONE = 0,
    ACTION_ESCAPE,
    ACTION_ENTER,
    ACTION_PAUSE,
    ACTION_UP,
    ACTION_DOWN,
    ACTION_DOWN_RELEASED,
    ACTION_LEFT,
    ACTION_RIGHT
};

enum color_road {
	COLOR_DARK,
	COLOR_BRIGHT,
	COLOR_START
};

enum ai_car_state {
	AI_CAR_STATE_SPEED_FULL = 0,
	AI_CAR_STATE_SPEED_SLOW,
	AI_CAR_STATE_SPEED_BEHIND_PLAYER,
	AI_CAR_STATE_SWITCHING_LANE_LEFT,
	AI_CAR_STATE_SWITCHING_LANE_RIGHT
};


enum scene_sprite_type {
	SCENE_SPRITE_NORMAL = 0,
	SCENE_SPRITE_CENTERED
};

//static float SPRITES_SCALE = 0.3 * (1.f / 80.f);

/////////////////////////////////////////////////////////////////
// structures
/////////////////////////////////////////////////////////////////




/*struct car_model_texture{
    // image textures
	struct texture rear;
	struct texture right_1;
	struct texture right_2;
};*/


struct race_info {

	// race duration in milli seconds
	int race_time_ms;

	// angle (degrees) for field of view
	float field_of_view;
	// z height of camera
	int camera_height;
	// z distance camera is from screen (computed)
	float camera_depth;
	// number of segments to draw
	int draw_distance;

	// highest point on screen
	int max_y;
	int max_y_idx;
	// highest point on screen
	int max_y_bis;
	// second highest point on screen
	int max_y_bis_idx;
	// nb of lap of the race
	int nb_lap;
	int nb_lap_logic;
	// nb_lap the player has done
	int player_lap;

	// number of frame spent in STATE_RACE_ANIM_START
	int nb_frame_anim;
	int finish_placed_frame_nb;
	int bgm_name_dislayed;
};


struct segment_point_coord {
	int x;
	float y;
	float z;
	int w;
	float scale; // TODO: num + den ?
};

struct segment_point {
	struct segment_point_coord world;
	struct segment_point_coord screen;
	struct segment_point_coord camera;
};

struct scene_sprite_desc {
	struct texture *t;
	float position;
	float scale;
	SDL_RendererFlip flip;
	// 1 if sprite cause collision, 0 otherwise
	int collide;
	// determine the hitbox of the sprite within the texture (eg. trunk of a tree)
	SDL_Rect *hitbox;
	int scaled_x;	
	//int scaled_w;	// TODO: useless ???
};

struct scene_seg_desc {
	int nb_sprites;
	struct scene_sprite_desc sprite[MAX_SCENE_SPRITE_PER_SEG];
	enum scene_sprite_type type;
};

struct road_segment {

	struct segment_point p1;
	struct segment_point p2;
	//enum road_curve curve;
	float curve;
	enum color_road color;
	struct scene_seg_desc *scene;
	int nb_lanes;
	int width;
	//struct scene_sprite_desc sprite_desc;
	struct color_desc_scene *cds;

};

struct keys_status {
	int accel;
	int accel_prev;
	int brake;
	int left;
	int right;
	int nitro;
	int nitro_prev;

	int up;
	int down;
	int select;
	int back;

	int volume_music;
	int volume_sfx;
	int reset_save;
};

struct ai_car_info {
	// lane on which is the car
	int lane;
	// x postion
	float pos_x;
	// acceleration
	float accel;
	// current speed
	float speed;
	// max speed on straight road
	float speed_max_straight;
	// max speed in curves
	float speed_max_curve;

	// to use in SLOW state
	float speed_slow_straight;
	float speed_slow_curve;


	// car position (distance) on the road
	int pos_z;
	float pos_z_rest_percent;
	// car position segment idx
	int segment;
	// distance done by this car
	int distance;

	// car hitbox
	SDL_Rect hitbox;

	// car sprite
	enum car_sprite_idx sprite_idx;
	enum car_model_type car_model;	
	SDL_RendererFlip car_flip;

	//struct texture *t;
	
	//struct car_model_texture;
	float car_x_scale_coef;
	float ai_car_scale_coef;

	enum ai_car_state state;
	// idx of the closest car ahead. Align speeds (straight and turn on this car)
	int closest_car_idx;
	// destination x value when switching lane
	float dest_x;
	int dest_lane;

	// number of frame the AI car is in 'BEHIND_CAR' state after colliding it from behind
	int behind_player_frames;

};



// game context, contains all information of the game
struct game_context {

	/**********************************************************************/
	/* global ****************************************************************/

	// how long is each frame (in seconds)
	int step;

    // window
    SDL_Window *window;
    // renderer
    SDL_Renderer *renderer;

    // current status in state machine
    enum game_status status_cur;
    // previous status in state machine
    enum game_status status_prev;

    // event
    SDL_Event event;
    // action
    enum input_action action;

    // timer reference
    Uint32 start_ticks;
	Uint32 ts_prev;
	Uint32 ts_cur;
	// delta time between 2 frame. float time to avoid several cast
	float dt;

	struct keys_status keys;

	float scale_player_car[CAR_MODEL_LAST];
	float scale_ai_car[CAR_MODEL_LAST];

    // quit game when set to 1
    int exit;
	// TODO: move elsewhere more relevant
	// constant computed once to avoid computation at each frame
	float scene_sprite_coef;


	/**********************************************************************/
	/* track ****************************************************************/
	struct track_info track;

	/**********************************************************************/
	/* player car *************************************************************/
	struct player_car pcar;

	/**********************************************************************/
	/* ai car *************************************************************/
	struct ai_car_info ai_cars[NB_AI_CARS];


	/* HUD **************************************************************/

    // font to display text
    TTF_Font *sc_font_big;
    TTF_Font *sc_font_medium;

    TTF_Font *font_choice;
    TTF_Font *font_game_text;


	/**********************************************************************/
	/* sound **************************************************************/
	struct sound_info sound;

	/**********************************************************************/
	/* gfx **************************************************************/
	// struct containing all the sprites
	struct game_graphics gfx;

	/**********************************************************************/
	/* race related *******************************************************************/

	struct race_info race;

};


/////////////////////////////////////////////////////////////////
// inline function
/////////////////////////////////////////////////////////////////

static inline float inline_accelerate( float speed, float coef, float dt)
{
	return speed + coef * dt / 100.f; 
}


static inline float inline_limit(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
	
}

static inline int inline_increase ( int start, int increment, int max)
{
	if(max == 0) {
		SDL_Log("[%s] ERROR: max == 0", __func__);
		return 0;
	}

	int result = start + increment;

	while(result >= max)
		result -= max;
	while (result < 0)
		result += max;

	return result;
}


static inline int inline_get_segment_idx(struct game_context *ctx, int z) {

  return ((z/ROAD_SEGMENT_LENGTH) % ctx->track.nb_segments);
}


 static inline int inline_rumble_width (int projected_road_width, int lanes)
 {
	if(6 > 2*lanes)
	 	return projected_road_width/6;
	else 
		return projected_road_width/ (2 * lanes);
 }

 static inline int inline_lane_marker_width (int projected_road_width, int lanes)
 {
	int width;

	if (32 > 8 * lanes)
		width = projected_road_width/32;
	else
		width = projected_road_width/(8*lanes);

	return width; // == 0 ? 1 : width;
 }

static inline float inline_curve_in (float a, float b, float percent)
{
	return a + (b-a) * powf(percent, 2.f);
}

static inline float inline_curve_out (float a, float b, float percent)
{
	return a + (b-a) * (1.f-powf(percent, 2.f));
}

static inline float inline_curve_inout (float a, float b, float percent)
{
	return a + (b-a) * ( 0.5f - (cosf(percent * (float)M_PI) / 2.f));
}

static inline float inline_interpolate (float a,float b, float percent)
{ 
	return a + (b-a)*percent;
}


static inline int rand_interval(int min, int max)
{
    int r;
    const int range = 1 + max - min;
    const int buckets = RAND_MAX / range;
    const int limit = buckets * range;

    do {
        r = rand();
    } while (r >= limit);

    return (min + (r / buckets));
}


/////////////////////////////////////////////////////////////////
// functions declarations
/////////////////////////////////////////////////////////////////

int track_build(struct game_context *ctx);
int track_unload(struct game_context *ctx);

int road_add_sector(struct road_segment *segments,
		    int start_idx,
		    int sector_enter_lg,
		    int sector_hold_lg,
		    int sector_exit_lg,
		    int y,
		    /*int*/ float curve,
		    int nb_lanes_enter,
		    int nb_lanes_exit);

int logic_project_coord(struct segment_point *p,
			int first_segments_z_offset,
			int camera_x,
			int camera_y,
			int camera_z,
			float camera_depth,
			int width,
			int height,
			int road_width);

// TODO: make static (inline) ?
/*static*/ float ai_lane_to_posx(int idx_lane, int nb_lanes);

int ai_car_init(struct game_context *ctx);
int logic_race_ai_cars(struct game_context *ctx);


int logic_get_player_place_nb(struct game_context *ctx);
char* logic_get_player_place_suffix(int pos);
int logic_get_player_lap_nb(struct game_context *ctx);




int gfx_load_resources_title(struct game_context *ctx);
int gfx_load_resources_menu_main(struct game_context *ctx);
int gfx_load_resources_menu_select_track(struct game_context *ctx);
int gfx_load_resources_menu_select_car(struct game_context *ctx);
int gfx_load_resources_race(struct game_context *ctx);
int gfx_unload_resources(struct game_context *ctx);

int sound_load_resources_title(struct game_context *ctx);
int sound_load_resources_menu(struct game_context *ctx);
int sound_load_resources_race(struct game_context *ctx);
int sound_unload_resources(struct game_context *ctx);

int event_update_game_state(struct game_context *ctx, enum game_status state);

// display 
int display_screen_race(struct game_context *ctx);
int texture_render(struct game_context *ctx,
			  struct texture *t,
			  int x,
			  int y,
			  SDL_Rect *clip,
			  float angle,
			  float scale,
			  SDL_RendererFlip flip,
			  SDL_Rect *hitbox);
int display_load_render_text_with_shade(struct game_context *ctx,
					       TTF_Font *font,
					       struct texture *t,
					       char *msg,
					       SDL_Color *color_front,
					       SDL_Color *color_shadow,
					       int x_front,
					       int y_front,
					       int shadow_num,
					       int shadow_den,
					       float angle);
int display_load_render_text(struct game_context *ctx,
				    TTF_Font *font,
				    struct texture *t,
				    char *msg,
				    SDL_Color *color,
				    int x,
				    int y,
				    float angle);
int load_text_message(struct game_context *ctx,
			     TTF_Font *font,
			     struct texture *t,
			     char *string,
			     SDL_Color text_color);



int main_ctx_init_menu_main(struct game_context *ctx);
int main_ctx_init_menu_select_track(struct game_context *ctx);
int main_ctx_init_menu_select_car(struct game_context *ctx);
int main_ctx_init_menu_option(struct game_context *ctx);
int main_ctx_init_race(struct game_context *ctx);

int display_screen_menu_main(struct game_context *ctx);
int display_screen_menu_select_track(struct game_context *ctx);
int display_screen_menu_select_car(struct game_context *ctx);
int display_screen_menu_option(struct game_context *ctx);

int display_screen_title(struct game_context *ctx);

int display_render_background_layer(struct game_context *ctx,
					   enum background_layer bg_layer,
					   int *texture_x_offset,
					   struct texture *bg_texture);


char *sound_volume2string(enum sound_volume volume);

// MAINs
int main_sound(struct game_context *ctx);
int main_display(struct game_context *ctx);
int main_logic(struct game_context *ctx);
int main_event(struct game_context *ctx);
