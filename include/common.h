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

//#define PLAYER_Y (SCREEN_HEIGHT - 30)

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
};


/////////////////////////////////////////////////////////////////
// structures
/////////////////////////////////////////////////////////////////

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
};

struct color_desc {
	int r;
	int g;
	int b;
	int a;
};

struct segment_point_coord {
	int x;
	int y;
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
	int segment_length;
	// number of segments per red/white rumble strip
	int rumble_length;
	// z length of entire track (computed)
	int track_length; //null;
	// number of lanes
	int lanes;
	// angle (degrees) for field of view
	int field_of_view;
	// z height of camera
	int camera_height;
	// z distance camera is from screen (computed)
	float camera_depth;
	// number of segments to draw
	int draw_distance;
	// player x offset from center of road (-1 to 1 to
	// stay independent of roadWidth)
	float player_x;
	// position of player car in pixel (top of texture)
	int player_y;
	// player relative z distance from camera (computed)
	int player_z;
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

  return ((z/ctx->segment_length) % ctx->nb_segments);
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


/////////////////////////////////////////////////////////////////
// functions declarations
/////////////////////////////////////////////////////////////////


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