#include "main.h"

#define AHEAD_SEG_DISTANCE 30

enum ai_car_available_lane {
	AI_NO_CAR_AHEAD = 0x00,
	AI_CAR_AHEAD = 0x01,
	AI_CAR_LEFT = 0x02,
	AI_CAR_RIGHT = 0x04
};

/*
static const int lane____ = AI_NO_CAR_AHEAD;
static const int lane___r = AI_CAR_RIGHT;
static const int lane__s_ = AI_CAR_AHEAD;
static const int lane__sr = AI_CAR_AHEAD | AI_CAR_RIGHT;
static const int lane_l__ = AI_CAR_LEFT;
static const int lane_l_r = AI_CAR_LEFT | AI_CAR_RIGHT;
static const int lane_ls_ = AI_CAR_LEFT | AI_CAR_AHEAD;
static const int lane_lsr = AI_CAR_LEFT | AI_CAR_AHEAD | AI_CAR_RIGHT;
*/


#define lane____ AI_NO_CAR_AHEAD
#define lane___r AI_CAR_RIGHT
#define lane__s_ AI_CAR_AHEAD
#define lane__sr AI_CAR_AHEAD | AI_CAR_RIGHT
#define lane_l__ AI_CAR_LEFT
#define lane_l_r AI_CAR_LEFT | AI_CAR_RIGHT
#define lane_ls_ AI_CAR_LEFT | AI_CAR_AHEAD
#define lane_lsr AI_CAR_LEFT | AI_CAR_AHEAD | AI_CAR_RIGHT


static int ai_check_lane_collision(struct ai_car_info *car_info, int lane)
{
	if (car_info->lane == lane ||
	    ((car_info->state == AI_CAR_STATE_SWITCHING_LANE_LEFT ||
	      car_info->state == AI_CAR_STATE_SWITCHING_LANE_RIGHT) &&
	     car_info->dest_lane == lane))
		return 1;
	else
		return 0;
}

static enum ai_car_available_lane
ai_is_there_a_car_ahead(struct game_context *ctx,
			int ai_car_idx,
			int ai_car_lane,
			int ai_car_seg_idx,
			int *closest_car_idx)
{
	int ret = AI_NO_CAR_AHEAD;
	int dist_with_closest_car = ctx->track.nb_segments;
	int car_detected_on_left_lane = 0;
	int car_detected_on_right_lane = 0;
	*closest_car_idx = -1;

	// boarder lanes are considered as occupied by an ai car
	if (ai_car_lane == 0)
		car_detected_on_left_lane = 1;
	if (ai_car_lane == ctx->track.lanes - 1)
		car_detected_on_right_lane = 1;

	for (int i = 0; i < NB_AI_CARS; i++) {

		// ignore current car
		if (i == ai_car_idx)
			continue;

		// ignore cars on different lane
		/*if (ctx->ai_cars[i].lane != ai_car_lane)
			continue;*/

		/*if (ctx->ai_cars[i].speed_max_straight >=
		    ctx->pcar.max_speed * 0.88f)
			SDL_Log("[%s] idx = %d is first !!!\n", __func__, i);*/

		if (ai_car_seg_idx <
		    ctx->track.nb_segments - AHEAD_SEG_DISTANCE) {
			int dst = ctx->ai_cars[i].segment - ai_car_seg_idx;

			if (dst < 0 || dst > AHEAD_SEG_DISTANCE)
				continue;

			// check if car ahead
			if (ctx->ai_cars[i].lane == ai_car_lane
			    /*ai_check_lane_collision(&ctx->ai_cars[i],
						    ai_car_lane)*/
			    &&
			    // dst <= AHEAD_SEG_DISTANCE &&
			    dst < dist_with_closest_car) {
				dist_with_closest_car = dst;
				*closest_car_idx = i;
			}

			// check if there is a car on left lane
			if (!car_detected_on_left_lane &&
			    // ctx->ai_cars[i].lane == ai_car_lane - 1
			    ai_check_lane_collision(&ctx->ai_cars[i],
						    ai_car_lane - 1)) {
				car_detected_on_left_lane = 1;
			}

			// check if there is a car on right lane
			if (!car_detected_on_right_lane &&
			    // ctx->ai_cars[i].lane == ai_car_lane + 1
			    ai_check_lane_collision(&ctx->ai_cars[i],
						    ai_car_lane + 1)) {
				car_detected_on_right_lane = 1;
			}

		} else {
			// case if car to check is close before the start lane
			int nb_seg_to_start =
				ctx->track.nb_segments - ai_car_seg_idx;
			if (ctx->ai_cars[i].segment > ai_car_seg_idx) {

				int dst = ctx->ai_cars[i].segment -
					  ai_car_seg_idx;

				if (dst < 0 || dst > AHEAD_SEG_DISTANCE)
					continue;

				// check if car ahead
				if (ctx->ai_cars[i].lane == ai_car_lane
				    /*ai_check_lane_collision(
					    &ctx->ai_cars[i],
					    ai_car_lane)*/
				    && dst <= AHEAD_SEG_DISTANCE &&
				    dst < dist_with_closest_car) {
					dist_with_closest_car = dst;
					*closest_car_idx = i;
				}

				// check if there is a car on left lane
				if (!car_detected_on_left_lane &&
				    // ctx->ai_cars[i].lane == ai_car_lane - 1
				    ai_check_lane_collision(&ctx->ai_cars[i],
							    ai_car_lane - 1)) {
					car_detected_on_left_lane = 1;
				}

				// check if there is a car on right lane
				if (!car_detected_on_right_lane &&
				    // ctx->ai_cars[i].lane == ai_car_lane + 1
				    ai_check_lane_collision(&ctx->ai_cars[i],
							    ai_car_lane + 1)) {
					car_detected_on_right_lane = 1;
				}


			} else {
				if (ctx->ai_cars[i].segment <=
				    AHEAD_SEG_DISTANCE - nb_seg_to_start) {

					int dst = ctx->ai_cars[i].segment +
						  nb_seg_to_start;

					if (dst < 0 || dst > AHEAD_SEG_DISTANCE)
						continue;

					// check if car ahead
					if (ctx->ai_cars[i].lane == ai_car_lane
					    /*ai_check_lane_collision(
						    &ctx->ai_cars[i],
						    ai_car_lane)*/

					    /*&& dst <= AHEAD_SEG_DISTANCE*/
					    && dst < dist_with_closest_car) {
						dist_with_closest_car = dst;
						*closest_car_idx = i;
					}

					// check if there is a car on left lane
					if (!car_detected_on_left_lane &&
					    /*ctx->ai_cars[i].lane ==
						    ai_car_lane - 1*/
					    ai_check_lane_collision(
						    &ctx->ai_cars[i],
						    ai_car_lane - 1)

					) {
						car_detected_on_left_lane = 1;
					}

					// check if there is a car on right lane
					if (!car_detected_on_right_lane &&
					    /*ctx->ai_cars[i].lane ==
						    ai_car_lane + 1*/
					    ai_check_lane_collision(
						    &ctx->ai_cars[i],
						    ai_car_lane + 1)) {
						car_detected_on_right_lane = 1;
					}
				}
			}
		}
	}

	if (car_detected_on_left_lane)
		ret += AI_CAR_LEFT;
	if (car_detected_on_right_lane)
		ret += AI_CAR_RIGHT;
	if (*closest_car_idx >= 0) {
		ret += AI_CAR_AHEAD;
	}

	return ret;
}


/*static*/ float ai_lane_to_posx(int idx_lane, int nb_lanes)
{
	float pos_x;
	// x position in a [0,1] range
	if (idx_lane > 0) {
		pos_x = (float)idx_lane / (float)nb_lanes +
			1.f / ((float)nb_lanes * 2.f);
		// shift x position in a [-1,1] range
		return pos_x * 2.f - 1.f;
	} else {
		pos_x = (float)(nb_lanes - 1) / (float)nb_lanes +
			1.f / ((float)nb_lanes * 2.f);
		// shift x position in a [-1,1] range
		return -(pos_x * 2.f - 1.f) +
		       2.f / (2.f + 5.f * (float)nb_lanes);
	}
}


int logic_race_ai_cars_speed(struct game_context *ctx)
{

	float max_speed;

	static unsigned int cpt = 0;
	cpt++;

	for (int i = 0; i < NB_AI_CARS; i++) {

		if ((ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW ||
		     ctx->ai_cars[i].state ==
			     AI_CAR_STATE_SPEED_BEHIND_PLAYER) &&
		    ctx->ai_cars[i].speed_slow_straight <
			    ctx->ai_cars[i].speed_max_straight) {

			if (ctx->track.segments[ctx->ai_cars[i].segment]
				    .curve != 0)
				max_speed = ctx->ai_cars[i]
						    .speed_slow_curve /** .9f*/;
			else
				max_speed = ctx->ai_cars[i].speed_slow_straight;
		} else {
			if (ctx->track.segments[ctx->ai_cars[i].segment]
				    .curve != 0)
				max_speed = ctx->ai_cars[i]
						    .speed_max_curve /** .9f*/;
			else
				max_speed = ctx->ai_cars[i].speed_max_straight;
		}

		int step = (int)(ctx->dt * max_speed);
		ctx->ai_cars[i].distance += step;

		ctx->ai_cars[i].pos_z = inline_increase(
			ctx->ai_cars[i].pos_z, step, ctx->track.track_length);

		ctx->ai_cars[i].segment_prev2 =
			ctx->ai_cars[i].segment_prev;
		ctx->ai_cars[i].segment_prev = ctx->ai_cars[i].segment;
		ctx->ai_cars[i].segment =
			((ctx->ai_cars[i].pos_z / ROAD_SEGMENT_LENGTH) %
			 ctx->track.nb_segments);

		ctx->ai_cars[i].pos_z_rest_percent =
			(float)(ctx->ai_cars[i].pos_z % ROAD_SEGMENT_LENGTH) /
			(float)ROAD_SEGMENT_LENGTH;

		float dx = (ctx->dt * max_speed) / 3000 / 10;

		if (ctx->ai_cars[i].state ==
		    AI_CAR_STATE_SWITCHING_LANE_RIGHT) {
			ctx->ai_cars[i].pos_x += dx;
		} else if (ctx->ai_cars[i].state ==
			   AI_CAR_STATE_SWITCHING_LANE_LEFT) {
			ctx->ai_cars[i].pos_x -= dx;
		}
	}

	return 0;
}


int logic_race_ai_cars_state(struct game_context *ctx)
{
	int lane_status;
	int can_switch_lane = 0;
	static int cpt = 0;
	cpt++;

	for (int i = 0; i < NB_AI_CARS; i++) {

		// check if lane switching is done
		if (ctx->ai_cars[i].state == AI_CAR_STATE_SWITCHING_LANE_LEFT) {
			if (ctx->ai_cars[i].pos_x <= ctx->ai_cars[i].dest_x) {
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
				ctx->ai_cars[i].lane--;
			}
		} else if (ctx->ai_cars[i].state ==
			   AI_CAR_STATE_SWITCHING_LANE_RIGHT) {
			if (ctx->ai_cars[i].pos_x >= ctx->ai_cars[i].dest_x) {
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
				ctx->ai_cars[i].lane++;
			}
		} else if (ctx->ai_cars[i].state ==
			   AI_CAR_STATE_SPEED_BEHIND_PLAYER) {

			if (ctx->ai_cars[i].behind_player_frames > FPS)
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_SLOW;

			ctx->ai_cars[i].behind_player_frames++;
			continue;
		}

		// change state according lane status
		lane_status = ai_is_there_a_car_ahead(
			ctx,
			i,
			ctx->ai_cars[i].lane,
			ctx->ai_cars[i].segment,
			&ctx->ai_cars[i].closest_car_idx);

		// possibly change lanes every 5 seconds
		if ((cpt + i) % 150 == 0)
			can_switch_lane = 1;

		switch (lane_status) {
		case lane____:
			if (ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW) {
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
			} else if (can_switch_lane &&
				   ctx->ai_cars[i].state ==
					   AI_CAR_STATE_SPEED_FULL) {
				int rnd = rand_interval(0, 2);
				if (rnd == 1 && ctx->ai_cars[i].lane > 0) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SWITCHING_LANE_LEFT;
					ctx->ai_cars[i].dest_x =
						ai_lane_to_posx(
							ctx->ai_cars[i].lane -
								1,
							ctx->track.lanes);
					ctx->ai_cars[i].dest_lane =
						ctx->ai_cars[i].lane - 1;
				} else if (rnd == 2 &&
					   ctx->ai_cars[i].lane <
						   ctx->track.lanes - 1) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SWITCHING_LANE_RIGHT;
					ctx->ai_cars[i].dest_x =
						ai_lane_to_posx(
							ctx->ai_cars[i].lane +
								1,
							ctx->track.lanes);
					ctx->ai_cars[i].dest_lane =
						ctx->ai_cars[i].lane + 1;
				}
			}
			break;
		case lane___r:
			if (ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW) {
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
			} else if (can_switch_lane &&
				   ctx->ai_cars[i].state ==
					   AI_CAR_STATE_SPEED_FULL) {
				if (rand_interval(0, 1) == 0 &&
				    ctx->ai_cars[i].lane > 0) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SWITCHING_LANE_LEFT;
					ctx->ai_cars[i].dest_x =
						ai_lane_to_posx(
							ctx->ai_cars[i].lane -
								1,
							ctx->track.lanes);
					ctx->ai_cars[i].dest_lane =
						ctx->ai_cars[i].lane - 1;
				}
			}
			break;
		case lane__s_:
			if (rand_interval(0, 1) == 0 &&
			    ctx->ai_cars[i].lane < ctx->track.lanes - 1) {
				ctx->ai_cars[i].state =
					AI_CAR_STATE_SWITCHING_LANE_RIGHT;
				ctx->ai_cars[i].dest_x = ai_lane_to_posx(
					ctx->ai_cars[i].lane + 1,
					ctx->track.lanes);
				ctx->ai_cars[i].dest_lane =
					ctx->ai_cars[i].lane + 1;
			} else if (ctx->ai_cars[i].lane > 0) {
				ctx->ai_cars[i].state =
					AI_CAR_STATE_SWITCHING_LANE_LEFT;
				ctx->ai_cars[i].dest_x = ai_lane_to_posx(
					ctx->ai_cars[i].lane - 1,
					ctx->track.lanes);
				ctx->ai_cars[i].dest_lane =
					ctx->ai_cars[i].lane - 1;
			}
			break;
		case lane__sr:
			ctx->ai_cars[i].state =
				AI_CAR_STATE_SWITCHING_LANE_LEFT;
			ctx->ai_cars[i].dest_x = ai_lane_to_posx(
				ctx->ai_cars[i].lane - 1, ctx->track.lanes);
			ctx->ai_cars[i].dest_lane = ctx->ai_cars[i].lane - 1;
			break;
		case lane_l__:
			if (ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW) {
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
			} else if (can_switch_lane &&
				   ctx->ai_cars[i].state ==
					   AI_CAR_STATE_SPEED_FULL) {
				if (rand_interval(0, 1) == 0 &&
				    ctx->ai_cars[i].lane <
					    ctx->track.lanes - 1) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SWITCHING_LANE_RIGHT;
					ctx->ai_cars[i].dest_x =
						ai_lane_to_posx(
							ctx->ai_cars[i].lane +
								1,
							ctx->track.lanes);
					ctx->ai_cars[i].dest_lane =
						ctx->ai_cars[i].lane + 1;
				}
			}
			break;
		case lane_l_r:
			if (ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW)
				ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
			break;
		case lane_ls_:
			ctx->ai_cars[i].state =
				AI_CAR_STATE_SWITCHING_LANE_RIGHT;
			ctx->ai_cars[i].dest_x = ai_lane_to_posx(
				ctx->ai_cars[i].lane + 1, ctx->track.lanes);
			break;
		case lane_lsr:
			ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_SLOW;
			break;
		}

		if (ctx->ai_cars[i].state == AI_CAR_STATE_SPEED_SLOW) {
			if (ctx->ai_cars[ctx->ai_cars[i].closest_car_idx]
				    .speed_max_straight >
			    ctx->ai_cars[ctx->ai_cars[i].closest_car_idx]
				    .speed_slow_straight)
				ctx->ai_cars[i].speed_slow_straight =
					ctx->ai_cars[ctx->ai_cars[i]
							     .closest_car_idx]
						.speed_slow_straight;
			else
				ctx->ai_cars[i].speed_slow_straight =
					ctx->ai_cars[ctx->ai_cars[i]
							     .closest_car_idx]
						.speed_max_straight;

			if (ctx->ai_cars[ctx->ai_cars[i].closest_car_idx]
				    .speed_max_curve >
			    ctx->ai_cars[ctx->ai_cars[i].closest_car_idx]
				    .speed_slow_curve)
				ctx->ai_cars[i].speed_slow_curve =
					ctx->ai_cars[ctx->ai_cars[i]
							     .closest_car_idx]
						.speed_slow_curve;
			else
				ctx->ai_cars[i].speed_slow_curve =
					ctx->ai_cars[ctx->ai_cars[i]
							     .closest_car_idx]
						.speed_max_curve;
		}
	}

	return 0;
}


int logic_race_ai_cars(struct game_context *ctx)
{
	int ret;

	ret = logic_race_ai_cars_state(ctx);
	ret = logic_race_ai_cars_speed(ctx);

	return ret;
}


///////////////////////////////////////////////////////////////////////////

int ai_car_init(struct game_context *ctx)
{

	for (int i = 0; i < NB_AI_CARS; i++) {

		ctx->ai_cars[i].lane = i % ctx->track.lanes;
		ctx->ai_cars[i].pos_x =
			ai_lane_to_posx(ctx->ai_cars[i].lane, ctx->track.lanes);

		ctx->ai_cars[i].segment_prev2 =
			ctx->ai_cars[i].segment_prev;
		ctx->ai_cars[i].segment_prev = ctx->ai_cars[i].segment;
		ctx->ai_cars[i].segment =
			ctx->track.nb_segments - 1 -
			(i / ctx->track.lanes) * AI_SEGMENTS_SPACING;

		ctx->ai_cars[i].pos_z =
			ctx->ai_cars[i].segment * ROAD_SEGMENT_LENGTH;

		ctx->ai_cars[i].distance =
			(ctx->ai_cars[i].segment - ctx->track.nb_segments) *
			ROAD_SEGMENT_LENGTH;

		ctx->ai_cars[i].speed_max_straight =
			ctx->pcar.max_speed * (.99f - (float)i * 0.01f);
		ctx->ai_cars[i].speed_max_curve =
			ctx->pcar.max_speed * (0.95f - (float)i * 0.01f);

		ctx->ai_cars[i].speed = 0.f;
		ctx->ai_cars[i].accel = ctx->ai_cars[i].speed_max_straight / 50;

		ctx->ai_cars[i].speed_slow_straight =
			ctx->ai_cars[i].speed_max_straight;
		ctx->ai_cars[i].speed_slow_curve =
			ctx->ai_cars[i].speed_max_curve;

		ctx->ai_cars[i].car_model = i % CAR_MODEL_LAST;
		ctx->ai_cars[i].sprite_idx = CAR_SPRITE_REAR;
		ctx->ai_cars[i].car_flip = SDL_FLIP_NONE;

		ctx->ai_cars[i].state = AI_CAR_STATE_SPEED_FULL;
		ctx->ai_cars[i].closest_car_idx = -1;
		ctx->ai_cars[i].dest_x = 0.f;

		// TODO: change the idx of each car randomly
		ctx->ai_cars[i].car_x_scale_coef =
			(float)ctx->display.screen_width * 2.f *
			ctx->display.scale_ai_car[ctx->ai_cars[i].car_model];
		ctx->ai_cars[i].ai_car_scale_coef =
			(float)ctx->display.screen_width * 2.f *
			ctx->display.scale_ai_car[ctx->ai_cars[i].car_model];

		/*SDL_Log("ctx->ai_cars[%d].distance = %d\n",
			i,
			ctx->ai_cars[i].distance);*/
	}

	// shuffle start grid 5 times
	for (int k = 0; k < 5; k++) {
		// shuffle the ai cars
		for (int i = 0; i < NB_AI_CARS; i++) {
			int j = i + rand() / (RAND_MAX / (NB_AI_CARS - i) + 1);

			int tmp_segment = ctx->ai_cars[j].segment;
			int tmp_pos_z = ctx->ai_cars[j].pos_z;
			float tmp_pos_x = ctx->ai_cars[j].pos_x;
			int tmp_distance = ctx->ai_cars[j].distance;
			enum car_model_type tmp_model =
				ctx->ai_cars[j].car_model;
			float car_x_scale_coef =
				ctx->ai_cars[j].car_x_scale_coef;
			float ai_car_scale_coef =
				ctx->ai_cars[j].ai_car_scale_coef;

			ctx->ai_cars[j].car_model = ctx->ai_cars[i].car_model;
			ctx->ai_cars[i].car_model = tmp_model;
			ctx->ai_cars[j].car_x_scale_coef =
				ctx->ai_cars[i].car_x_scale_coef;
			ctx->ai_cars[i].car_x_scale_coef = car_x_scale_coef;
			ctx->ai_cars[j].ai_car_scale_coef =
				ctx->ai_cars[i].ai_car_scale_coef;
			ctx->ai_cars[i].ai_car_scale_coef = ai_car_scale_coef;

			/* Let the 3 first cars have the best stats so they
			 * always are ahead */
			if (i < 3)
				continue;

			ctx->ai_cars[i].segment_prev2 =
				ctx->ai_cars[i].segment_prev;
			ctx->ai_cars[i].segment_prev = ctx->ai_cars[i].segment;
			ctx->ai_cars[j].segment = ctx->ai_cars[i].segment;
			ctx->ai_cars[i].segment = tmp_segment;

			ctx->ai_cars[j].pos_z = ctx->ai_cars[i].pos_z;
			ctx->ai_cars[i].pos_z = tmp_pos_z;

			ctx->ai_cars[j].distance = ctx->ai_cars[i].distance;
			ctx->ai_cars[i].distance = tmp_distance;

			ctx->ai_cars[j].pos_x = ctx->ai_cars[i].pos_x;
			ctx->ai_cars[i].pos_x = tmp_pos_x;

			// SDL_Log("[%s] switching #%d and #%d\n", __func__, i,
			// j);
		}
	}

	return 0;
}
