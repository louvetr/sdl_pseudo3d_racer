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
	int ret;
	// load png
	ret = load_texture_from_file(ctx, PNG_CAR_PLAYER, &ctx->gfx.car_player);
	if (ret < 0) {
		SDL_Log("[%s:%d] Failed to load title PNG!\n",
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
	/*ctx->font = TTF_OpenFont(PATH_FONT, 52);
	if (!ctx->font) {
		printf("[%s] Failed to load font! SDL_ttf Error: %s\n",
		       __func__, TTF_GetError());
		return -EINVAL;
	}*/

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
	ctx->nb_segments = 500; // ???????????????????

	ctx->segments = calloc(ctx->nb_segments, sizeof(struct road_segment));
	if (!ctx->segments) {
		SDL_Log("[%s:%d] calloc failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	ctx->road_width = 2100;
	// ctx->segment_length = 200;
	ctx->rumble_length = RUMBLE_LENGTH;
	ctx->track_length = 0; // null;
	ctx->lanes = 3;
	ctx->field_of_view = 100;
	ctx->camera_height = 1000;
	ctx->camera_depth = 0;
	ctx->draw_distance = 300; // 300 ????
	// ctx->draw_distance = 100; // 300 ????
	// ctx->draw_distance = 300; // 300 ????
	ctx->player_x = 0;
	ctx->player_z = 0;
	ctx->fog_density = 5;
	ctx->position = 0; // TODO: 0 ????
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


static int main_road_add_segment(struct road_segment *segment,
				 int idx,
				 float y,
				 float prev_y,
				 float curve)
// enum road_curve curve)
{
	memset(&segment->p1, 0, sizeof(segment->p1));
	memset(&segment->p2, 0, sizeof(segment->p2));

	segment->p1.world.z = idx * ROAD_SEGMENT_LENGTH;
	segment->p2.world.z = (idx + 1) * ROAD_SEGMENT_LENGTH;
	segment->p1.world.y = prev_y;
	segment->p2.world.y = y;
	segment->curve = curve;


	/*static float prev_curve;
	if (curve != prev_curve)
		SDL_Log("[%s] curve = %f\n", __func__, curve);
	prev_curve = curve;*/

	static float prev_p2_y;
	//if (segment->p2.world.y != prev_p2_y)
		SDL_Log("[%s] p2.w.y = %f\n", __func__, segment->p2.world.y);
	prev_p2_y = segment->p2.world.y;

	/* TODO: use ctx->rumble_length */
	segment->color = (idx / RUMBLE_LENGTH /*ctx->rumble_length*/) % 2
				 ? COLOR_DARK
				 : COLOR_BRIGHT;

	return 0;
}


static int main_road_add_sector(struct road_segment *segments,
				int start_idx,
				int sector_enter_lg,
				int sector_hold_lg,
				int sector_exit_lg,
				int y,
				enum road_curve curve)
{
	int i, idx, nb_segment_added, sector_total_lg;
	float start_y, end_y;
	static int prev_y = 0;
	sector_total_lg = sector_enter_lg + sector_hold_lg + sector_exit_lg;
	idx = start_idx;
	if (idx == 0)
		prev_y = 0;

	// TODO: set prev_y properly !
	start_y = prev_y;
	/*
	toInt:
		function(obj, def)
		{
			if (obj != = null) {
				var x = parseInt(obj, 10);
				if (!isNaN(x))
					return x;
			}
			return Util.toInt(def, 0);
		}
	*/

	end_y = start_y + (float) (y * ROAD_SEGMENT_LENGTH);
	
	SDL_Log("[%s] start_y = %f, end_y = %f\n", __func__, start_y, end_y);

	for (i = 0; i < sector_enter_lg; i++) {
		// main_road_add_segment(&segments[idx], idx, y, prev_y, curve);
		main_road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(start_y,
					   end_y,
					   (float)i / (float)sector_total_lg), //TODO: BUG
			prev_y,
			inline_curve_inout(
				0, curve, (float)i / (float)sector_enter_lg));
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	SDL_Log("[%s] ---------------------------------------\n", __func__);

	for (i = 0; i < sector_hold_lg; i++) {
		// idx = start_idx + nb_segment_added + i;
		main_road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(start_y,
					   end_y,
					   (float)(i + sector_enter_lg) /
						   (float)sector_total_lg),
			prev_y,
			curve);
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	SDL_Log("[%s] ---------------------------------------\n", __func__);

	for (i = 0; i < sector_exit_lg; i++) {
		// idx = start_idx + nb_segment_added + i;
		// main_road_add_segment(&segments[idx], idx, y, prev_y, curve);
		main_road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(
				start_y,
				end_y,
				(float)(i + sector_enter_lg + sector_hold_lg) /
					(float)sector_total_lg),
			prev_y,
			inline_curve_inout(
				curve, 0, (float)i / (float)sector_exit_lg));
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	return (idx - start_idx);
}


// TODO: use realloc at each sector addition instead counting total nb sectors
// in advance

static int main_build_track(struct game_context *ctx)
{
	int nb_segments_added = 0;

	ctx->nb_segments = 1350;
	//ctx->nb_segments = 1050;
	//ctx->nb_segments = 300;

	ctx->segments = calloc(ctx->nb_segments, sizeof(*ctx->segments));
	if (!ctx->segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}

	/*
	for (int i = 0; i < ctx->nb_segments; i++) {

		memset(&ctx->segments[i].p1, 0, sizeof(ctx->segments[i].p1));
		memset(&ctx->segments[i].p2, 0, sizeof(ctx->segments[i].p2));

		ctx->segments[i].p1.world.z = i * ROAD_SEGMENT_LENGTH;
		ctx->segments[i].p2.world.z = (i + 1) * ROAD_SEGMENT_LENGTH;

		ctx->segments[i].curve = CURVE_NONE;

		ctx->segments[i].color = (i / ctx->rumble_length) % 2
						 ? COLOR_DARK
						 : COLOR_BRIGHT;
	}
	*/

/*
	// 75 straight --- 75
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  //HILL_UP_LOW,
						  HILL_NONE,
						  CURVE_NONE);

	// 150 left --- 225
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_LEFT_EASY);

	// 75 straight --- 300
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_MEDIUM,
						  CURVE_NONE);

	// 150 right --- 450
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	// 75 straight --- 525
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_HIGH,
						  CURVE_NONE);

	// 300 left --- 825
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_LEFT_EASY);


	// 75 straight --- 900
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_HIGH,
						  CURVE_NONE);

	// 150 right --- 1050
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_MEDIUM,
						  CURVE_RIGHT_HARD);
*/
	// 150 straight --- 1050
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	// 150 straight --- 1050
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);

	// 150 straight --- 150
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_LOW,
						  CURVE_NONE);

	// 150 straight --- 300
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_LOW,
						  CURVE_NONE);

	// 150 straight --- 450
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_MEDIUM,
						  CURVE_NONE);

	// 150 straight --- 600
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_NONE);

	// 150 straight --- 750
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_HIGH,
						  CURVE_NONE);

	// 150 straight --- 900
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_HIGH,
						  CURVE_NONE);

	// 150 straight --- 1050
	nb_segments_added += main_road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);



	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

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

	main_build_track(ctx);

	// game loop
	while (!ctx->exit) {

		// main_build_track(ctx); // TODO: move out of loop !!!!!

		// TODO: MOVE
		double cam_depth =
			1. / tan((double)(ctx->field_of_view / 2) * M_PI / 180);
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