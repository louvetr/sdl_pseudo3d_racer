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

//#define PNG_CAR_PLAYER "./media/car_rear_01.png"
#define PNG_IMPREZIA_REAR "./media/imprezia_rear.png"
#define PNG_IMPREZIA_RIGHT1 "./media/imprezia_right_1.png"
#define PNG_IMPREZIA_RIGHT2 "./media/imprezia_right_2.png"

#define PNG_FALCON_REAR "./media/falcon_rear.png"
#define PNG_FALCON_RIGHT1 "./media/falcon_right_1.png"
#define PNG_FALCON_RIGHT2 "./media/falcon_right_2.png"

#define PNG_LOTUS_REAR "./media/lotus_rear.png"
#define PNG_LOTUS_RIGHT1 "./media/lotus_right_1.png"
#define PNG_LOTUS_RIGHT2 "./media/lotus_right_2.png"

#define PNG_TT_REAR "./media/tt_rear.png"
#define PNG_TT_RIGHT1 "./media/tt_right_1.png"
#define PNG_TT_RIGHT2 "./media/tt_right_2.png"

#define PNG_NSX_REAR "./media/nsx_rear.png"
#define PNG_NSX_RIGHT1 "./media/nsx_right_1.png"
#define PNG_NSX_RIGHT2 "./media/nsx_right_2.png"

#define PNG_TRUENO_REAR "./media/trueno_rear.png"
#define PNG_TRUENO_RIGHT1 "./media/trueno_right_1.png"
#define PNG_TRUENO_RIGHT2 "./media/trueno_right_2.png"

#define PNG_VIPER_REAR "./media/viper_rear.png"
#define PNG_VIPER_RIGHT1 "./media/viper_right_1.png"
#define PNG_VIPER_RIGHT2 "./media/viper_right_2.png"

#define PNG_HART_REAR "./media/hart_rear.png"
#define PNG_HART_RIGHT1 "./media/hart_right_1.png"
#define PNG_HART_RIGHT2 "./media/hart_right_2.png"

#define PNG_DELTA_REAR "./media/delta_rear.png"
#define PNG_DELTA_RIGHT1 "./media/delta_right_1.png"
#define PNG_DELTA_RIGHT2 "./media/delta_right_2.png"

#define PNG_LANCER_REAR "./media/lancer_rear.png"
#define PNG_LANCER_RIGHT1 "./media/lancer_right_1.png"
#define PNG_LANCER_RIGHT2 "./media/lancer_right_2.png"


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

/////////////////////////////////////////////////////////////////
// enums
/////////////////////////////////////////////////////////////////

enum game_status {
	GAME_STATE_UNKNOWN = 0,
	GAME_STATE_TITLE,
	GAME_STATE_CREDIT,
	GAME_STATE_GAME,
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

enum player_sprite_orientation {
 	PLAYER_SPRITE_HARD_LEFT,
 	PLAYER_SPRITE_LIGHT_LEFT,
 	PLAYER_SPRITE_STRAIGHT,
 	PLAYER_SPRITE_LIGHT_RIGHT,
 	PLAYER_SPRITE_HARD_RIGHT
};

enum car_sprite_idx {
 	CAR_SPRITE_REAR,
 	CAR_SPRITE_RIGHT1,
 	CAR_SPRITE_RIGHT2,
 	CAR_SPRITE_LAST
};

enum car_model_type {
 	CAR_MODEL_IMPREZIA = 0,
 	CAR_MODEL_LOTUS,
 	CAR_MODEL_FALCON,
 	CAR_MODEL_TT,
 	CAR_MODEL_TRUENO,
 	CAR_MODEL_VIPER,
 	CAR_MODEL_NSX,
 	CAR_MODEL_HART,
 	CAR_MODEL_DELTA,
 	CAR_MODEL_LANCER,
 	CAR_MODEL_LAST
};

enum ai_car_state {
	AI_CAR_STATE_SPEED_FULL = 0,
	AI_CAR_STATE_SPEED_SLOW,
	AI_CAR_STATE_SPEED_BEHIND_PLAYER,
	AI_CAR_STATE_SWITCHING_LANE_LEFT,
	AI_CAR_STATE_SWITCHING_LANE_RIGHT
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

/*struct car_model_texture{
    // image textures
	struct texture rear;
	struct texture right_1;
	struct texture right_2;
};*/

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
	
	struct texture font_race_anim;
	struct texture font_race_anim_2;
	struct texture font_race_anim_3;
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
	int nb_sprites;
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

// Various constants computed once for all to avoid to recompute them at each frame
struct various_constants {
	float scene_sprite_coef;
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

	// highest point on screen
	int max_y;
	int max_y_idx;

	// highest point on screen
	int max_y_bis;
	// second highest point on screen
	int max_y_bis_idx;

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

	int player_car_x_in_pixels;

	// distance from start line at beginning of the race
	// int player_distance_start_offset;
	// distance travelled by the player
	int player_distance_ran;

	// player position
	int player_place;

	// collision related
	float collision_dst_x;

	// nb of lap of the race
	int nb_lap;
	// nb_lap the player has done
	int player_lap;

    // window
    SDL_Window *window;
    // renderer
    SDL_Renderer *renderer;

    // current status in state machine
    enum game_status status_cur;
    // previous status in state machine
    enum game_status status_prev;
	
	enum player_sprite_orientation car_orientation_cur;
	enum player_sprite_orientation car_orientation_prev;
	int same_car_orientation_in_frame;
//	struct texture *car_player_texture;
//	struct car_model_texture *car_player_textures;

	enum car_sprite_idx car_player_sprite_idx;
	enum car_model_type car_player_model;	
	SDL_RendererFlip car_player_flip;

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

	struct various_constants constants;

	// number of frame spent in STATE_RACE_ANIM_START
	int nb_frame_anim;
	int finish_placed_frame_nb;

	float scale_player_car[CAR_MODEL_LAST];
	float scale_ai_car[CAR_MODEL_LAST];
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
/*static*/ float ai_lane_to_posx(int idx_lane, int nb_lanes);

int ai_car_init(struct game_context *ctx);
int logic_race_ai_cars(struct game_context *ctx);


int logic_get_player_place_nb(struct game_context *ctx);
char* logic_get_player_place_suffix(int pos);
int logic_get_player_lap_nb(struct game_context *ctx);


int load_texture_from_file(struct game_context *ctx,
			   char *path,
			   struct texture *in);

int main_display(struct game_context *ctx);

int main_logic(struct game_context *ctx);

int main_event(struct game_context *ctx);
