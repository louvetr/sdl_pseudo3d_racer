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

#define FPS 30;
#define MS_PER_SEC 1000

#define PNG_CAR_PLAYER "./media/car_rear_01.png"
#define PNG_BG_MOUNTAINS "./media/bg_mountains.png"
#define PNG_BG_SKY_NEAR "./media/bg_clouds_near.png"
#define PNG_BG_SKY_FAR "./media/bg_clouds_far.png"

//#define PLAYER_Y (SCREEN_HEIGHT - 30)


#define ROAD_SEGMENT_LENGTH 200

#define RUMBLE_LENGTH 3

/////////////////////////////////////////////////////////////////
// enums
/////////////////////////////////////////////////////////////////

enum game_status {
	GAME_STATE_UNKNOWN = 0,
	GAME_STATE_TITLE,
	GAME_STATE_CREDIT,
	GAME_STATE_GAME,
	GAME_STATE_RACE,
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
};

struct color_desc {
	int r;
	int g;
	int b;
	int a;
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

struct road_segment {

	struct segment_point p1;
	struct segment_point p2;
	//enum road_curve curve;
	float curve;
	enum color_road color;

};

struct keys_status {
	int accel;
	int brake;
	int left;
	int right;
	int nitro;
};

// game context, contains all information of the game
struct game_context {

	// how many 'update' frames per second
	//int fps = 30; // how many 'update' frames per second


	// how long is each frame (in seconds)
	int step;
    // number of road segments of the track
    int nb_segments;
	// array of road segments
	struct road_segment *segments; // array of road segments
	// var background    = null;                    // our background image
	// (loaded below) var sprites       = null;                    // our
	// spritesheet (loaded below) var resolution    = null; // scaling
	// factor to provide resolution independence (computed) actually half
	// the roads width, easier math if the road spans from -roadWidth to
	// +roadWidth
	int road_width;
	// length of a single segment
	//int segment_length;
	// number of segments per red/white rumble strip
	int rumble_length;
	// z length of entire track (computed)
	int track_length; //null;
	// number of lanes
	int lanes;
	// angle (degrees) for field of view
	float field_of_view;
	// z height of camera
	int camera_height;
	// z distance camera is from screen (computed)
	float camera_depth;
	// number of segments to draw
	int draw_distance;
	// player x offset from center of road (-1 to 1 to
	// stay independent of roadWidth)
	float player_x;
	// position of player car in the world
	int player_y;
	// player relative z distance from camera (computed)
	int player_z;
	// position of player car sprite in pixel(top of texture)
	int player_sprite_y;
	// exponential fog density
	int fog_density;
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
    // window
    SDL_Window *window;
    // renderer
    SDL_Renderer *renderer;

    // current status in state machine
    enum game_status status_cur;
    // previous status in state machine
    enum game_status status_prev;

    // font to display text
    TTF_Font *font;
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

static inline int  inline_increase ( int start, int increment, int max)
{
	//SDL_Log("[%s] ENTER with %d, %d, %d\n", __func__, start, increment, max);

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
  //return ctx->segments[Math.floor(z/segmentLength) % segments.length];
  //return ctx->segments[(z/ctx->segment_length) % ctx->nb_segments];

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
	return a + (b-a) * powf(percent, 2.);
}

static inline float inline_curve_out (float a, float b, float percent)
{
	return a + (b-a) * (1-powf(percent, 2.));
}

static inline float inline_curve_inout (float a, float b, float percent)
{
	return a + (b-a) * ( 0.5 - (cosf(percent * M_PI) / 2));
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

int main_display(struct game_context *ctx);

int main_logic(struct game_context *ctx);

int main_event(struct game_context *ctx);