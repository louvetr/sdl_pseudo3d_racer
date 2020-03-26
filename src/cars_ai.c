#include "common.h"

/*static*/ float ai_lane_to_posx(size_t idx_lane, size_t nb_lanes)
{
	float pos_x;
	// x position in a [0,1] range
	pos_x = (float)idx_lane / (float)nb_lanes +
		1.f / ((float)nb_lanes * 2.f);
	// shift x position in a [-1,1] range
	return pos_x * 2.f - 1.f;
}


int logic_race_ai_cars(struct game_context *ctx)
{

	float max_speed;

	for (int i = 0; i < NB_AI_CARS; i++) {

		if (ctx->segments[ctx->ai_cars[i].segment].curve != 0)
			max_speed = ctx->ai_cars[i].speed_max_curve;
		else
			max_speed = ctx->ai_cars[i].speed_max_straight;

		if (ctx->ai_cars[i].speed < max_speed) {
			ctx->ai_cars[i].speed = inline_accelerate(
				max_speed, ctx->ai_cars[i].accel, ctx->dt);
		}

		ctx->ai_cars[i].pos_z =
			inline_increase(ctx->ai_cars[i].pos_z,
					(size_t)(ctx->dt * ctx->ai_cars[i].speed),
					ctx->track_length);

		/*ctx->ai_cars[i].segment =
			inline_get_segment_idx(ctx, ctx->ai_cars[i].pos_z);*/

		ctx->ai_cars[i].segment =
			((ctx->ai_cars[i].pos_z / ROAD_SEGMENT_LENGTH) %
			 ctx->nb_segments);

		ctx->ai_cars[i].pos_z_rest_percent =
			(float)(ctx->ai_cars[i].pos_z % ROAD_SEGMENT_LENGTH) /
			(float)ROAD_SEGMENT_LENGTH;
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////

int ai_car_init(struct game_context *ctx)
{

	for (size_t i = 0; i < NB_AI_CARS; i++) {

		ctx->ai_cars[i].lane = i % ctx->lanes;
		ctx->ai_cars[i].pos_x =
			ai_lane_to_posx(ctx->ai_cars[i].lane, ctx->lanes);


		ctx->ai_cars[i].segment =
			ctx->nb_segments - (i / ctx->lanes) * 5;
		ctx->ai_cars[i].pos_z =
			ctx->ai_cars[i].segment * ROAD_SEGMENT_LENGTH;

		/*ctx->ai_cars[i].pos_z = 0;
		ctx->ai_cars[i].segment =
			inline_get_segment_idx(ctx, ctx->ai_cars[i].pos_z);*/
		ctx->ai_cars[i].speed_max_straight =
			ctx->max_speed * (0.95f - (float)i * 0.025f);
		ctx->ai_cars[i].speed_max_curve =
			ctx->max_speed * (0.75f - (float)i * 0.025f);
		ctx->ai_cars[i].speed = 0.f;
		ctx->ai_cars[i].accel = ctx->ai_cars[i].speed_max_straight / 50;

		/*ctx->ai_cars[i].speed_max_straight =
		ctx->ai_cars[i].speed_max_straight * 0.05;
		ctx->ai_cars[i].speed_max_curve =
		ctx->ai_cars[i].speed_max_curve * 0.05;*/
	}
	return 0;
}