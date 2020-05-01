#include "common.h"

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
		printf("[%s] SDL_Init ERROR: %s\n", __func__, SDL_GetError());
		return ret;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("[%s] Warning: Linear texture filtering not enabled!",
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
		printf("[%s] SDL_SetVideoMode ERROR: %s\n",
		       SDL_GetError(),
		       __func__);
		return -EINVAL;
	}

	ctx->renderer =
		SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
	if (!ctx->renderer) {
		printf("[%s] Renderer could not be created! SDL Error: %s\n",
		       __func__,
		       SDL_GetError());
		return -EINVAL;
	}

	SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ctx->renderer, 0x00, 0xFF, 0xFF, 0x00);

	// init PNG loading
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		printf("[%s] SDL_image could not initialize! SDL_image Error: %s\n",
		       __func__,
		       IMG_GetError());
		return -EINVAL;
	}

	// init Fonts management
	if (TTF_Init() < 0) {
		printf("[%s] SDL_ttf could not initialize! SDL_ttf Error: %s\n",
		       __func__,
		       TTF_GetError());
		return -EINVAL;
	}

	// init Music and SFX management
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("[%s] SDL_ttf could not initialize! SDL_Mixer Error: %s\n",
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

static int main_ctx_init(struct game_context *ctx)
{
	ctx->dt = 0;
	ctx->step = 1000 / FPS;
	ctx->nb_segments = 0; // to be set later

	ctx->segments =
		calloc((size_t)ctx->nb_segments, sizeof(struct road_segment));
	if (!ctx->segments) {
		SDL_Log("[%s:%d] calloc failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	// ctx->segment_length = 200;
	ctx->rumble_length = RUMBLE_LENGTH;
	ctx->track_length = 0;
	ctx->lanes = 3;
	ctx->field_of_view = 100;
	// ctx->camera_height = 1000;
	ctx->camera_height = CAMERA_HEIGHT_START;
	ctx->camera_depth = 0;
	ctx->draw_distance = 500;
	ctx->player_x = 0;
	ctx->player_z = 0;
	ctx->fog_density = 5;
	ctx->position = 0;
	ctx->speed = 0;
	ctx->max_speed = 1.f * (2.f * (float)ROAD_SEGMENT_LENGTH) /
			 (float)ctx->step * (30.f / (float)FPS);
	// ctx->accel = ctx->max_speed / 5;
	ctx->accel = ctx->max_speed / 50;

	ctx->max_speed_nitro = ctx->max_speed * 1.33f;
	ctx->accel_nitro = ctx->accel * 2.f;
	ctx->nb_nitro = 3;
	ctx->breaking = ctx->max_speed * -1 / 20;
	// ctx->decel = (ctx->max_speed / 5) * -1;
	ctx->decel = (ctx->max_speed / 50) * -1;
	// ctx->off_road_decel = (ctx->max_speed / 20) * -1;
	ctx->off_road_decel = (ctx->max_speed / 30) * -1;
	// ctx->off_road_limit = (ctx->max_speed / 3);
	ctx->off_road_limit = (ctx->max_speed / 2);
	ctx->centrifugal = 0.3f;

	ctx->car_orientation_cur = PLAYER_SPRITE_STRAIGHT;
	ctx->car_orientation_prev = PLAYER_SPRITE_STRAIGHT;
	ctx->same_car_orientation_in_frame = 0;

	// ctx->car_player_model = CAR_MODEL_NSX;
	// ctx->car_player_model = CAR_MODEL_FALCON;
	// ctx->car_player_model = CAR_MODEL_VIPER;
	ctx->car_player_model = CAR_MODEL_IMPREZIA;
	ctx->car_player_sprite_idx = CAR_SPRITE_REAR;
	ctx->car_player_flip = SDL_FLIP_NONE;

	ctx->status_cur = GAME_STATE_RACE_ANIM_START;
	ctx->status_prev = GAME_STATE_RACE_ANIM_START;
	/*ctx->status_cur = GAME_STATE_RACE;
	ctx->status_prev = GAME_STATE_RACE;*/

	ctx->nb_lap = 3;
	ctx->player_lap = 0;
	ctx->player_place = NB_AI_CARS + 1;

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


	ctx->constants.scene_sprite_coef = (float)SCREEN_WIDTH / 2.f;

	// track info init
	ctx->track.track_selected = TRACK_DIJON;
	ctx->track.lane_type = LANE_TYPE_HALF;
	ctx->track.lane_color = color_lane_yellow;


	// player sprite constant values

	/*ctx->player_sprite_y =
		SCREEN_HEIGHT -
		(int)((float)ctx->gfx
			      .cars[ctx->car_player_model]
				   [ctx->car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->car_player_model]) -
		30; // TODO: Why 30 ??????*/

	ctx->player_sprite_w =
		(int)((float)ctx->gfx
			      .cars[ctx->car_player_model]
				   [ctx->car_player_sprite_idx]
			      .w *
		      ctx->scale_player_car[ctx->car_player_model]);

	ctx->player_sprite_h =
		(int)((float)ctx->gfx
			      .cars[ctx->car_player_model]
				   [ctx->car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->car_player_model]);


	// just draw the player in middle of the screen. It doesn't
	// move, that's
	// the world around it which moves.
	ctx->player_sprite_x = SCREEN_WIDTH / 2 - ctx->player_sprite_w / 2;

	ctx->player_sprite_y =
		SCREEN_HEIGHT -
		(int)((float)ctx->gfx
			      .cars[ctx->car_player_model]
				   [ctx->car_player_sprite_idx]
			      .h *
		      ctx->scale_player_car[ctx->car_player_model]) -
		SCREEN_HEIGHT * 4 / 100;
	/*- 30*/;


	ctx->player_max_x = ctx->player_sprite_x + ctx->player_sprite_w;
	ctx->player_max_y = ctx->player_sprite_y + ctx->player_sprite_h;

	return 0;
};


static int main_destroy(struct game_context *ctx)
{
	// TODO

	// free textures
	// SDL_DestroyTexture(ctx->gfx.t_bg_title.texture);

	// free music
	// Mix_FreeMusic(ctx->sfx.music_title);

	// Free the sound effects
	// Mix_FreeChunk(ctx->sfx.sfx_gameover);

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

int load_texture_from_file(struct game_context *ctx,
			   char *path,
			   struct texture *in)
{
	SDL_Texture *new_texture;

	SDL_Surface *loaded_surface = IMG_Load(path);
	if (!loaded_surface) {
		SDL_Log("[%s] Unable to load image %s! SDL_image Error: %s\n",
			__func__,
			path,
			IMG_GetError());
		return -EINVAL;
	}

	// set color key to cyan
	SDL_SetColorKey(loaded_surface,
			SDL_TRUE,
			SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

	// create texture from surface pixels
	new_texture =
		SDL_CreateTextureFromSurface(ctx->renderer, loaded_surface);
	if (!new_texture) {
		printf("[%s] Unable to create texture from %s! SDL Error: %s\n",
		       __func__,
		       path,
		       SDL_GetError());
		return -EINVAL;
	}

	// get image dimensions
	in->w = loaded_surface->w;
	in->h = loaded_surface->h;

	// discard old surface
	SDL_FreeSurface(loaded_surface);

	in->texture = new_texture;

	return 0;
}

int main()
{
	struct game_context *ctx;

	ctx = calloc(1, sizeof(*ctx));

	// init
	main_init(ctx);

	// load media and stuff
	media_load_resources(ctx);

	main_ctx_init(ctx);

	// main_build_track(ctx);
	track_build(ctx);

	ai_car_init(ctx);

	// game loop
	while (!ctx->exit) {

		// main_build_track(ctx); // TODO: move out of loop !!!!!

		// TODO: MOVE
		float cam_depth = 1.f / tanf((ctx->field_of_view / 2.f) *
					     (float)M_PI / 180.f);
		ctx->camera_depth = (float)cam_depth;
		ctx->player_z =
			(int)((float)ctx->camera_height * ctx->camera_depth);
		/*SDL_Log("[%s] camera_depth: double=%f, float=%f,
		   player_z=%d\n",
			__func__,
			cam_depth,
			ctx->camera_depth,
			ctx->player_z);*/


		// events management
		main_event(ctx);

		// game logic
		main_logic(ctx);

		// display on screen
		main_display(ctx);

		// sleep
		main_sleep(ctx);

		ctx->action = ACTION_NONE;
	}

	// free resources
	main_destroy(ctx);

	return 0;
}
