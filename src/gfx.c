
#include "main.h"

//#define SOFACHROME_FONT "./media/font/GeneraleStation-Regular.otf"
//#define SOFACHROME_FONT "./media/font/01 DigitMono.ttf"

//#define PNG_CAR_PLAYER "./media/car_rear_01.png"
#define PNG_IMPREZIA_SIDE "./media/cars/imprezia_side.png"
#define PNG_IMPREZIA_REAR "./media/cars/imprezia_rear.png"
#define PNG_IMPREZIA_RIGHT1 "./media/cars/imprezia_right_1.png"
#define PNG_IMPREZIA_RIGHT2 "./media/cars/imprezia_right_2.png"

#define PNG_FALCON_SIDE "./media/cars/falcon_side.png"
#define PNG_FALCON_REAR "./media/cars/falcon_rear.png"
#define PNG_FALCON_RIGHT1 "./media/cars/falcon_right_1.png"
#define PNG_FALCON_RIGHT2 "./media/cars/falcon_right_2.png"

#define PNG_LOTUS_SIDE "./media/cars/lotus_side.png"
#define PNG_LOTUS_REAR "./media/cars/lotus_rear.png"
#define PNG_LOTUS_RIGHT1 "./media/cars/lotus_right_1.png"
#define PNG_LOTUS_RIGHT2 "./media/cars/lotus_right_2.png"

#define PNG_TT_SIDE "./media/cars/tt_side.png"
#define PNG_TT_REAR "./media/cars/tt_rear.png"
#define PNG_TT_RIGHT1 "./media/cars/tt_right_1.png"
#define PNG_TT_RIGHT2 "./media/cars/tt_right_2.png"

#define PNG_NSX_SIDE "./media/cars/nsx_side.png"
#define PNG_NSX_REAR "./media/cars/nsx_rear.png"
#define PNG_NSX_RIGHT1 "./media/cars/nsx_right_1.png"
#define PNG_NSX_RIGHT2 "./media/cars/nsx_right_2.png"

#define PNG_TRUENO_SIDE "./media/cars/trueno_side.png"
#define PNG_TRUENO_REAR "./media/cars/trueno_rear.png"
#define PNG_TRUENO_RIGHT1 "./media/cars/trueno_right_1.png"
#define PNG_TRUENO_RIGHT2 "./media/cars/trueno_right_2.png"

#define PNG_VIPER_SIDE "./media/cars/viper_side.png"
#define PNG_VIPER_REAR "./media/cars/viper_rear.png"
#define PNG_VIPER_RIGHT1 "./media/cars/viper_right_1.png"
#define PNG_VIPER_RIGHT2 "./media/cars/viper_right_2.png"

#define PNG_HART_SIDE "./media/cars/hart_side.png"
#define PNG_HART_REAR "./media/cars/hart_rear.png"
#define PNG_HART_RIGHT1 "./media/cars/hart_right_1.png"
#define PNG_HART_RIGHT2 "./media/cars/hart_right_2.png"

#define PNG_DELTA_SIDE "./media/cars/delta_side.png"
#define PNG_DELTA_REAR "./media/cars/delta_rear.png"
#define PNG_DELTA_RIGHT1 "./media/cars/delta_right_1.png"
#define PNG_DELTA_RIGHT2 "./media/cars/delta_right_2.png"

#define PNG_LANCER_SIDE "./media/cars/lancer_side.png"
#define PNG_LANCER_REAR "./media/cars/lancer_rear.png"
#define PNG_LANCER_RIGHT1 "./media/cars/lancer_right_1.png"
#define PNG_LANCER_RIGHT2 "./media/cars/lancer_right_2.png"


#define PNG_BG_MOUNTAINS "./media/background/bg_mountains.png"
#define PNG_BG_SKY_NEAR "./media/background/bg_clouds_near.png"
#define PNG_BG_SKY_FAR "./media/background/bg_clouds_far.png"

#define PNG_SCENE_START_LANE "./media/scene/scene_start_lane_01.png"
#define PNG_SCENE_TREE_OAK "./media/scene/scene_tree_oak.png"
#define PNG_SCENE_TREE_WILLOW "./media/scene/scene_tree_willow.png"
#define PNG_SCENE_TREE_PINE "./media/scene/scene_tree_pine.png"
#define PNG_SCENE_CABIN "./media/scene/scene_cabin.png"
#define PNG_SCENE_FENCE "./media/scene/scene_fence.png"
#define PNG_SCENE_GRASS "./media/scene/scene_grass.png"
#define PNG_SCENE_WINDMILL "./media/scene/scene_windmill.png"
#define PNG_SCENE_BARN "./media/scene/scene_barn.png"
#define PNG_SCENE_WELL "./media/scene/scene_well.png"

#define PNG_SCENE_BUSH_01 "./media/scene/scene_bush_01.png"
#define PNG_SCENE_BUSH_02 "./media/scene/scene_bush_02.png"
#define PNG_SCENE_BUSH_03 "./media/scene/scene_bush_03.png"
#define PNG_SCENE_BUSH_04 "./media/scene/scene_bush_04.png"
#define PNG_SCENE_BUSH_05 "./media/scene/scene_bush_05.png"
#define PNG_SCENE_BUSH_06 "./media/scene/scene_bush_06.png"
#define PNG_SCENE_BUSH_FLOWER "./media/scene/scene_bush_flower.png"

#define PNG_SMOKE_00 "./media/particles/whitePuff00.png"
#define PNG_SMOKE_01 "./media/particles/whitePuff01.png"
#define PNG_SMOKE_02 "./media/particles/whitePuff02.png"
#define PNG_SMOKE_03 "./media/particles/whitePuff03.png"
#define PNG_SMOKE_04 "./media/particles/whitePuff04.png"
#define PNG_SMOKE_05 "./media/particles/whitePuff05.png"
#define PNG_SMOKE_06 "./media/particles/whitePuff24.png"

#define PNG_NITRO_00 "./media/particles/explosion00.png"
#define PNG_NITRO_01 "./media/particles/explosion01.png"
#define PNG_NITRO_02 "./media/particles/explosion02.png"
#define PNG_NITRO_03 "./media/particles/explosion06.png"
#define PNG_NITRO_04 "./media/particles/explosion07.png"


static int
load_texture_from_file(struct game_context *ctx, char *path, struct texture *in)
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
		SDL_Log("[%s] Unable to create texture from %s! SDL Error: %s\n",
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


static int
gfx_load_texture(struct game_context *ctx, char *path, struct texture *t)
{
	int ret = 0;
	ret = load_texture_from_file(ctx, path, t);
	if (ret < 0)
		SDL_Log("[%s:%d] Failed to load PNG!\n", __func__, __LINE__);
	return ret;
}


static int gfx_load_cars_sprites_one_model(struct game_context *ctx,
					   enum car_model_type idx,
					   char *rear,
					   char *right1,
					   char *right2)
{
	gfx_load_texture(ctx, rear, &ctx->gfx.cars[idx][CAR_SPRITE_REAR]);
	gfx_load_texture(ctx, right1, &ctx->gfx.cars[idx][CAR_SPRITE_RIGHT1]);
	gfx_load_texture(ctx, right2, &ctx->gfx.cars[idx][CAR_SPRITE_RIGHT2]);

	return 0;
}

static int gfx_load_cars_sprites(struct game_context *ctx)
{
	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_IMPREZIA,
					PNG_IMPREZIA_REAR,
					PNG_IMPREZIA_RIGHT1,
					PNG_IMPREZIA_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_LOTUS,
					PNG_LOTUS_REAR,
					PNG_LOTUS_RIGHT1,
					PNG_LOTUS_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_FALCON,
					PNG_FALCON_REAR,
					PNG_FALCON_RIGHT1,
					PNG_FALCON_RIGHT2);

	gfx_load_cars_sprites_one_model(
		ctx, CAR_MODEL_TT, PNG_TT_REAR, PNG_TT_RIGHT1, PNG_TT_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_TRUENO,
					PNG_TRUENO_REAR,
					PNG_TRUENO_RIGHT1,
					PNG_TRUENO_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_NSX,
					PNG_NSX_REAR,
					PNG_NSX_RIGHT1,
					PNG_NSX_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_VIPER,
					PNG_VIPER_REAR,
					PNG_VIPER_RIGHT1,
					PNG_VIPER_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_HART,
					PNG_HART_REAR,
					PNG_HART_RIGHT1,
					PNG_HART_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_DELTA,
					PNG_DELTA_REAR,
					PNG_DELTA_RIGHT1,
					PNG_DELTA_RIGHT2);

	gfx_load_cars_sprites_one_model(ctx,
					CAR_MODEL_LANCER,
					PNG_LANCER_REAR,
					PNG_LANCER_RIGHT1,
					PNG_LANCER_RIGHT2);

	return 0;
}


static int gfx_load_background(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_mountains);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	return 0;
}


static int gfx_load_scene_sprites(struct game_context *ctx)
{
	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_OAK, &ctx->gfx.scene_tree_oak);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_WILLOW, &ctx->gfx.scene_tree_willow);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_PINE, &ctx->gfx.scene_tree_pine);
	load_texture_from_file(ctx, PNG_SCENE_WELL, &ctx->gfx.scene_well);
	load_texture_from_file(ctx, PNG_SCENE_FENCE, &ctx->gfx.scene_fence);
	load_texture_from_file(ctx, PNG_SCENE_GRASS, &ctx->gfx.scene_grass);
	load_texture_from_file(
		ctx, PNG_SCENE_WINDMILL, &ctx->gfx.scene_windmill);
	load_texture_from_file(ctx, PNG_SCENE_BARN, &ctx->gfx.scene_barn);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_01, &ctx->gfx.scene_bushes[0]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_02, &ctx->gfx.scene_bushes[2]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_03, &ctx->gfx.scene_bushes[3]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_04, &ctx->gfx.scene_bushes[4]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_05, &ctx->gfx.scene_bushes[5]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_06, &ctx->gfx.scene_bushes[6]);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_FLOWER, &ctx->gfx.scene_bush_flower);

	return 0;
}

static int gfx_load_font(struct game_context *ctx)
{
	// Open the font
	ctx->sc_font_big = TTF_OpenFont(SOFACHROME_FONT, 72);
	if (!ctx->sc_font_big) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	ctx->sc_font_medium = TTF_OpenFont(SOFACHROME_FONT, 36);
	if (!ctx->sc_font_medium) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	return 0;
}


static int gfx_load_cars_side(struct game_context *ctx)
{
	gfx_load_texture(ctx,
			 PNG_IMPREZIA_SIDE,
			 &ctx->gfx.cars_side[CAR_MODEL_IMPREZIA]);
	gfx_load_texture(
		ctx, PNG_DELTA_SIDE, &ctx->gfx.cars_side[CAR_MODEL_DELTA]);
	gfx_load_texture(
		ctx, PNG_TRUENO_SIDE, &ctx->gfx.cars_side[CAR_MODEL_TRUENO]);
	gfx_load_texture(
		ctx, PNG_FALCON_SIDE, &ctx->gfx.cars_side[CAR_MODEL_FALCON]);
	gfx_load_texture(
		ctx, PNG_HART_SIDE, &ctx->gfx.cars_side[CAR_MODEL_HART]);
	gfx_load_texture(ctx, PNG_NSX_SIDE, &ctx->gfx.cars_side[CAR_MODEL_NSX]);
	gfx_load_texture(
		ctx, PNG_VIPER_SIDE, &ctx->gfx.cars_side[CAR_MODEL_VIPER]);
	gfx_load_texture(
		ctx, PNG_LANCER_SIDE, &ctx->gfx.cars_side[CAR_MODEL_LANCER]);
	gfx_load_texture(
		ctx, PNG_LOTUS_SIDE, &ctx->gfx.cars_side[CAR_MODEL_LOTUS]);
	gfx_load_texture(ctx, PNG_TT_SIDE, &ctx->gfx.cars_side[CAR_MODEL_TT]);

	return 0;
}

static int gfx_load_particles(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_SMOKE_00, &ctx->gfx.t_smoke[0]);
	gfx_load_texture(ctx, PNG_SMOKE_01, &ctx->gfx.t_smoke[1]);
	gfx_load_texture(ctx, PNG_SMOKE_02, &ctx->gfx.t_smoke[2]);
	gfx_load_texture(ctx, PNG_SMOKE_03, &ctx->gfx.t_smoke[3]);
	gfx_load_texture(ctx, PNG_SMOKE_04, &ctx->gfx.t_smoke[4]);
	gfx_load_texture(ctx, PNG_SMOKE_05, &ctx->gfx.t_smoke[5]);
	gfx_load_texture(ctx, PNG_SMOKE_06, &ctx->gfx.t_smoke[6]);
	gfx_load_texture(ctx, PNG_NITRO_00, &ctx->gfx.t_nitro[0]);
	gfx_load_texture(ctx, PNG_NITRO_01, &ctx->gfx.t_nitro[1]);
	gfx_load_texture(ctx, PNG_NITRO_02, &ctx->gfx.t_nitro[2]);
	gfx_load_texture(ctx, PNG_NITRO_03, &ctx->gfx.t_nitro[3]);
	gfx_load_texture(ctx, PNG_NITRO_04, &ctx->gfx.t_nitro[4]);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// public function
/////////////////////////////////////////////////////////////////////////////////////

int gfx_load_resources_menu_car_select(struct game_context *ctx)
{

	gfx_load_cars_side(ctx);

	return 0;
}

int gfx_load_resources_race(struct game_context *ctx)
{
	// TODO, use macro for texture loading

	int ret;

	ret = gfx_load_cars_sprites(ctx);
	if (ret < 0) {
		SDL_Log("[%s] main_load_cars_sprites!\n", __func__);
		return ret;
	}

	ret = gfx_load_background(ctx);
	if (ret < 0) {
		SDL_Log("[%s] gfx_load_background!\n", __func__);
		return ret;
	}

	ret = gfx_load_scene_sprites(ctx);
	if (ret < 0) {
		SDL_Log("[%s] gfx_load_scene_sprites!\n", __func__);
		return ret;
	}

	ret = gfx_load_particles(ctx);
	if (ret < 0) {
		SDL_Log("[%s] gfx_load_particles!\n", __func__);
		return ret;
	}

	ret = gfx_load_font(ctx);
	if (ret < 0) {
		SDL_Log("[%s] gfx_load_scene_font!\n", __func__);
		return ret;
	}

	SDL_Log("media loaded\n");

	return 0;
}


int gfx_unload_resources(struct game_context *ctx)
{
	for (int i = 0; i < CAR_MODEL_LAST; i++)
		SDL_DestroyTexture(ctx->gfx.cars_side[i].texture);


	return 0;
}