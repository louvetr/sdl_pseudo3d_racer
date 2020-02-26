#include "common.h"

// TODO: use realloc at each sector addition instead counting total nb sectors
// in advance

static int main_build_track_test(struct game_context *ctx)
{
	int nb_segments_added = 0;

	ctx->nb_segments = 450 + 75;
	//ctx->nb_segments = 1350;
	// ctx->nb_segments = 1050;
	// ctx->nb_segments = 300;

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
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  //HILL_UP_LOW,
							  HILL_NONE,
							  CURVE_NONE);

		// 150 left --- 225
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_MEDIUM,
							  SECTOR_LENGTH_MEDIUM,
							  SECTOR_LENGTH_MEDIUM,
							  HILL_NONE,
							  CURVE_LEFT_EASY);

		// 75 straight --- 300
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  HILL_UP_MEDIUM,
							  CURVE_NONE);

		// 150 right --- 450
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_MEDIUM,
							  SECTOR_LENGTH_MEDIUM,
							  SECTOR_LENGTH_MEDIUM,
							  HILL_NONE,
							  CURVE_RIGHT_MEDIUM);

		// 75 straight --- 525
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  HILL_UP_HIGH,
							  CURVE_NONE);

		// 300 left --- 825
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_LONG,
							  SECTOR_LENGTH_LONG,
							  SECTOR_LENGTH_LONG,
							  HILL_NONE,
							  CURVE_LEFT_EASY);


		// 75 straight --- 900
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_SHORT,
							  HILL_DOWN_HIGH,
							  CURVE_NONE);

		// 150 right --- 1050
		nb_segments_added += road_add_sector(ctx->segments,
							  nb_segments_added,
							  SECTOR_LENGTH_SHORT,
							  SECTOR_LENGTH_LONG,
							  SECTOR_LENGTH_SHORT,
							  HILL_DOWN_MEDIUM,
							  CURVE_RIGHT_HARD);
	*/
	/*
	// 150 straight --- 1050
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	// 150 straight --- 1050
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);

	// 150 straight --- 150
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_LOW,
						  CURVE_NONE);

	// 150 straight --- 300
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_LOW,
						  CURVE_LEFT_EASY);

	// 150 straight --- 450
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_MEDIUM,
						  CURVE_NONE);

	// 150 straight --- 600
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_NONE);

	// 150 straight --- 750
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_MEDIUM,
						  CURVE_NONE);

	// 150 straight --- 900
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_RIGHT_MEDIUM);

	// 150 straight --- 1050
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	*/

	// 150 straight --- 150
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	// 75 hill H --- 225
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_HIGH,
						  CURVE_NONE);
	// 75 hill D --- 300
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_HIGH,
						  CURVE_NONE);

	// 75 hill H --- 375
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_SLIGHT,
						  CURVE_NONE);

	// 75 hill D --- 450
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_SLIGHT,
						  CURVE_NONE);
	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

	return 0;
}


static int main_build_track_1(struct game_context *ctx)
{
	int nb_segments_added = 0;

	ctx->nb_segments = 2325;


	ctx->segments = calloc(ctx->nb_segments, sizeof(*ctx->segments));
	if (!ctx->segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}


	//A 150 straight --- 150
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	//B 150 hill H --- 300
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//C 150 hill UP M --- 450    y = 60
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_HIGH,
						  CURVE_NONE);

	//D 300 left --- 750     y = +100
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_UP_MEDIUM,
						  CURVE_RIGHT_MEDIUM);

	//E 75 straight --- 825
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_NONE,
						  CURVE_NONE);

	//F 150 straight down --- 975
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//G 150 straight down --- 1125   y = 60
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_NONE);

	//H 150 left down --- 1275    y = 20 
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_LEFT_MEDIUM);

	//I 150 straight --- 1425  y = 80
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_HIGH,
						  CURVE_NONE);

	//J 300 right --- 1725  y = 40
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_DOWN_MEDIUM,
						  CURVE_RIGHT_HARD);

	//I 150 straight --- 1800  y = 00
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_DOWN_MEDIUM,
						  CURVE_NONE);

	//K  150 roller coaster --- 1950 
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_LOW,
						  CURVE_NONE);
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_LOW,
						  CURVE_NONE);

	//K'  150 roller coaster --- 2100
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_LOW,
						  CURVE_NONE);
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_LOW,
						  CURVE_NONE);

	//K''  150 roller coaster --- 2250
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_UP_LOW,
						  CURVE_NONE);
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_DOWN_LOW,
						  CURVE_NONE);

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

	return 0;
}


int track_build_try_turns(struct game_context *ctx)
{
	int nb_segments_added = 0;

	ctx->nb_segments = 575;


	ctx->segments = calloc(ctx->nb_segments, sizeof(*ctx->segments));
	if (!ctx->segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}


	//A 150 straight --- 150
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_NONE);
	
	//B 150 hill H --- 300
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_SHORT,
						  HILL_NONE,
						  CURVE_RIGHT_HARD);

	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_RIGHT_HARD);

	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_SHORT,
						  HILL_NONE,
						  CURVE_RIGHT_HARD);

	//B 150 hill H --- 600
	/*nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//B 150 hill H --- 600
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_RIGHT_EASY);*/


	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

	return 0;

}


// DP track
int track_build(struct game_context *ctx)
{
	int nb_segments_added = 0;

	//ctx->nb_segments = 2750;
	ctx->nb_segments = 2450;

	ctx->segments = calloc(ctx->nb_segments, sizeof(*ctx->segments));
	if (!ctx->segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}


	//A: 300 --- 300 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_NONE);
	
	//B: 175 --- 475 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//C: 200 --- 675 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_LOW,
						  CURVE_LEFT_EASY);

	//D: 175 --- 825 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_LEFT_HARD);    

	//E: 300 --- 1125 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_UP_HIGH,
						  CURVE_NONE);

	//F: 200 --- 1325 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//G: 300 --- 1625 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_DOWN_HIGH,
						  CURVE_NONE);

	//H: 175 --- 1800 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_SHORT,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_LEFT_HARD);

	//I: 150 --- 1950 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_MEDIUM,
						  HILL_UP_MEDIUM,
						  CURVE_RIGHT_MEDIUM);

	//J: 175 --- 2125 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_MEDIUM,
						  SECTOR_LENGTH_SHORT,
						  HILL_NONE,
						  CURVE_RIGHT_MEDIUM);

	//K: 300 --- 2425 --- y = 0
	nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_DOWN_HIGH,
						  CURVE_NONE);

	//L: 300 --- 2725 --- y = 0
	/*nb_segments_added += road_add_sector(ctx->segments,
						  nb_segments_added,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  SECTOR_LENGTH_LONG,
						  HILL_NONE,
						  CURVE_NONE);*/

	ctx->track_length = ROAD_SEGMENT_LENGTH * ctx->nb_segments;

    SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	/////// add trees --- oak
	for(int i = 0; i < nb_segments_added / 3; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_oak;
	}
	for(int i = 10; i < nb_segments_added / 3 ; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_oak;
	}

	/////// add trees --- willow
	for(int i = nb_segments_added / 3; i < nb_segments_added * 2/ 3; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_willow;
	}
	for(int i = nb_segments_added / 3 + 10; i < nb_segments_added * 2/ 3 ; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_willow;
	}

	/////// add trees --- pine
	for(int i = nb_segments_added * 2 / 3; i < nb_segments_added; i+=20) {
		ctx->segments[i].sprite_desc.position = 1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_pine;
	}
	for(int i = nb_segments_added * 2 / 3 + 10; i < nb_segments_added; i+=20) {
		ctx->segments[i].sprite_desc.position = -1;
		ctx->segments[i].sprite_desc.t = &ctx->gfx.scene_tree_pine;
	}
	return 0;

}

