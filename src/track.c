#include "track.h"
#include "main.h"


struct color_desc cd_lane_yellow = {.r = 255, .g = 234, .b = 0};
struct color_desc cd_lane_white = {.r = 255, .g = 255, .b = 255};
struct color_desc cd_road_asphalt_bright = {.r = 140, .g = 140, .b = 140};
struct color_desc cd_road_asphalt_dark = {.r = 128, .g = 128, .b = 128};
struct color_desc cd_road_mud_bright = {.r = 149, .g = 69, .b = 53};
struct color_desc cd_road_mud_dark = {.r = 129, .g= 49, .b = 33};
struct color_desc cd_grass_bright = {.r = 0, .g = 169, .b = 0};
struct color_desc cd_grass_dark = {.r = 0, .g = 160, .b = 0};
struct color_desc cd_rumble_bright = {.r = 255, .g = 255, .b = 255};
struct color_desc cd_rumble_dark = {.r = 255, .g = 0, .b = 0};
struct color_desc cd_rumble_mud_bright = {.r = 123, .g = 63, .b = 0};
struct color_desc cd_rumble_mud_dark = {.r = 103, .g = 43, .b = 0};
/*struct color_desc cd_rumble_mud_bright = {.r = 138, .g = 51, .b = 36};
struct color_desc cd_rumble_mud_dark = {.r = 118, .g = 31, .b = 16};*/
/*struct color_desc cd_rumble_mud_bright = {.r = 130, .g = 102, .b = 68};
struct color_desc cd_rumble_mud_dark = {.r = 110, .g = 82, .b = 48};*/
struct color_desc cd_water_bright = {.r = 38, .g = 75, .b = 106};
struct color_desc cd_water_dark = {.r = 58, .g = 95, .b = 126};
struct color_desc cd_foam_bright = {.r = 240, .g = 240, .b = 240};
struct color_desc cd_foam_dark = {.r = 220, .g = 220, .b = 220};
struct color_desc cd_sand_bright = {.r = 248, .g = 220, .b = 172};
struct color_desc cd_sand_dark = {.r = 228, .g = 200, .b = 152};
struct color_desc cd_mud_bright = {.r = 193, .g = 154, .b = 107};
struct color_desc cd_mud_dark = {.r = 173, .g= 134, .b = 87};

static struct track_build_info track_build_tab[TRACK_LAST] = {
	{.nb_sector = NB_SECTOR_DIJON, .nb_segment = NB_SEGMENT_DIJON},
	{.nb_sector = NB_SECTOR_SPEEDWAY, .nb_segment = NB_SEGMENT_SPEEDWAY},
	{.nb_sector = NB_SECTOR_FORK, .nb_segment = NB_SEGMENT_FORK}
	};

static int sector_dijon[NB_SECTOR_DIJON][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 3, 2},
	{LG_SHORT, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_UP_LOW, CURVE_L_EASY, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 2, 2},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 3, 2},

	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_R_MEDIUM, 2, 2},
	{LG_LONG, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_MEDIUM, 2, 2},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}


};

static int sector_speedway[NB_SECTOR_SPEEDWAY][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 4},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 4, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 4, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}};


static int sector_fork[NB_SECTOR_FORK][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_L_MEDIUM, 3, 2},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_EASY, 2, 2},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_L_MEDIUM, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 3, 3},
	
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}
	};


static SDL_Rect hitbox_oak = {.x = 262, .y = 0, .w = 240, .h = 711};


static int set_scene_sprite_desc(struct scene_sprite_desc *sprite_desc,
				 struct texture *t,
				 float position,
				 SDL_Rect *hitbox,
				 int collide)
{
	sprite_desc->position = position;
	sprite_desc->t = t;
	sprite_desc->hitbox = hitbox;
	sprite_desc->collide = collide;


	if (position < 0)
		sprite_desc->flip = SDL_FLIP_HORIZONTAL;
	else
		sprite_desc->flip = SDL_FLIP_NONE;

	return 0;
}

// TODO: use realloc at each sector addition instead counting total nb sectors
// in advance


static int track_build_fork(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_FORK; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_fork[i][SECTOR_PARAM_ENTER_LG],
			sector_fork[i][SECTOR_PARAM_HOLD_LG],
			sector_fork[i][SECTOR_PARAM_EXIT_LG],
			sector_fork[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_fork[i][SECTOR_PARAM_EXIT_CURVE],
			sector_fork[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_fork[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_fork[i][SECTOR_PARAM_ENTER_LG] +
				sector_fork[i][SECTOR_PARAM_HOLD_LG] +
				sector_fork[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_NONE;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.cd_road_bright = &cd_road_mud_bright;
	ctx->track.cd_road_dark = &cd_road_mud_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_mud_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_mud_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_mud_bright;
	ctx->track.cds[0].dark = &cd_mud_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	return 0;
}


static int track_build_speedway(struct game_context *ctx)
{


	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_SPEEDWAY; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_speedway[i][SECTOR_PARAM_ENTER_LG],
			sector_speedway[i][SECTOR_PARAM_HOLD_LG],
			sector_speedway[i][SECTOR_PARAM_EXIT_LG],
			sector_speedway[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_speedway[i][SECTOR_PARAM_EXIT_CURVE],
			sector_speedway[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_speedway[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_speedway[i][SECTOR_PARAM_ENTER_LG] +
				sector_speedway[i][SECTOR_PARAM_HOLD_LG] +
				sector_speedway[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 4;
	ctx->track.cds[0].bright = &cd_water_bright;
	ctx->track.cds[0].dark = &cd_water_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_RIGHT;

	ctx->track.cds[1].bright = &cd_foam_bright;
	ctx->track.cds[1].dark = &cd_foam_dark;
	ctx->track.cds[1].num = 300;
	ctx->track.cds[1].den = 100;
	ctx->track.cds[1].side = CDS_RIGHT;

	ctx->track.cds[2].bright = &cd_sand_bright;
	ctx->track.cds[2].dark = &cd_sand_dark;
	ctx->track.cds[2].num = 250;
	ctx->track.cds[2].den = 100;
	ctx->track.cds[2].side = CDS_RIGHT;

	ctx->track.cds[3].bright = &cd_sand_bright;
	ctx->track.cds[3].dark = &cd_sand_dark;
	ctx->track.cds[3].num = 250;
	ctx->track.cds[3].den = 100;
	ctx->track.cds[3].side = CDS_FULL_LEFT;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	ctx->track.lane_type = LANE_TYPE_HALF;

	return 0;
}


static int track_build_dijon(struct game_context *ctx)
{


	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_DIJON; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_dijon[i][SECTOR_PARAM_ENTER_LG],
			sector_dijon[i][SECTOR_PARAM_HOLD_LG],
			sector_dijon[i][SECTOR_PARAM_EXIT_LG],
			sector_dijon[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_dijon[i][SECTOR_PARAM_EXIT_CURVE],
			sector_dijon[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_dijon[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_dijon[i][SECTOR_PARAM_ENTER_LG] +
				sector_dijon[i][SECTOR_PARAM_HOLD_LG] +
				sector_dijon[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	/////////////////////////////////////////////////////////////////////


	struct scene_seg_desc *start_lane =
		calloc(1, sizeof(struct scene_seg_desc));
	start_lane->nb_sprites = 1;
	float position = -0.9000001f;
	set_scene_sprite_desc(&start_lane->sprite[0],
			      &ctx->gfx.scene_start_lane,
			      position,
			      NULL,
			      1);

	struct scene_seg_desc *barn_n_well =
		calloc(1, sizeof(struct scene_seg_desc));
	barn_n_well->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&barn_n_well->sprite[2 * i],
				      i == 0 ? &ctx->gfx.scene_barn
					     : &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      1);
		set_scene_sprite_desc(&barn_n_well->sprite[2 * i + 1],
				      i == 0 ? &ctx->gfx.scene_well
					     : &ctx->gfx.scene_bush_flower,
				      -position,
				      NULL,
				      1);
	}

	struct scene_seg_desc *windmill_n_grass =
		calloc(1, sizeof(struct scene_seg_desc));
	windmill_n_grass->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&windmill_n_grass->sprite[2 * i],
				      i == 1 ? &ctx->gfx.scene_windmill
					     : &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      1);
		set_scene_sprite_desc(&windmill_n_grass->sprite[2 * i + 1],
				      i == 1 ? &ctx->gfx.scene_windmill
					     : &ctx->gfx.scene_grass,
				      -position,
				      NULL,
				      1);
	}

	struct scene_seg_desc *fence_n_bush =
		calloc(1, sizeof(struct scene_seg_desc));
	fence_n_bush->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&fence_n_bush->sprite[2 * i],
				      i < 1 ? &ctx->gfx.scene_fence
					    : &ctx->gfx.scene_bush_flower,
				      position,
				      NULL,
				      1);
		set_scene_sprite_desc(&fence_n_bush->sprite[2 * i + 1],
				      i < 1 ? &ctx->gfx.scene_fence
					    : &ctx->gfx.scene_bush_flower,
				      -position,
				      NULL,
				      1);
	}

	struct scene_seg_desc *grass = calloc(1, sizeof(struct scene_seg_desc));
	grass->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&grass->sprite[2 * i],
				      &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      0);
		set_scene_sprite_desc(&grass->sprite[2 * i + 1],
				      &ctx->gfx.scene_grass,
				      -position,
				      NULL,
				      0);
	}

	struct scene_seg_desc *oak_forest_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	oak_forest_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 + 2 * i);
		set_scene_sprite_desc(&oak_forest_1->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      position,
				      &hitbox_oak,
				      1);
		set_scene_sprite_desc(&oak_forest_1->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -position,
				      &hitbox_oak,
				      1);
	}

	struct scene_seg_desc *oak_forest_2 =
		calloc(1, sizeof(struct scene_seg_desc));
	oak_forest_2->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(2 + 2 * i);
		set_scene_sprite_desc(&oak_forest_2->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      position,
				      &hitbox_oak,
				      1);
		set_scene_sprite_desc(&oak_forest_2->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -position,
				      &hitbox_oak,
				      1);
	}

	// randomize different bushes set
	struct scene_seg_desc *bushes_rnd_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_1->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0);
		set_scene_sprite_desc(
			&bushes_rnd_1->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0);
	}
	struct scene_seg_desc *bushes_rnd_2 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_2->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_2->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0);
		set_scene_sprite_desc(
			&bushes_rnd_2->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0);
	}
	struct scene_seg_desc *bushes_rnd_3 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_3->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_3->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0);
		set_scene_sprite_desc(
			&bushes_rnd_3->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0);
	}
	struct scene_seg_desc *bushes_rnd_4 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_4->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_4->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0);
		set_scene_sprite_desc(
			&bushes_rnd_4->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0);
	}
	struct scene_seg_desc *bushes_rnd_5 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_5->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_5->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0);
		set_scene_sprite_desc(
			&bushes_rnd_5->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0);
	}

	struct scene_seg_desc *bushes_rnd_tab[5] = {bushes_rnd_1,
						    bushes_rnd_2,
						    bushes_rnd_3,
						    bushes_rnd_4,
						    bushes_rnd_5};

	/////////////////////////////////////////////////////////////////////

	for (int i = 0; i < nb_segments_added / 10; i += 5)
		// ctx->track.segments[i].scene = grass;
		ctx->track.segments[i].scene = bushes_rnd_tab[rand() % 5];

	for (int i = nb_segments_added / 10; i < nb_segments_added * 3 / 10;
	     i += 8)
		ctx->track.segments[i].scene = oak_forest_1;
	for (int i = nb_segments_added / 10 + 4; i < nb_segments_added * 3 / 10;
	     i += 8)
		ctx->track.segments[i].scene = oak_forest_2;

	for (int i = nb_segments_added * 3 / 10; i < nb_segments_added * 5 / 10;
	     i += 32)
		ctx->track.segments[i].scene = barn_n_well;

	for (int i = nb_segments_added * 5 / 10; i < nb_segments_added * 7 / 10;
	     i += 5)
		ctx->track.segments[i].scene = fence_n_bush;

	for (int i = nb_segments_added * 7 / 10; i < nb_segments_added * 9 / 10;
	     i += 16)
		ctx->track.segments[i].scene = windmill_n_grass;

	for (int i = nb_segments_added * 9 / 10; i < nb_segments_added; i += 4)
		// ctx->track.segments[i].scene = bushes_rnd_1;
		ctx->track.segments[i].scene = bushes_rnd_tab[rand() % 5];
	// ctx->track.segments[i].scene = grass;


	// ctx->track.segments[0].scene = start_lane;


	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_grass_bright;
	ctx->track.cds[0].dark = &cd_grass_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	ctx->track.lane_type = LANE_TYPE_HALF;

	return 0;
}

int track_build(struct game_context *ctx)
{

	int tid = ctx->track.track_selected;
	ctx->track.nb_segments = track_build_tab[tid].nb_segment;

	///////////////////////////////////
	// TODO: put this in a function elsewhere
	int player_lane = NB_AI_CARS % ctx->track.lanes;
	ctx->pcar.player_x = ai_lane_to_posx(player_lane, ctx->track.lanes);
	ctx->pcar.player_segment =
		ctx->track.nb_segments -
		(NB_AI_CARS / ctx->track.lanes) * AI_SEGMENTS_SPACING - 6;
	ctx->pcar.player_segment_prev = ctx->pcar.player_segment;
	ctx->pcar.position = ctx->pcar.player_segment * ROAD_SEGMENT_LENGTH;
	ctx->pcar.player_distance_ran =
		(ctx->pcar.player_segment - ctx->track.nb_segments) *
			ROAD_SEGMENT_LENGTH -
		1;

	SDL_Log("PLAYER player_distance_ran = %d\n",
		ctx->pcar.player_distance_ran);

	///////////////////////////////////

	ctx->track.segments = calloc((size_t)ctx->track.nb_segments,
				     sizeof(*ctx->track.segments));
	if (!ctx->track.segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}

	switch (tid) {
	case TRACK_DIJON:
		track_build_dijon(ctx);
		break;
	case TRACK_SPEEDWAY:
		track_build_speedway(ctx);
		break;
	case TRACK_FORK:
		track_build_fork(ctx);
		break;
	}

	return 0;
}

int track_unload(struct game_context *ctx)
{

	struct scene_seg_desc *scene_desc_freed[50] = {};
	int idx = 0;


	for (int i = 0; i < ctx->track.nb_segments; i++) {
		int desc_found = 0;
		for (int j = 0; j < 50; j++) {
			if (ctx->track.segments[i].scene ==
			    scene_desc_freed[j]) {
				desc_found = 1;
				break;
			}
		}

		if (!desc_found) {
			scene_desc_freed[idx] = ctx->track.segments[i].scene;
			idx++;
			free(ctx->track.segments[i].scene);
		}
	}

	free(ctx->track.segments);
	ctx->track.segments = NULL;

	return 0;
}
