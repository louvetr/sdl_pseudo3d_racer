#include "main.h"

const Uint32 SCREEN_TICKS_PER_FRAME = MS_PER_SEC / FPS;


// TODO: move in a separtate file
struct color_desc color_lane_white = {
	.r = 255,
	.g = 255,
	.b = 255,
	.a = 255,
};

struct color_desc color_lane_yellow = {
	.r = 0xFC,
	.g = 0xE2,
	.b = 0x05,
	.a = 255,
};


/////////////////////////////////////////////////////////////////
// static function definitions
////////////////////////////////////////////////////////////////

static int main_init(struct game_context *ctx)
{
	int ret;

	srand((unsigned int)time(0));

	// init SDL
	ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		SDL_Log("[%s] SDL_Init ERROR: %s\n", __func__, SDL_GetError());
		return ret;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		SDL_Log("[%s] Warning: Linear texture filtering not enabled!",
			__func__);
	}

	// create g_window
	ctx->window = SDL_CreateWindow("SDL_pseudo3Dracer",
				       SDL_WINDOWPOS_UNDEFINED,
				       SDL_WINDOWPOS_UNDEFINED,
				       SCREEN_WIDTH,
				       SCREEN_HEIGHT,
				       SDL_WINDOW_SHOWN);
	if (!ctx->window) {
		SDL_Log("[%s] SDL_SetVideoMode ERROR: %s\n",
			SDL_GetError(),
			__func__);
		return -EINVAL;
	}

	ctx->renderer =
		SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
	if (!ctx->renderer) {
		SDL_Log("[%s] Renderer could not be created! SDL Error: %s\n",
			__func__,
			SDL_GetError());
		return -EINVAL;
	}

	SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ctx->renderer, 0x00, 0xFF, 0xFF, 0x00);

	// init PNG loading
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		SDL_Log("[%s] SDL_image could not initialize! SDL_image Error: %s\n",
			__func__,
			IMG_GetError());
		return -EINVAL;
	}

	// init Fonts management
	if (TTF_Init() < 0) {
		SDL_Log("[%s] SDL_ttf could not initialize! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	// init Music and SFX management
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("[%s] SDL_ttf could not initialize! SDL_Mixer Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	ctx->start_ticks = SDL_GetTicks();

	return 0;
}


static int main_sleep(struct game_context *ctx)
{
	Uint32 frame_ticks = SDL_GetTicks() - ctx->start_ticks;
	if (frame_ticks < SCREEN_TICKS_PER_FRAME)
		SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);

	ctx->start_ticks = SDL_GetTicks();

	return 0;
}


int main_ctx_init_race(struct game_context *ctx)
{
	ctx->dt = 0;
	ctx->step = 1000 / FPS;
	ctx->track.nb_segments = 0; // to be set later

	ctx->track.segments = calloc((size_t)ctx->track.nb_segments,
				     sizeof(struct road_segment));
	if (!ctx->track.segments) {
		SDL_Log("[%s:%d] calloc failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	// ctx->segment_length = 200;
	ctx->track.rumble_length = RUMBLE_LENGTH;
	ctx->track.track_length = 0;
	ctx->track.lanes = 3;
	ctx->race.field_of_view = 100;


	float cam_depth = 1.f / tanf((ctx->race.field_of_view / 2.f) *
				     (float)M_PI / 180.f);
	ctx->race.camera_depth = (float)cam_depth;
	ctx->pcar.player_z =
		(int)((float)ctx->race.camera_height * ctx->race.camera_depth);


	ctx->race.nb_frame_anim = 0;
	// ctx->race.camera_height = 1000;
	ctx->race.camera_height = CAMERA_HEIGHT_START;
	ctx->race.camera_depth = 0;
	ctx->race.draw_distance = 500;
	ctx->pcar.player_x = 0;
	ctx->pcar.player_z = 0;
	ctx->pcar.position = 0;
	ctx->pcar.speed = 0;
	ctx->pcar.max_speed = 1.f * (2.f * (float)ROAD_SEGMENT_LENGTH) /
			      (float)ctx->step * (30.f / (float)FPS);
	// ctx->pcar.accel = ctx->pcar.max_speed / 5;
	ctx->pcar.accel = ctx->pcar.max_speed / 50;

	ctx->pcar.max_speed_nitro = ctx->pcar.max_speed * 1.33f;
	ctx->pcar.accel_nitro = ctx->pcar.accel * 2.f;
	ctx->pcar.nb_nitro = 3;
	ctx->pcar.breaking = ctx->pcar.max_speed * -1 / 20;
	// ctx->pcar.decel = (ctx->pcar.max_speed / 5) * -1;
	ctx->pcar.decel = (ctx->pcar.max_speed / 50) * -1;
	// ctx->pcar.off_road_decel = (ctx->pcar.max_speed / 20) * -1;
	ctx->pcar.off_road_decel = (ctx->pcar.max_speed / 30) * -1;
	// ctx->pcar.off_road_limit = (ctx->pcar.max_speed / 3);
	ctx->pcar.off_road_limit = (ctx->pcar.max_speed / 2);
	ctx->pcar.centrifugal = 0.3f;

	ctx->pcar.car_orientation_cur = PLAYER_SPRITE_STRAIGHT;
	ctx->pcar.car_orientation_prev = PLAYER_SPRITE_STRAIGHT;
	ctx->pcar.same_car_orientation_in_frame = 0;

	// ctx->pcar.car_player_model = CAR_MODEL_NSX;
	// ctx->pcar.car_player_model = CAR_MODEL_FALCON;
	// ctx->pcar.car_player_model = CAR_MODEL_VIPER;
	// ctx->pcar.car_player_model = CAR_MODEL_IMPREZIA;
	// ctx->pcar.car_player_model = CAR_MODEL_LANCER;
	// ctx->pcar.car_player_model = CAR_MODEL_DELTA;
	ctx->pcar.car_player_sprite_idx = CAR_SPRITE_REAR;
	ctx->pcar.car_player_flip = SDL_FLIP_NONE;

	ctx->status_cur = GAME_STATE_RACE_ANIM_START;
	ctx->status_prev = GAME_STATE_UNKNOWN;
	/*ctx->status_cur = GAME_STATE_RACE;
	ctx->status_prev = GAME_STATE_RACE;*/

	ctx->race.nb_lap_logic = 0;
	ctx->race.nb_lap = 3;
	// ctx->race.nb_lap = 1;
	ctx->race.player_lap = 0;
	ctx->pcar.player_place = NB_AI_CARS + 1;

	ctx->scale_player_car[CAR_MODEL_IMPREZIA] = PLAYER_CAR_SCALE_IMPREZIA;
	ctx->scale_player_car[CAR_MODEL_LOTUS] = PLAYER_CAR_SCALE_LOTUS;
	ctx->scale_player_car[CAR_MODEL_FALCON] = PLAYER_CAR_SCALE_FALCON;
	ctx->scale_player_car[CAR_MODEL_TT] = PLAYER_CAR_SCALE_TT;
	ctx->scale_player_car[CAR_MODEL_TRUENO] = PLAYER_CAR_SCALE_TRUENO;
	ctx->scale_player_car[CAR_MODEL_NSX] = PLAYER_CAR_SCALE_NSX;
	ctx->scale_player_car[CAR_MODEL_VIPER] = PLAYER_CAR_SCALE_VIPER;
	ctx->scale_player_car[CAR_MODEL_HART] = PLAYER_CAR_SCALE_HART;
	ctx->scale_player_car[CAR_MODEL_DELTA] = PLAYER_CAR_SCALE_DELTA;
	ctx->scale_player_car[CAR_MODEL_LANCER] = PLAYER_CAR_SCALE_LANCER;

	ctx->scale_ai_car[CAR_MODEL_IMPREZIA] = AI_CAR_SCALE_IMPREZIA;
	ctx->scale_ai_car[CAR_MODEL_LOTUS] = AI_CAR_SCALE_LOTUS;
	ctx->scale_ai_car[CAR_MODEL_FALCON] = AI_CAR_SCALE_FALCON;
	ctx->scale_ai_car[CAR_MODEL_TT] = AI_CAR_SCALE_TT;
	ctx->scale_ai_car[CAR_MODEL_TRUENO] = AI_CAR_SCALE_TRUENO;
	ctx->scale_ai_car[CAR_MODEL_NSX] = AI_CAR_SCALE_NSX;
	ctx->scale_ai_car[CAR_MODEL_VIPER] = AI_CAR_SCALE_VIPER;
	ctx->scale_ai_car[CAR_MODEL_HART] = AI_CAR_SCALE_HART;
	ctx->scale_ai_car[CAR_MODEL_DELTA] = AI_CAR_SCALE_DELTA;
	ctx->scale_ai_car[CAR_MODEL_LANCER] = AI_CAR_SCALE_LANCER;


	ctx->scene_sprite_coef = (float)SCREEN_WIDTH / 2.f;

	// track info init
	//ctx->track.track_selected = TRACK_DIJON;
	ctx->track.lane_type = LANE_TYPE_HALF;
	ctx->track.lane_color = color_lane_yellow;


	// player sprite constant values

	/*ctx->pcar.player_sprite_y =
		SCREEN_HEIGHT -
		(int)((float)ctx->gfx
			      .cars[ctx->pcar.car_player_model]
				   [ctx->pcar.car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->pcar.car_player_model]) -
		30; // TODO: Why 30 ??????*/

	ctx->pcar.player_sprite_w =
		(int)((float)ctx->gfx
			      .cars[ctx->pcar.car_player_model]
				   [ctx->pcar.car_player_sprite_idx]
			      .w *
		      ctx->scale_player_car[ctx->pcar.car_player_model]);

	ctx->pcar.player_sprite_h =
		(int)((float)ctx->gfx
			      .cars[ctx->pcar.car_player_model]
				   [ctx->pcar.car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->pcar.car_player_model]);


	// just draw the player in middle of the screen. It doesn't
	// move, that's
	// the world around it which moves.
	ctx->pcar.player_sprite_x =
		SCREEN_WIDTH / 2 - ctx->pcar.player_sprite_w / 2;

	ctx->pcar.player_sprite_y =
		SCREEN_HEIGHT -
		(int)((float)ctx->gfx
			      .cars[ctx->pcar.car_player_model]
				   [ctx->pcar.car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->pcar.car_player_model]) -
		SCREEN_HEIGHT * 4 / 100;
	/*- 30*/;


	ctx->pcar.player_max_x =
		ctx->pcar.player_sprite_x + ctx->pcar.player_sprite_w;
	ctx->pcar.player_max_y =
		ctx->pcar.player_sprite_y + ctx->pcar.player_sprite_h;

	return 0;
};

int main_ctx_init_menu_select_car(struct game_context *ctx)
{
	ctx->status_cur = GAME_STATE_MENU_SELECT_CAR;
	ctx->status_prev = GAME_STATE_UNKNOWN;

	return 0;
}

int main_ctx_init_menu_select_track(struct game_context *ctx)
{
	ctx->status_cur = GAME_STATE_MENU_SELECT_TRACK;
	ctx->status_prev = GAME_STATE_UNKNOWN;

	return 0;
}


int main_ctx_init_menu_main(struct game_context *ctx)
{
	ctx->status_cur = GAME_STATE_MENU_MAIN;

	if (ctx->status_prev != GAME_STATE_MENU_SELECT_CAR &&
	    ctx->status_prev != GAME_STATE_MENU_SELECT_TRACK)
		Mix_PlayMusic(ctx->sound.music.menu, -1);

	return 0;
}

static int main_destroy(struct game_context *ctx)
{
	// TODO

	// free textures
	// SDL_DestroyTexture(ctx->gfx.t_bg_title.texture);

	// free music
	// Mix_FreeMusic(ctx->sound.sfx.music_title);

	// Free the sound effects
	// Mix_FreeChunk(ctx->sound.sfx.sfx_gameover);

	// Destroy window
	// SDL_DestroyRenderer(ctx->gfx.renderer);

	// Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	free(ctx);

	return 0;
}


/////////////////////////////////////////////////////////////////
// Main function
////////////////////////////////////////////////////////////////

int main()
{
	struct game_context *ctx;

	ctx = calloc(1, sizeof(*ctx));

	// init
	main_init(ctx);

	// init Music and SFX management
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("SDL_ttf could not initialize! SDL_Mixer Error: %s\n",
			TTF_GetError());
		return -EINVAL;
	}

	Mix_VolumeMusic(MAX_VOLUME);


	// load media and stuff
	// gfx_load_resources_race(ctx);
	// sound_load_resources(ctx);

	// main_ctx_init(ctx);
	// main_ctx_init_race(ctx);

	// gfx_load_resources_menu_select_car(ctx);
	// main_ctx_init_menu_select_car(ctx);

	/*gfx_load_resources_menu_select_track(ctx);
	main_ctx_init_menu_select_track(ctx);*/

	gfx_load_resources_menu_main(ctx);
	sound_load_resources_menu(ctx);
	main_ctx_init_menu_main(ctx);

	// main_build_track(ctx);
	// track_build(ctx);

	// ai_car_init(ctx);

	// game loop
	while (!ctx->exit) {

		// main_build_track(ctx); // TODO: move out of loop !!!!!

		// TODO: MOVE

		float cam_depth = 1.f / tanf((ctx->race.field_of_view / 2.f) *
					     (float)M_PI / 180.f);
		ctx->race.camera_depth = (float)cam_depth;
		ctx->pcar.player_z = (int)((float)ctx->race.camera_height *
					   ctx->race.camera_depth);

		/*SDL_Log("[%s] camera_depth: double=%f, float=%f,
		   player_z=%d\n",
			__func__,
			cam_depth,
			ctx->race.camera_depth,
			ctx->pcar.player_z);*/


		// events management
		main_event(ctx);

		// game logic
		main_logic(ctx);

		// display on screen
		main_display(ctx);

		// music and sfx
		main_sound(ctx);

		// sleep
		main_sleep(ctx);

		ctx->status_prev = ctx->status_cur;
		ctx->action = ACTION_NONE;
		ctx->keys.accel_prev = ctx->keys.accel;
		ctx->keys.nitro_prev = ctx->keys.nitro;
		ctx->sound.drift_prev = ctx->sound.drift;
	}

	// free resources
	main_destroy(ctx);

	return 0;
}
