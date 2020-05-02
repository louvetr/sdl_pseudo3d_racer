#include "track.h"
#include "common.h"


static SDL_Rect hitbox_oak = {.x = 262, .y = 0, .w = 240, .h = 711};


static struct scene_sprite_desc *
create_scene_sprite_desc(struct texture *t, float position, SDL_Rect *hitbox)
{
	struct scene_sprite_desc *sprite_desc =
		calloc(1, sizeof(struct scene_sprite_desc));
	if (!sprite_desc)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);
	sprite_desc->position = position;
	sprite_desc->t = t;
	sprite_desc->hitbox = hitbox;

	if (position < 0)
		sprite_desc->flip = SDL_FLIP_HORIZONTAL;
	else
		sprite_desc->flip = SDL_FLIP_NONE;

	return sprite_desc;
}


// TODO: use realloc at each sector addition instead counting total nb sectors
// in advance


// DP track
int track_build(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// ctx->nb_segments = 2750;
	// ctx->nb_segments = 2450;
	ctx->nb_segments = 2510;
	// ctx->nb_segments = 2600;

	///////////////////////////////////
	// TODO: put this in a function elsewhere
	// ctx->player_segment = ctx->nb_segments - 30;

	// ctx->position = ctx->player_segment * ROAD_SEGMENT_LENGTH;

	int player_lane = NB_AI_CARS % ctx->lanes;
	// ctx->position =
	ctx->player_x = ai_lane_to_posx(player_lane, ctx->lanes);

	ctx->player_segment = ctx->nb_segments -
			      (NB_AI_CARS / ctx->lanes) * AI_SEGMENTS_SPACING -
			      6;
	ctx->player_segment_prev = ctx->player_segment;
	ctx->position = ctx->player_segment * ROAD_SEGMENT_LENGTH;
	ctx->player_distance_ran =
		(ctx->player_segment - ctx->nb_segments) * ROAD_SEGMENT_LENGTH -
		1;

	SDL_Log("PLAYER player_distance_ran = %d\n", ctx->player_distance_ran);

	///////////////////////////////////

	ctx->segments =
		calloc((size_t)ctx->nb_segments, sizeof(*ctx->segments));
	if (!ctx->segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}

	for (int i = 0; i < NB_SECTOR_DIJON; i++) {
		nb_segments_added += road_add_sector(
			ctx->segments,
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

	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	//////////////////////////////////////////////////////////////

	struct scene_sprite_desc *oak_desc_p1 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 1, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p2 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 2, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p3 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 3, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p4 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 4, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p5 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 5, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p6 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 6, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_p7 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, 7, &hitbox_oak);

	struct scene_sprite_desc *oak_desc_m1 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -1, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m2 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -2, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m3 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -3, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m4 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -4, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m5 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -5, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m6 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -6, &hitbox_oak);
	struct scene_sprite_desc *oak_desc_m7 = create_scene_sprite_desc(
		&ctx->gfx.scene_tree_oak, -7, &hitbox_oak);


	struct scene_sprite_desc *grass_desc_p1 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, 1.5, NULL);
	struct scene_sprite_desc *grass_desc_p2 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, 3, NULL);
	struct scene_sprite_desc *grass_desc_p3 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, 4.5, NULL);
	struct scene_sprite_desc *grass_desc_m1 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, -1.5, NULL);
	struct scene_sprite_desc *grass_desc_m2 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, -3, NULL);
	struct scene_sprite_desc *grass_desc_m3 =
		create_scene_sprite_desc(&ctx->gfx.scene_grass, -4.5, NULL);

	struct scene_sprite_desc *fence_desc_p1 = create_scene_sprite_desc(
		&ctx->gfx.scene_fence, 1.5, &hitbox_oak);
	struct scene_sprite_desc *fence_desc_m1 = create_scene_sprite_desc(
		&ctx->gfx.scene_fence, -1.5, &hitbox_oak);

	struct scene_sprite_desc *windmill_desc_p1 = create_scene_sprite_desc(
		&ctx->gfx.scene_windmill, 2, &hitbox_oak);
	struct scene_sprite_desc *bush_desc_m1 = create_scene_sprite_desc(
		&ctx->gfx.scene_bush, -1.5, &hitbox_oak);


	struct scene_sprite_desc *cabin_desc_p1 =
		create_scene_sprite_desc(&ctx->gfx.scene_cabin, 6, &hitbox_oak);


	/////////////////////////////////////////////////////////

	struct scene_segment_desc *seg_oaks_forest_1 =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_oaks_forest_1)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_oaks_forest_1->nb_sprites = 8;
	seg_oaks_forest_1->sprite =
		calloc((size_t)seg_oaks_forest_1->nb_sprites,
		       sizeof(struct scene_sprite_desc *));

	seg_oaks_forest_1->sprite[0] = oak_desc_p1;
	seg_oaks_forest_1->sprite[1] = oak_desc_p3;
	seg_oaks_forest_1->sprite[2] = oak_desc_p5;
	seg_oaks_forest_1->sprite[3] = oak_desc_p7;
	seg_oaks_forest_1->sprite[4] = oak_desc_m1;
	seg_oaks_forest_1->sprite[5] = oak_desc_m3;
	seg_oaks_forest_1->sprite[6] = oak_desc_m5;
	seg_oaks_forest_1->sprite[7] = oak_desc_m7;

	struct scene_segment_desc *seg_oaks_forest_2 =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_oaks_forest_2)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_oaks_forest_2->nb_sprites = 6;
	seg_oaks_forest_2->sprite =
		calloc((size_t)seg_oaks_forest_2->nb_sprites,
		       sizeof(struct scene_sprite_desc *));

	seg_oaks_forest_2->sprite[0] = oak_desc_m2;
	seg_oaks_forest_2->sprite[1] = oak_desc_m4;
	seg_oaks_forest_2->sprite[2] = oak_desc_m6;
	seg_oaks_forest_2->sprite[3] = oak_desc_p2;
	seg_oaks_forest_2->sprite[4] = oak_desc_p4;
	seg_oaks_forest_2->sprite[5] = oak_desc_p6;


	struct scene_segment_desc *seg_grass =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_grass)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_grass->nb_sprites = 6;
	seg_grass->sprite = calloc((size_t)seg_grass->nb_sprites,
				   sizeof(struct scene_sprite_desc *));

	seg_grass->sprite[0] = grass_desc_p1;
	seg_grass->sprite[1] = grass_desc_p2;
	seg_grass->sprite[2] = grass_desc_p3;
	seg_grass->sprite[3] = grass_desc_m1;
	seg_grass->sprite[4] = grass_desc_m2;
	seg_grass->sprite[5] = grass_desc_m3;


	struct scene_segment_desc *seg_fence =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_fence)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_fence->nb_sprites = 2;
	seg_fence->sprite = calloc((size_t)seg_fence->nb_sprites,
				   sizeof(struct scene_sprite_desc *));

	seg_fence->sprite[0] = fence_desc_p1;
	seg_fence->sprite[1] = fence_desc_m1;


	struct scene_segment_desc *seg_bush_mill =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_bush_mill)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_bush_mill->nb_sprites = 2;
	seg_bush_mill->sprite = calloc((size_t)seg_bush_mill->nb_sprites,
				       sizeof(struct scene_sprite_desc *));

	seg_bush_mill->sprite[0] = windmill_desc_p1;
	seg_bush_mill->sprite[1] = bush_desc_m1;


	struct scene_segment_desc *seg_cabin =
		calloc(1, sizeof(struct scene_segment_desc));
	if (!seg_cabin)
		SDL_Log("[%s:%d] calloc\n", __func__, __LINE__);

	seg_cabin->nb_sprites = 1;
	seg_cabin->sprite = calloc((size_t)seg_cabin->nb_sprites,
				   sizeof(struct scene_sprite_desc *));

	seg_cabin->sprite[0] = cabin_desc_p1;

	/////////////////////////////////////////////////////////////////////


	for (int i = 0; i < nb_segments_added / 4; i += 4)
		ctx->segments[i].scene = seg_grass;

	for (int i = nb_segments_added / 4; i < nb_segments_added / 2; i += 8)
		ctx->segments[i].scene = seg_oaks_forest_1;
	for (int i = nb_segments_added / 4 + 4; i < nb_segments_added / 2;
	     i += 8)
		ctx->segments[i].scene = seg_oaks_forest_2;

	for (int i = nb_segments_added / 2; i < nb_segments_added * 3 / 4;
	     i += 6)
		ctx->segments[i].scene = seg_fence;

	for (int i = nb_segments_added * 3 / 4; i < nb_segments_added; i += 20)
		ctx->segments[i].scene = seg_bush_mill;

		/*for(int i = 0; i < nb_segments_added; i+=30)
			ctx->segments[i].scene = seg_cabin;*/

		/*for (int i = 0; i < nb_segments_added; i += 8)
			ctx->segments[i].scene = seg_oaks_forest_1;
		for (int i = 4; i < nb_segments_added; i += 8)
			ctx->segments[i].scene = seg_oaks_forest_2;*/

#if 0
	/////// add trees --- oak
	for(int i = 0; i < nb_segments_added / 3; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_oak;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_grass;
	}
	for(int i = 10; i < nb_segments_added / 3 ; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_oak;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_bush;
	}

	/////// add trees --- willow
	for(int i = nb_segments_added / 3; i < nb_segments_added * 2/ 3; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_willow;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_fence;
	}
	for(int i = nb_segments_added / 3 + 10; i < nb_segments_added * 2/ 3 ; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_willow;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_barn;
	}

	/////// add trees --- pine
	for(int i = nb_segments_added * 2 / 3; i < nb_segments_added; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_pine;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_pine;
	}
	for(int i = nb_segments_added * 2 / 3 + 10; i < nb_segments_added; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		//ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_pine;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_windmill;
	}


	/*for(int i = 0; i < nb_segments_added; i+=40) {
		ctx->segments[i].sprite_desc.position = 4.f;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_cabin;
	}*/

#endif

	/*for(int i = 0; i < nb_segments_added; i++)
		SDL_Log("segment[%d].curve = %f\n", i,
	   ctx->segments[i].curve);*/

	return 0;
}
