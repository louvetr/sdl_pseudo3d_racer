#include "track.h"
#include "main.h"



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
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}};




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


// DP track
int track_build(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// ctx->track.nb_segments = 2750;
	// ctx->track.nb_segments = 2450;
	// ctx->track.nb_segments = 2510;
	ctx->track.nb_segments = 2570;
	// ctx->track.nb_segments = 2600;

	///////////////////////////////////
	// TODO: put this in a function elsewhere
	// ctx->pcar.player_segment = ctx->track.nb_segments - 30;

	// ctx->pcar.position = ctx->pcar.player_segment * ROAD_SEGMENT_LENGTH;

	int player_lane = NB_AI_CARS % ctx->track.lanes;
	// ctx->pcar.position =
	ctx->pcar.player_x = ai_lane_to_posx(player_lane, ctx->track.lanes);

	ctx->pcar.player_segment = ctx->track.nb_segments -
			      (NB_AI_CARS / ctx->track.lanes) * AI_SEGMENTS_SPACING -
			      6;
	ctx->pcar.player_segment_prev = ctx->pcar.player_segment;
	ctx->pcar.position = ctx->pcar.player_segment * ROAD_SEGMENT_LENGTH;
	ctx->pcar.player_distance_ran =
		(ctx->pcar.player_segment - ctx->track.nb_segments) * ROAD_SEGMENT_LENGTH -
		1;

	SDL_Log("PLAYER player_distance_ran = %d\n", ctx->pcar.player_distance_ran);

	///////////////////////////////////

	ctx->track.segments =
		calloc((size_t)ctx->track.nb_segments, sizeof(*ctx->track.segments));
	if (!ctx->track.segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}

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

	return 0;
}
