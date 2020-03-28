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


/////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FPS 30
#define MS_PER_SEC 1000

#define SOFACHROME_FONT "./media/font/GeneraleStation-Regular.otf"
//#define SOFACHROME_FONT "./media/font/01 DigitMono.ttf"

#define PNG_CAR_PLAYER "./media/car_rear_01.png"
#define PNG_BG_MOUNTAINS "./media/bg_mountains.png"
#define PNG_BG_SKY_NEAR "./media/bg_clouds_near.png"
#define PNG_BG_SKY_FAR "./media/bg_clouds_far.png"
#define PNG_SCENE_TREE_OAK "./media/scene_tree_oak.png"
#define PNG_SCENE_TREE_WILLOW "./media/scene_tree_willow.png"
#define PNG_SCENE_TREE_PINE "./media/scene_tree_pine.png"
#define PNG_SCENE_CABIN "./media/scene_cabin.png"
#define PNG_SCENE_FENCE "./media/scene_fence.png"
#define PNG_SCENE_GRASS "./media/scene_grass.png"
#define PNG_SCENE_BUSH "./media/scene_bush.png"
#define PNG_SCENE_WINDMILL "./media/scene_windmill.png"
#define PNG_SCENE_BARN "./media/scene_barn.png"

//#define PLAYER_Y (SCREEN_HEIGHT - 30)

#define PNG_AI_CAR_01 "./media/car_rear_02.png"
//#define PNG_AI_CAR_01 "./media/rect_h.png"

#define ROAD_SEGMENT_LENGTH 200

#define RUMBLE_LENGTH 3

#define PLAYER_CAR_SPRITE_ZOOM 0.5f
#define AI_CAR_SPRITE_ZOOM 0.22f


#define NB_AI_CARS 17

/////////////////////////////////////////////////////////////////
// enums
/////////////////////////////////////////////////////////////////

enum game_status {
	GAME_STATE_UNKNOWN = 0,
	GAME_STATE_TITLE,
	GAME_STATE_CREDIT,
	GAME_STATE_GAME,
	GAME_STATE_RACE,
	GAME_STATE_RACE_COLLISION_SCENE,
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


// turn curve level and direction
enum road_curve {
	CURVE_LEFT_HARD = -6,
	CURVE_LEFT_MEDIUM = -4,
	CURVE_LEFT_EASY = -2,
	CURVE_NONE = 0,
	CURVE_RIGHT_EASY = 2,
	CURVE_RIGHT_MEDIUM = 4,
	CURVE_RIGHT_HARD = 6
};

// 'altitude' of the road
enum road_hill {
	HILL_DOWN_HIGH = -60,
	HILL_DOWN_MEDIUM = -40,
	HILL_DOWN_LOW = -20,
	HILL_DOWN_SLIGHT = -10,
	HILL_NONE = 0,
	HILL_UP_SLIGHT = 10,
	HILL_UP_LOW = 20,
	HILL_UP_MEDIUM = 40,
	HILL_UP_HIGH = 60
};

// length in segment of a road sector
enum road_sector_length {
 	SECTOR_LENGTH_SHORT = 25,
 	SECTOR_LENGTH_MEDIUM = 50,
 	SECTOR_LENGTH_LONG = 100
};


//static float SPRITES_SCALE = 0.3 * (1.f / 80.f);

/////////////////////////////////////////////////////////////////
// structures
/////////////////////////////////////////////////////////////////

struct background_layers_x_offset {
	int sky_far;
	int landscape_far;
	int landscape_near;
	int sky_near;
};

struct texture {
    // width and height
    int w, h;
    // texture
	SDL_Texture *texture;
};

// grapĥics of the game
struct game_graphics{
    // image textures
	struct texture car_player;
	struct texture bg_mountains;
	struct texture bg_sky_near;
	struct texture bg_sky_far;
	struct texture scene_tree_oak;
	struct texture scene_tree_willow;
	struct texture scene_tree_pine;
	struct texture scene_cabin;
	
	struct texture scene_fence;
	struct texture scene_grass;
	struct texture scene_bush;
	struct texture scene_barn;
	struct texture scene_windmill;
	
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

};

struct color_desc {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
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
	SDL_Rect *hitbox;
	int scaled_x;	
	//int scaled_w;	// TODO: useless ???
};

struct scene_segment_desc {
	size_t nb_sprites;
	struct scene_sprite_desc **sprite;
};

struct road_segment {

	struct segment_point p1;
	struct segment_point p2;
	//enum road_curve curve;
	float curve;
	enum color_road color;
	struct scene_segment_desc *scene;
	//struct scene_sprite_desc sprite_desc;

};

struct keys_status {
	int accel;
	int brake;
	int left;
	int right;
	int nitro;
};

struct ai_car_info {
	// lane on which is the car
	size_t lane;
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
	// car position (distance) on the road
	size_t pos_z;
	float pos_z_rest_percent;
	// car position segment idx
	size_t segment;
	// distance done by this car
	int distance;

	// car hitbox
	SDL_Rect hitbox;

	// car sprite
	struct texture t;

};

// game context, contains all information of the game
struct game_context {

	// how many 'update' frames per second
	//int fps = 30; // how many 'update' frames per second


	// how long is each frame (in seconds)
	int step;
    // number of road segments of the track
    size_t nb_segments;
	// array of road segments
	struct road_segment *segments; // array of road segments

	// factor to provide resolution independence (computed) actually half
	// the roads width, easier math if the road spans from -roadWidth to
	// +roadWidth
	int road_width;
	// length of a single segment
	//int segment_length;
	// number of segments per red/white rumble strip
	int rumble_length;
	// z length of entire track (computed)
	size_t track_length; //null;
	// number of lanes
	size_t lanes;
	// angle (degrees) for field of view
	float field_of_view;
	// z height of camera
	int camera_height;
	// z distance camera is from screen (computed)
	float camera_depth;
	// number of segments to draw
	size_t draw_distance;

	// highest point on screen
	size_t max_y;
	size_t max_y_idx;

	// highest point on screen
	size_t max_y_bis;
	// second highest point on screen
	size_t max_y_bis_idx;

	// player x offset from center of road (-1 to 1 to
	// stay independent of roadWidth)
	float player_x;
	// position of player car in the world
	int player_y;
	// player relative z distance from camera (computed)
	size_t player_z;
	// position of player car sprite in pixel(top of texture)
	int player_sprite_y;
	// exponential fog density
	int fog_density;
	// current camera Z position (add playerZ to get player's absolute Z
	// position)
	size_t position;
	// current speed
	float speed;
	// top speed (ensure we can't move more than 1 segment in
	// a single frame to make collision detection easier)
	float max_speed;
	// acceleration rate - tuned until it 'felt' right
	float accel;
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
	size_t player_segment;

	int player_car_x_in_pixels;
	
	// collion related
	float collision_dst_x;

    // window
    SDL_Window *window;
    // renderer
    SDL_Renderer *renderer;

    // current status in state machine
    enum game_status status_cur;
    // previous status in state machine
    enum game_status status_prev;

    // font to display text
    TTF_Font *sc_font_big;
    TTF_Font *sc_font_medium;

    TTF_Font *font_choice;
    TTF_Font *font_game_text;

    // graphic related stuff
    //struct game_graphics gfx;

    // sounds
    //struct game_media sfx;

    int mute_sfx;
    int mute_music;

	struct background_layers_x_offset layers_x_offset;

    // event
    SDL_Event event;
    // action
    enum input_action action;

    // timer reference
    Uint32 start_ticks;
    
	Uint32 ts_prev;
	Uint32 ts_cur;
	float dt;

	// struct containing all the sprites
	struct game_graphics gfx;

	struct keys_status keys;

	struct ai_car_info ai_cars[NB_AI_CARS];

    // quit game when set to 1
    int exit;
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

static inline size_t inline_increase ( size_t start, size_t increment, size_t max)
{
	if(max == 0) {
		SDL_Log("[%s] ERROR: max == 0", __func__);
		return 0;
	}

	size_t result = start + increment;

	while(result >= max)
		result -= max;
	while (result < 0)
		result += max;

	return result;
}


static inline size_t inline_get_segment_idx(struct game_context *ctx, size_t z) {

  return ((z/ROAD_SEGMENT_LENGTH) % ctx->nb_segments);
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

/////////////////////////////////////////////////////////////////
// functions declarations
/////////////////////////////////////////////////////////////////

int track_build(struct game_context *ctx);

int road_add_sector(struct road_segment *segments,
				int start_idx,
				int sector_enter_lg,
				int sector_hold_lg,
				int sector_exit_lg,
				int y,
				enum road_curve curve);

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
/*static*/ float ai_lane_to_posx(size_t idx_lane, size_t nb_lanes);

int ai_car_init(struct game_context *ctx);
int logic_race_ai_cars(struct game_context *ctx);

int load_texture_from_file(struct game_context *ctx,
			   char *path,
			   struct texture *in);

int main_display(struct game_context *ctx);

int main_logic(struct game_context *ctx);

int main_event(struct game_context *ctx);
