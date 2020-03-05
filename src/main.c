#include "common.h"

const int SCREEN_TICKS_PER_FRAME = MS_PER_SEC / FPS;

/////////////////////////////////////////////////////////////////
// static function definitions
////////////////////////////////////////////////////////////////

static int main_init(struct game_context *ctx)
{
	int ret;

	srand(time(0));

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

	// set state to title screen
	ctx->status_cur = GAME_STATE_RACE;
	ctx->status_prev = GAME_STATE_UNKNOWN;

	ctx->start_ticks = SDL_GetTicks();

	return 0;
}

static int main_load_media(struct game_context *ctx)
{
	// TODO, use macro for texture loading

	int ret;
	// load png
	ret = load_texture_from_file(ctx, PNG_CAR_PLAYER, &ctx->gfx.car_player);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}


	ret = load_texture_from_file(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_mountains);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_SCENE_TREE_OAK, &ctx->gfx.scene_tree_oak);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_SCENE_TREE_WILLOW, &ctx->gfx.scene_tree_willow);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_SCENE_TREE_PINE, &ctx->gfx.scene_tree_pine);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_SCENE_CABIN, &ctx->gfx.scene_cabin);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}

	ret = load_texture_from_file(ctx, PNG_SCENE_FENCE, &ctx->gfx.scene_fence);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}
	ret = load_texture_from_file(ctx, PNG_SCENE_GRASS, &ctx->gfx.scene_grass);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}
	ret = load_texture_from_file(ctx, PNG_SCENE_WINDMILL, &ctx->gfx.scene_windmill);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}
	ret = load_texture_from_file(ctx, PNG_SCENE_BARN, &ctx->gfx.scene_barn);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}
	ret = load_texture_from_file(ctx, PNG_SCENE_BUSH, &ctx->gfx.scene_bush);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load PNG!\n",
			__func__,
			__LINE__);
		return ret;
	}
	/*ret = load_texture_from_file(ctx, PATH_BG_GAME, &ctx->gfx.t_bg_game);
	if (ret < 0) {
		printf("[%s] Failed to load game PNG!\n", __func__);
		return ret;
	}*/

	// load music
	/*ctx->sfx.music_game = Mix_LoadMUS(PATH_MUSIC_GAME);
	if (!ctx->sfx.music_game) {
		printf("[%s] Failed to load game music\n", __func__);
		return -EINVAL;
	}
	ctx->sfx.music_title = Mix_LoadMUS(PATH_MUSIC_TITLE);
	if (!ctx->sfx.music_game) {
		printf("[%s] Failed to load title music\n", __func__);
		return -EINVAL;
	}

	//Load sound effects
	ctx->sfx.sfx_menu_move = Mix_LoadWAV(PATH_SFX_MENU_MOVE);
	if (!ctx->sfx.sfx_menu_move) {
		printf("Failed to load sfx menu move! SDL_mixer Error: %s\n",
		       Mix_GetError());
		return -EINVAL;
	}*/

	// Open the font
	ctx->sc_font_big = TTF_OpenFont(SOFACHROME_FONT, 72);
	if (!ctx->sc_font_big) {
		printf("[%s] Failed to load font! SDL_ttf Error: %s\n",
		       __func__, TTF_GetError());
		return -EINVAL;
	}
	
	ctx->sc_font_medium = TTF_OpenFont(SOFACHROME_FONT, 36);
	if (!ctx->sc_font_medium) {
		printf("[%s] Failed to load font! SDL_ttf Error: %s\n",
		       __func__, TTF_GetError());
		return -EINVAL;
	}

	SDL_Log("media loaded\n");

	return 0;
}

static int main_sleep(struct game_context *ctx)
{
	int frame_ticks = SDL_GetTicks() - ctx->start_ticks;
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

	ctx->segments = calloc(ctx->nb_segments, sizeof(struct road_segment));
	if (!ctx->segments) {
		SDL_Log("[%s:%d] calloc failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	ctx->road_width = 2100;
	// ctx->segment_length = 200;
	ctx->rumble_length = RUMBLE_LENGTH;
	ctx->track_length = 0;
	ctx->lanes = 3;
	ctx->field_of_view = 100;
	ctx->camera_height = 1000;
	ctx->camera_depth = 0;
	ctx->draw_distance = 500;
	ctx->player_x = 0;
	ctx->player_z = 0;
	ctx->fog_density = 5;
	ctx->position = 0;
	ctx->speed = 0;
	ctx->max_speed = (2 * ROAD_SEGMENT_LENGTH) / ctx->step;
	// ctx->accel = ctx->max_speed / 5;
	ctx->accel = ctx->max_speed / 50;
	ctx->breaking = ctx->max_speed * -1;
	// ctx->decel = (ctx->max_speed / 5) * -1;
	ctx->decel = (ctx->max_speed / 50) * -1;
	ctx->off_road_decel = (ctx->max_speed / 20) * -1;
	ctx->off_road_limit = (ctx->max_speed / 3);
	ctx->centrifugal = 0.3;

	ctx->status_cur = GAME_STATE_GAME;
	ctx->status_prev = GAME_STATE_GAME;

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
	main_load_media(ctx);

	main_ctx_init(ctx);

	//main_build_track(ctx);
	track_build(ctx);

	// game loop
	while (!ctx->exit) {

		// main_build_track(ctx); // TODO: move out of loop !!!!!

		// TODO: MOVE
		float cam_depth =
			1. / tanf((ctx->field_of_view / 2.f) * M_PI / 180.f);
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