
#include "main.h"

//#define SOFACHROME_FONT "./media/font/GeneraleStation-Regular.otf"
//#define SOFACHROME_FONT "./media/font/01 DigitMono.ttf"

#define PNG_CAR_SIDE_BACKGROUND "./media/car_side_background.png"

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
#define PNG_BG_CANYON "./media/background/bg_canyon.png"
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

#define PNG_SCENE_MAOI "./media/scene/scene_maoi.png"
#define PNG_SCENE_BUOY "./media/scene/scene_buoy.png"
#define PNG_SCENE_TREE_PALM "./media/scene/scene_tree_palm.png"
#define PNG_SCENE_BOAT_SPEED "./media/scene/scene_boat_speed.png"
#define PNG_SCENE_BEACH_CABIN "./media/scene/scene_beach_cabin.png"
#define PNG_SCENE_BEACH_UMBRELLA "./media/scene/scene_beach_umbrella.png"
#define PNG_SCENE_BILLBOARD_BEACH "./media/scene/scene_billboard_beach.png"

#define PNG_SCENE_IGLOO "./media/scene/scene_igloo.png"
#define PNG_SCENE_SNOW_INN "./media/scene/scene_snow_inn.png"
#define PNG_SCENE_SNOWMAN "./media/scene/scene_snowman.png"
#define PNG_SCENE_LANTERN "./media/scene/scene_lantern.png"
#define PNG_SCENE_BENCH "./media/scene/scene_bench.png"
#define PNG_SCENE_TREE_PINE_SNOW "./media/scene/scene_tree_pine_snow.png"
#define PNG_SCENE_TREE_DEAD_SNOW "./media/scene/scene_tree_dead_snow.png"

#define PNG_SCENE_TUNNEL_A_BRIGHT "./media/scene/scene_tunnel_a_bright.png"
#define PNG_SCENE_TUNNEL_A_DARK "./media/scene/scene_tunnel_a_dark.png"
#define PNG_SCENE_BUILDING_01 "./media/scene/scene_building_01.png"
#define PNG_SCENE_BUILDING_02 "./media/scene/scene_building_02.png"
#define PNG_SCENE_BUILDING_03 "./media/scene/scene_building_03.png"

#define PNG_SCENE_VAULT "./media/scene/scene_vault.png"
#define PNG_SCENE_GRAVE_01 "./media/scene/scene_grave_01.png"
#define PNG_SCENE_GRAVE_02 "./media/scene/scene_grave_02.png"
#define PNG_SCENE_GRAVE_03 "./media/scene/scene_grave_03.png"
#define PNG_SCENE_GRAVE_FENCE "./media/scene/scene_grave_fence.png"
#define PNG_SCENE_TREE_SPOOKY "./media/scene/scene_tree_spooky.png"

#define PNG_SCENE_CAROUSEL "./media/scene/scene_carousel.png"
#define PNG_SCENE_CIRCUS "./media/scene/scene_circus.png"
#define PNG_SCENE_GREATWHEEL "./media/scene/scene_greatwheel.png"
#define PNG_SCENE_ROLLERCOASTER "./media/scene/scene_rollercoaster.png"

#define PNG_SCENE_BUSH_01 "./media/scene/scene_bush_01.png"
#define PNG_SCENE_BUSH_02 "./media/scene/scene_bush_02.png"
#define PNG_SCENE_BUSH_03 "./media/scene/scene_bush_03.png"
#define PNG_SCENE_BUSH_04 "./media/scene/scene_bush_04.png"
#define PNG_SCENE_BUSH_05 "./media/scene/scene_bush_05.png"
#define PNG_SCENE_BUSH_06 "./media/scene/scene_bush_06.png"
#define PNG_SCENE_BUSH_FLOWER "./media/scene/scene_bush_flower.png"


#define PNG_SCENE_BIG_ROCK "./media/scene/scene_big_rock.png"
#define PNG_SCENE_ROCK_01 "./media/scene/scene_rock_01.png"
#define PNG_SCENE_ROCK_02 "./media/scene/scene_rock_02.png"
#define PNG_SCENE_ROCK_03 "./media/scene/scene_rock_03.png"
#define PNG_SCENE_ROCK_04 "./media/scene/scene_rock_04.png"
#define PNG_SCENE_ROCK_05 "./media/scene/scene_rock_05.png"
#define PNG_SCENE_CACTUS_01 "./media/scene/scene_cactus_01.png"
#define PNG_SCENE_CACTUS_02 "./media/scene/scene_cactus_02.png"
#define PNG_SCENE_CACTUS_03 "./media/scene/scene_cactus_03.png"
#define PNG_SCENE_CACTUS_04 "./media/scene/scene_cactus_04.png"
#define PNG_SCENE_DESERT_GRASS_01 "./media/scene/scene_desert_grass_01.png"
#define PNG_SCENE_DESERT_GRASS_02 "./media/scene/scene_desert_grass_02.png"


#define PNG_SCENE_COLUMN_01 "./media/scene/scene_column_01.png"
#define PNG_SCENE_COLUMN_02 "./media/scene/scene_column_02.png"
#define PNG_SCENE_COLUMN_03 "./media/scene/scene_column_03.png"
#define PNG_SCENE_DELPHI "./media/scene/scene_delphi.png"
#define PNG_SCENE_TEMPLE "./media/scene/scene_temple.png"

#define PNG_SCENE_DUNE_01 "./media/scene/scene_dune_01.png"
#define PNG_SCENE_DUNE_02 "./media/scene/scene_dune_02.png"
#define PNG_SCENE_DUNE_03 "./media/scene/scene_dune_03.png"
#define PNG_SCENE_EGYPT_COLUMN "./media/scene/scene_egypt_column.png"
#define PNG_SCENE_EGYPT_TEMPLE "./media/scene/scene_egypt_temple.png"
//#define PNG_SCENE_RAM_STATUE "./media/scene/scene_ram_statue.png"
#define PNG_SCENE_RAM_STATUE "./media/scene/scene_ram_statue_75p.png"


#define PNG_SCENE_WALL "./media/scene/scene_wall.png"
#define PNG_SCENE_TOWER "./media/scene/scene_tower.png"
#define PNG_SCENE_GARGAMEL "./media/scene/scene_gargamel.png"

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


#define PNG_TRACK_DIJON "./media/tracks/dijon.png"
#define PNG_TRACK_SPEEDWAY "./media/tracks/speedway.png"
#define PNG_TRACK_FORK "./media/tracks/fork.png"
#define PNG_TRACK_FROST "./media/tracks/frost.png"
#define PNG_TRACK_STONE "./media/tracks/stone.png"
#define PNG_TRACK_CURVES "./media/tracks/curves.png"
#define PNG_TRACK_HORNS "./media/tracks/horns.png"
#define PNG_TRACK_SQUARES "./media/tracks/squares.png"
#define PNG_TRACK_WHALE "./media/tracks/whale.png"
#define PNG_TRACK_CARMONA "./media/tracks/carmona.png"


#define PNG_STATS_TRUENO "./media/stats/stats_trueno.png"
#define PNG_STATS_DELTA "./media/stats/stats_delta.png"
#define PNG_STATS_FALCON "./media/stats/stats_falcon.png"
#define PNG_STATS_HART "./media/stats/stats_hart.png"
#define PNG_STATS_IMPREZIA "./media/stats/stats_imprezia.png"
#define PNG_STATS_LANCER "./media/stats/stats_lancer.png"
#define PNG_STATS_TT "./media/stats/stats_tt.png"
#define PNG_STATS_NSX "./media/stats/stats_nsx.png"
#define PNG_STATS_LOTUS "./media/stats/stats_lotus.png"
#define PNG_STATS_VIPER "./media/stats/stats_viper.png"


#define PNG_GUI_LOCK "./media/gui/lock_bright.png"
#define PNG_GUI_PAUSE "./media/gui/pause_grey.png"
#define PNG_GUI_SETTINGS "./media/gui/settings.png"
#define PNG_GUI_EXIT "./media/gui/exit.png"
#define PNG_GUI_PREV "./media/gui/prev.png"
//#define PNG_GUI_PLAY "./media/gui/play_y.png"
#define PNG_GUI_PLAY "./media/gui/play_icon.png"
#define PNG_GUI_UP "./media/gui/up.png"
#define PNG_GUI_DOWN "./media/gui/down.png"
#define PNG_GUI_CREDIT "./media/gui/credit.png"
#define PNG_GUI_CASE "./media/gui/case_empty.png"
#define PNG_GUI_ACCEL "./media/gui/pedal_accel.png"
#define PNG_GUI_BRAKE "./media/gui/pedal_brake.png"
#define PNG_GUI_LEFT "./media/gui/dir_left.png"
#define PNG_GUI_RIGHT "./media/gui/dir_right.png"


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


static int gfx_load_scene_sprites_carmona(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);

	load_texture_from_file(
		ctx, PNG_SCENE_CAROUSEL, &ctx->gfx.scene_carousel);
	load_texture_from_file(ctx, PNG_SCENE_CIRCUS, &ctx->gfx.scene_circus);
	load_texture_from_file(
		ctx, PNG_SCENE_GREATWHEEL, &ctx->gfx.scene_greatwheel);
	load_texture_from_file(
		ctx, PNG_SCENE_ROLLERCOASTER, &ctx->gfx.scene_rollercoaster);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_OAK, &ctx->gfx.scene_tree_oak);

	return 0;
}

static int gfx_load_scene_sprites_whale(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	load_texture_from_file(ctx,
			       PNG_SCENE_TUNNEL_A_BRIGHT,
			       &ctx->gfx.scene_tunnel_a_bright);
	load_texture_from_file(
		ctx, PNG_SCENE_TUNNEL_A_DARK, &ctx->gfx.scene_tunnel_a_dark);

	load_texture_from_file(
		ctx, PNG_SCENE_BUILDING_01, &ctx->gfx.scene_building_01);
	load_texture_from_file(
		ctx, PNG_SCENE_BUILDING_02, &ctx->gfx.scene_building_02);
	load_texture_from_file(
		ctx, PNG_SCENE_BUILDING_03, &ctx->gfx.scene_building_03);
	load_texture_from_file(ctx, PNG_SCENE_LANTERN, &ctx->gfx.scene_lantern);
	load_texture_from_file(ctx, PNG_SCENE_BENCH, &ctx->gfx.scene_bench);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_WILLOW, &ctx->gfx.scene_tree_willow);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_FLOWER, &ctx->gfx.scene_bush_flower);
	load_texture_from_file(ctx,
			       PNG_SCENE_BILLBOARD_BEACH,
			       &ctx->gfx.scene_billboard_beach);

	return 0;
}

static int gfx_load_scene_sprites_squares(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);

	load_texture_from_file(ctx, PNG_SCENE_VAULT, &ctx->gfx.scene_vault);
	load_texture_from_file(
		ctx, PNG_SCENE_GRAVE_01, &ctx->gfx.scene_grave_01);
	load_texture_from_file(
		ctx, PNG_SCENE_GRAVE_02, &ctx->gfx.scene_grave_02);
	load_texture_from_file(
		ctx, PNG_SCENE_GRAVE_03, &ctx->gfx.scene_grave_03);
	load_texture_from_file(
		ctx, PNG_SCENE_GRAVE_FENCE, &ctx->gfx.scene_grave_fence);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_SPOOKY, &ctx->gfx.scene_tree_spooky);

	return 0;
}

static int gfx_load_scene_sprites_horns(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_WILLOW, &ctx->gfx.scene_tree_willow);
	load_texture_from_file(ctx, PNG_SCENE_WELL, &ctx->gfx.scene_well);

	load_texture_from_file(ctx, PNG_SCENE_WALL, &ctx->gfx.scene_wall);
	load_texture_from_file(ctx, PNG_SCENE_TOWER, &ctx->gfx.scene_tower);
	load_texture_from_file(
		ctx, PNG_SCENE_GARGAMEL, &ctx->gfx.scene_gargamel);

	load_texture_from_file(ctx, PNG_SCENE_GRASS, &ctx->gfx.scene_grass);
	load_texture_from_file(
		ctx, PNG_SCENE_BUSH_FLOWER, &ctx->gfx.scene_bush_flower);

	/*load_texture_from_file(ctx, PNG_SCENE_FENCE, &ctx->gfx.scene_fence);
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
		ctx, PNG_SCENE_BUSH_FLOWER, &ctx->gfx.scene_bush_flower);*/

	return 0;
}

static int gfx_load_scene_sprites_stone(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);

	load_texture_from_file(
		ctx, PNG_SCENE_COLUMN_01, &ctx->gfx.scene_column_01);
	load_texture_from_file(
		ctx, PNG_SCENE_COLUMN_02, &ctx->gfx.scene_column_02);
	load_texture_from_file(
		ctx, PNG_SCENE_COLUMN_03, &ctx->gfx.scene_column_03);
	load_texture_from_file(ctx, PNG_SCENE_DELPHI, &ctx->gfx.scene_delphi);
	load_texture_from_file(ctx, PNG_SCENE_TEMPLE, &ctx->gfx.scene_temple);

	return 0;
}

static int gfx_load_scene_sprites_curves(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);

	load_texture_from_file(ctx, PNG_SCENE_DUNE_01, &ctx->gfx.scene_dune_01);
	load_texture_from_file(ctx, PNG_SCENE_DUNE_02, &ctx->gfx.scene_dune_02);
	load_texture_from_file(ctx, PNG_SCENE_DUNE_03, &ctx->gfx.scene_dune_03);
	load_texture_from_file(
		ctx, PNG_SCENE_EGYPT_COLUMN, &ctx->gfx.scene_egypt_column);
	load_texture_from_file(
		ctx, PNG_SCENE_EGYPT_TEMPLE, &ctx->gfx.scene_egypt_temple);
	load_texture_from_file(
		ctx, PNG_SCENE_RAM_STATUE, &ctx->gfx.scene_ram_statue);

	return 0;
}


static int gfx_load_scene_sprites_frost(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	load_texture_from_file(ctx, PNG_SCENE_IGLOO, &ctx->gfx.scene_igloo);
	load_texture_from_file(
		ctx, PNG_SCENE_SNOW_INN, &ctx->gfx.scene_snow_inn);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_PINE_SNOW, &ctx->gfx.scene_tree_pine_snow);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_DEAD_SNOW, &ctx->gfx.scene_tree_dead_snow);
	load_texture_from_file(ctx, PNG_SCENE_SNOWMAN, &ctx->gfx.scene_snowman);
	load_texture_from_file(ctx, PNG_SCENE_LANTERN, &ctx->gfx.scene_lantern);
	load_texture_from_file(ctx, PNG_SCENE_BENCH, &ctx->gfx.scene_bench);

	return 0;
}

static int gfx_load_scene_sprites_seaside(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	load_texture_from_file(ctx, PNG_SCENE_MAOI, &ctx->gfx.scene_maoi);
	load_texture_from_file(ctx, PNG_SCENE_BUOY, &ctx->gfx.scene_buoy);
	load_texture_from_file(
		ctx, PNG_SCENE_TREE_PALM, &ctx->gfx.scene_tree_palm);
	load_texture_from_file(
		ctx, PNG_SCENE_BOAT_SPEED, &ctx->gfx.scene_boat_speed);
	load_texture_from_file(
		ctx, PNG_SCENE_BEACH_CABIN, &ctx->gfx.scene_beach_cabin);
	load_texture_from_file(
		ctx, PNG_SCENE_BEACH_UMBRELLA, &ctx->gfx.scene_beach_umbrella);
	load_texture_from_file(ctx,
			       PNG_SCENE_BILLBOARD_BEACH,
			       &ctx->gfx.scene_billboard_beach);

	return 0;
}

static int gfx_load_scene_sprites_fork(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_CANYON, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	load_texture_from_file(
		ctx, PNG_SCENE_START_LANE, &ctx->gfx.scene_start_lane);
	/*load_texture_from_file(ctx,
			       PNG_SCENE_TUNNEL_A_BRIGHT,
			       &ctx->gfx.scene_tunnel_a_bright);
	load_texture_from_file(
		ctx, PNG_SCENE_TUNNEL_A_DARK, &ctx->gfx.scene_tunnel_a_dark);*/

	load_texture_from_file(
		ctx, PNG_SCENE_BIG_ROCK, &ctx->gfx.scene_big_rock);
	load_texture_from_file(ctx, PNG_SCENE_ROCK_01, &ctx->gfx.scene_rock_01);
	load_texture_from_file(ctx, PNG_SCENE_ROCK_02, &ctx->gfx.scene_rock_02);
	load_texture_from_file(ctx, PNG_SCENE_ROCK_03, &ctx->gfx.scene_rock_03);
	load_texture_from_file(ctx, PNG_SCENE_ROCK_04, &ctx->gfx.scene_rock_04);
	load_texture_from_file(ctx, PNG_SCENE_ROCK_05, &ctx->gfx.scene_rock_05);
	load_texture_from_file(
		ctx, PNG_SCENE_CACTUS_01, &ctx->gfx.scene_cactus_01);
	load_texture_from_file(
		ctx, PNG_SCENE_CACTUS_02, &ctx->gfx.scene_cactus_02);
	load_texture_from_file(
		ctx, PNG_SCENE_CACTUS_03, &ctx->gfx.scene_cactus_03);
	load_texture_from_file(
		ctx, PNG_SCENE_CACTUS_04, &ctx->gfx.scene_cactus_04);
	load_texture_from_file(ctx,
			       PNG_SCENE_DESERT_GRASS_01,
			       &ctx->gfx.scene_desert_grass_01);
	load_texture_from_file(ctx,
			       PNG_SCENE_DESERT_GRASS_02,
			       &ctx->gfx.scene_desert_grass_02);


	return 0;
}

static int gfx_load_scene_sprites_dijon(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_BG_MOUNTAINS, &ctx->gfx.bg_landscape_far);
	gfx_load_texture(ctx, PNG_BG_SKY_NEAR, &ctx->gfx.bg_sky_near);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

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


static int gfx_load_scene_sprites(struct game_context *ctx)
{
	switch (ctx->track.track_selected) {
	case TRACK_DIJON:
		gfx_load_scene_sprites_dijon(ctx);
		break;
	case TRACK_SPEEDWAY:
		gfx_load_scene_sprites_seaside(ctx);
		break;
	case TRACK_FROST:
		gfx_load_scene_sprites_frost(ctx);
		break;
	case TRACK_FORK:
		gfx_load_scene_sprites_fork(ctx);
		break;
	case TRACK_STONE:
		gfx_load_scene_sprites_stone(ctx);
		break;
	case TRACK_CURVES:
		gfx_load_scene_sprites_curves(ctx);
		break;
	case TRACK_HORNS:
		gfx_load_scene_sprites_horns(ctx);
		break;
	case TRACK_SQUARES:
		gfx_load_scene_sprites_squares(ctx);
		break;
	case TRACK_WHALE:
		gfx_load_scene_sprites_whale(ctx);
		break;
	case TRACK_CARMONA:
		gfx_load_scene_sprites_carmona(ctx);
		break;
	default:
		SDL_Log("[%s] invalid track\n", __func__);
	};
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


int gfx_load_cars_side(struct game_context *ctx)
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

	gfx_load_texture(ctx, PNG_CAR_SIDE_BACKGROUND, &ctx->gfx.car_side_bg);

	return 0;
}

static int gfx_load_cars_stats(struct game_context *ctx)
{
	gfx_load_texture(ctx,
			 PNG_STATS_IMPREZIA,
			 &ctx->gfx.cars_stats[CAR_MODEL_IMPREZIA]);
	gfx_load_texture(
		ctx, PNG_STATS_DELTA, &ctx->gfx.cars_stats[CAR_MODEL_DELTA]);
	gfx_load_texture(
		ctx, PNG_STATS_TRUENO, &ctx->gfx.cars_stats[CAR_MODEL_TRUENO]);
	gfx_load_texture(
		ctx, PNG_STATS_FALCON, &ctx->gfx.cars_stats[CAR_MODEL_FALCON]);
	gfx_load_texture(
		ctx, PNG_STATS_HART, &ctx->gfx.cars_stats[CAR_MODEL_HART]);
	gfx_load_texture(
		ctx, PNG_STATS_NSX, &ctx->gfx.cars_stats[CAR_MODEL_NSX]);
	gfx_load_texture(
		ctx, PNG_STATS_VIPER, &ctx->gfx.cars_stats[CAR_MODEL_VIPER]);
	gfx_load_texture(
		ctx, PNG_STATS_LANCER, &ctx->gfx.cars_stats[CAR_MODEL_LANCER]);
	gfx_load_texture(
		ctx, PNG_STATS_LOTUS, &ctx->gfx.cars_stats[CAR_MODEL_LOTUS]);
	gfx_load_texture(ctx, PNG_STATS_TT, &ctx->gfx.cars_stats[CAR_MODEL_TT]);

	return 0;
}

static int gfx_load_gui(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_GUI_CREDIT, &ctx->gfx.gui_credit);

	gfx_load_texture(ctx, PNG_GUI_SETTINGS, &ctx->gfx.gui_settings);

	gfx_load_texture(ctx, PNG_GUI_EXIT, &ctx->gfx.gui_exit);

	gfx_load_texture(ctx, PNG_GUI_PREV, &ctx->gfx.gui_prev);

	gfx_load_texture(ctx, PNG_GUI_PLAY, &ctx->gfx.gui_play);

	gfx_load_texture(ctx, PNG_GUI_UP, &ctx->gfx.gui_up);

	gfx_load_texture(ctx, PNG_GUI_DOWN, &ctx->gfx.gui_down);

	gfx_load_texture(ctx, PNG_GUI_CASE, &ctx->gfx.gui_case);

	gfx_load_texture(ctx, PNG_GUI_LOCK, &ctx->gfx.gui_lock);
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

int gfx_load_tracks_thumbnail(struct game_context *ctx)
{
	gfx_load_texture(
		ctx, PNG_TRACK_DIJON, &ctx->gfx.track_thumbnail[TRACK_DIJON]);
	gfx_load_texture(ctx,
			 PNG_TRACK_SPEEDWAY,
			 &ctx->gfx.track_thumbnail[TRACK_SPEEDWAY]);
	gfx_load_texture(
		ctx, PNG_TRACK_FORK, &ctx->gfx.track_thumbnail[TRACK_FORK]);
	gfx_load_texture(
		ctx, PNG_TRACK_FROST, &ctx->gfx.track_thumbnail[TRACK_FROST]);
	gfx_load_texture(
		ctx, PNG_TRACK_STONE, &ctx->gfx.track_thumbnail[TRACK_STONE]);
	gfx_load_texture(
		ctx, PNG_TRACK_HORNS, &ctx->gfx.track_thumbnail[TRACK_HORNS]);
	gfx_load_texture(
		ctx, PNG_TRACK_CURVES, &ctx->gfx.track_thumbnail[TRACK_CURVES]);
	gfx_load_texture(ctx,
			 PNG_TRACK_SQUARES,
			 &ctx->gfx.track_thumbnail[TRACK_SQUARES]);
	gfx_load_texture(
		ctx, PNG_TRACK_WHALE, &ctx->gfx.track_thumbnail[TRACK_WHALE]);
	gfx_load_texture(ctx,
			 PNG_TRACK_CARMONA,
			 &ctx->gfx.track_thumbnail[TRACK_CARMONA]);
	return 0;
}


static int gfx_load_title(struct game_context *ctx)
{
	gfx_load_texture(ctx, PNG_SCENE_TREE_OAK, &ctx->gfx.scene_tree_oak);
	gfx_load_texture(ctx, PNG_BG_SKY_FAR, &ctx->gfx.bg_sky_far);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// public function
/////////////////////////////////////////////////////////////////////////////////////

int gfx_load_resources_title(struct game_context *ctx)
{
	gfx_load_title(ctx);
	gfx_load_cars_side(ctx);
	return 0;
}

int gfx_load_resources_menu_select_track(struct game_context *ctx)
{
	gfx_load_tracks_thumbnail(ctx);
	return 0;
}

int gfx_load_resources_menu_select_car(struct game_context *ctx)
{
	gfx_load_cars_side(ctx);
	gfx_load_cars_stats(ctx);
	return 0;
}

int gfx_load_resources_menu_main(struct game_context *ctx)
{
	gfx_load_cars_side(ctx);
	gfx_load_cars_stats(ctx);
	gfx_load_tracks_thumbnail(ctx);
	gfx_load_gui(ctx);

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

	gfx_load_texture(ctx, PNG_GUI_PREV, &ctx->gfx.gui_prev);
	gfx_load_texture(ctx, PNG_GUI_CASE, &ctx->gfx.gui_case);
	gfx_load_texture(ctx, PNG_GUI_PAUSE, &ctx->gfx.gui_pause);
	gfx_load_texture(ctx, PNG_GUI_ACCEL, &ctx->gfx.gui_accel);
	gfx_load_texture(ctx, PNG_GUI_BRAKE, &ctx->gfx.gui_brake);
	gfx_load_texture(ctx, PNG_GUI_LEFT, &ctx->gfx.gui_left);
	gfx_load_texture(ctx, PNG_GUI_RIGHT, &ctx->gfx.gui_right);

	SDL_Log("media loaded\n");

	return 0;
}


int gfx_unload_resources(struct game_context *ctx)
{

	for (int i = 0; i < CAR_MODEL_LAST; i++)
		for (int j = 0; j < CAR_SPRITE_LAST; j++)
			SDL_DestroyTexture(ctx->gfx.cars[i][j].texture);

	for (int i = 0; i < CAR_MODEL_LAST; i++) {
		SDL_DestroyTexture(ctx->gfx.cars_side[i].texture);
		SDL_DestroyTexture(ctx->gfx.cars_stats[i].texture);
	}

	SDL_DestroyTexture(ctx->gfx.bg_landscape_far.texture);
	SDL_DestroyTexture(ctx->gfx.bg_sky_near.texture);
	SDL_DestroyTexture(ctx->gfx.bg_sky_far.texture);

	SDL_DestroyTexture(ctx->gfx.scene_start_lane.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_oak.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_willow.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_pine.texture);
	SDL_DestroyTexture(ctx->gfx.scene_well.texture);
	SDL_DestroyTexture(ctx->gfx.scene_fence.texture);
	SDL_DestroyTexture(ctx->gfx.scene_grass.texture);
	SDL_DestroyTexture(ctx->gfx.scene_windmill.texture);
	SDL_DestroyTexture(ctx->gfx.scene_barn.texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[0].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[2].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[3].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[4].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[5].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bushes[6].texture);
	SDL_DestroyTexture(ctx->gfx.scene_bush_flower.texture);

	SDL_DestroyTexture(ctx->gfx.scene_maoi.texture);
	SDL_DestroyTexture(ctx->gfx.scene_buoy.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_palm.texture);
	SDL_DestroyTexture(ctx->gfx.scene_boat_speed.texture);
	SDL_DestroyTexture(ctx->gfx.scene_beach_cabin.texture);
	SDL_DestroyTexture(ctx->gfx.scene_beach_umbrella.texture);
	SDL_DestroyTexture(ctx->gfx.scene_billboard_beach.texture);

	SDL_DestroyTexture(ctx->gfx.scene_igloo.texture);
	SDL_DestroyTexture(ctx->gfx.scene_snow_inn.texture);
	SDL_DestroyTexture(ctx->gfx.scene_snowman.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_pine_snow.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_dead_snow.texture);
	SDL_DestroyTexture(ctx->gfx.scene_lantern.texture);
	SDL_DestroyTexture(ctx->gfx.scene_bench.texture);

	SDL_DestroyTexture(ctx->gfx.scene_big_rock.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rock_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rock_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rock_03.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rock_04.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rock_05.texture);
	SDL_DestroyTexture(ctx->gfx.scene_cactus_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_cactus_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_cactus_03.texture);
	SDL_DestroyTexture(ctx->gfx.scene_cactus_04.texture);
	SDL_DestroyTexture(ctx->gfx.scene_desert_grass_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_desert_grass_02.texture);

	SDL_DestroyTexture(ctx->gfx.scene_column_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_column_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_column_03.texture);
	SDL_DestroyTexture(ctx->gfx.scene_delphi.texture);
	SDL_DestroyTexture(ctx->gfx.scene_temple.texture);

	SDL_DestroyTexture(ctx->gfx.scene_dune_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_dune_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_dune_03.texture);
	SDL_DestroyTexture(ctx->gfx.scene_egypt_column.texture);
	SDL_DestroyTexture(ctx->gfx.scene_egypt_temple.texture);
	SDL_DestroyTexture(ctx->gfx.scene_ram_statue.texture);

	SDL_DestroyTexture(ctx->gfx.scene_wall.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tower.texture);
	SDL_DestroyTexture(ctx->gfx.scene_gargamel.texture);

	SDL_DestroyTexture(ctx->gfx.scene_tunnel_a_bright.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tunnel_a_dark.texture);
	SDL_DestroyTexture(ctx->gfx.scene_building_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_building_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_building_03.texture);

	SDL_DestroyTexture(ctx->gfx.scene_vault.texture);
	SDL_DestroyTexture(ctx->gfx.scene_grave_01.texture);
	SDL_DestroyTexture(ctx->gfx.scene_grave_02.texture);
	SDL_DestroyTexture(ctx->gfx.scene_grave_03.texture);
	SDL_DestroyTexture(ctx->gfx.scene_grave_fence.texture);
	SDL_DestroyTexture(ctx->gfx.scene_tree_spooky.texture);

	SDL_DestroyTexture(ctx->gfx.scene_circus.texture);
	SDL_DestroyTexture(ctx->gfx.scene_greatwheel.texture);
	SDL_DestroyTexture(ctx->gfx.scene_carousel.texture);
	SDL_DestroyTexture(ctx->gfx.scene_rollercoaster.texture);

	SDL_DestroyTexture(ctx->gfx.t_smoke[0].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[1].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[2].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[3].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[4].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[5].texture);
	SDL_DestroyTexture(ctx->gfx.t_smoke[6].texture);
	SDL_DestroyTexture(ctx->gfx.t_nitro[0].texture);
	SDL_DestroyTexture(ctx->gfx.t_nitro[1].texture);
	SDL_DestroyTexture(ctx->gfx.t_nitro[2].texture);
	SDL_DestroyTexture(ctx->gfx.t_nitro[3].texture);
	SDL_DestroyTexture(ctx->gfx.t_nitro[4].texture);


	for (int i = 0; i < TRACK_LAST; i++)
		SDL_DestroyTexture(ctx->gfx.track_thumbnail[i].texture);


	SDL_DestroyTexture(ctx->gfx.gui_lock.texture);
	SDL_DestroyTexture(ctx->gfx.gui_pause.texture);
	SDL_DestroyTexture(ctx->gfx.gui_credit.texture);
	SDL_DestroyTexture(ctx->gfx.gui_settings.texture);
	SDL_DestroyTexture(ctx->gfx.gui_exit.texture);
	SDL_DestroyTexture(ctx->gfx.gui_prev.texture);
	SDL_DestroyTexture(ctx->gfx.gui_play.texture);
	SDL_DestroyTexture(ctx->gfx.gui_up.texture);
	SDL_DestroyTexture(ctx->gfx.gui_down.texture);
	SDL_DestroyTexture(ctx->gfx.gui_case.texture);
	SDL_DestroyTexture(ctx->gfx.gui_accel.texture);
	SDL_DestroyTexture(ctx->gfx.gui_brake.texture);
	SDL_DestroyTexture(ctx->gfx.gui_left.texture);
	SDL_DestroyTexture(ctx->gfx.gui_right.texture);

	// unload fonts

	return 0;
}
