#include "common.h"

#define NB_SEGMENT_CAR_COLLISION 5
#define NITRO_DURATION 5

static float COLLIONSION_SCENE_SHIFT = 0.5f;

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////

static int logic_set_player_sprite(struct game_context *ctx)
{
	switch (ctx->car_orientation_cur) {
	case PLAYER_SPRITE_HARD_LEFT:
		ctx->car_player_sprite_idx = CAR_SPRITE_RIGHT2;
		ctx->car_player_flip = SDL_FLIP_HORIZONTAL;
		break;
	case PLAYER_SPRITE_LIGHT_LEFT:
		ctx->car_player_sprite_idx = CAR_SPRITE_RIGHT1;
		ctx->car_player_flip = SDL_FLIP_HORIZONTAL;
		break;
	case PLAYER_SPRITE_STRAIGHT:
		ctx->car_player_sprite_idx = CAR_SPRITE_REAR;
		ctx->car_player_flip = SDL_FLIP_NONE;
		break;
	case PLAYER_SPRITE_LIGHT_RIGHT:
		ctx->car_player_sprite_idx = CAR_SPRITE_RIGHT1;
		ctx->car_player_flip = SDL_FLIP_NONE;
		break;
	case PLAYER_SPRITE_HARD_RIGHT:
		ctx->car_player_sprite_idx = CAR_SPRITE_RIGHT2;
		ctx->car_player_flip = SDL_FLIP_NONE;
		break;
	}

	return 0;
}


static int logic_race_check_collision_with_cars(struct game_context *ctx)
{
	int player_max_x = ctx->player_car_x_in_pixels +
			   (int)((float)ctx->gfx
					 .cars[ctx->car_player_model]
					      [ctx->car_player_sprite_idx]
					 .w *
				 ctx->scale_player_car[ctx->car_player_model]);
	int player_max_y = ctx->player_sprite_y +
			   (int)((float)ctx->gfx
					 .cars[ctx->car_player_model]
					      [ctx->car_player_sprite_idx]
					 .h *
				 ctx->scale_player_car[ctx->car_player_model]);

	for (int i = 0; i < NB_AI_CARS; i++) {
		int ai_max_x =
			ctx->ai_cars[i].hitbox.x + ctx->ai_cars[i].hitbox.w;
		int ai_max_y =
			ctx->ai_cars[i].hitbox.y + ctx->ai_cars[i].hitbox.h;

		// Xs collides
		if ((player_max_x > ctx->ai_cars[i].hitbox.x &&
		     player_max_x < ai_max_x) ||
		    (ctx->player_car_x_in_pixels < ai_max_x &&
		     ctx->player_car_x_in_pixels > ctx->ai_cars[i].hitbox.x)) {

			/*SDL_Log("[%s] player[%d->%d, %d->%d], ai[%d->%d,
			   %d->%d])\n",
				__func__,
				ctx->player_car_x_in_pixels,
				player_max_x,
				ctx->player_sprite_y,
				player_max_y,
				ctx->ai_cars[i].hitbox.x,
				ai_max_x,
				ctx->ai_cars[i].hitbox.y,
				ai_max_y);*/

			// Front collision
			if (ai_max_y > ctx->player_sprite_y &&
			    ai_max_y < player_max_y) {

				if (ctx->ai_cars[i].segment -
					    ctx->player_segment <
				    NB_SEGMENT_CAR_COLLISION)
					ctx->speed /= 2.f;
				else if (ctx->nb_segments -
						 ctx->player_segment +
						 ctx->ai_cars[i].segment <
					 NB_SEGMENT_CAR_COLLISION)
					ctx->speed /= 2.f;
			}

			// Back collison
			if (ctx->ai_cars[i].hitbox.y < player_max_y &&
			    ctx->ai_cars[i].hitbox.y > ctx->player_sprite_y) {

				if (ctx->player_segment -
					    ctx->ai_cars[i].segment <
				    NB_SEGMENT_CAR_COLLISION) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SPEED_BEHIND_PLAYER;
					ctx->ai_cars[i].behind_player_frames =
						0;
					ctx->ai_cars[i].speed_slow_straight =
						ctx->speed * .9f;
					ctx->ai_cars[i].speed_slow_curve =
						ctx->ai_cars[i]
							.speed_slow_straight;
				} else if (ctx->nb_segments -
						   ctx->ai_cars[i].segment +
						   ctx->player_segment <
					   NB_SEGMENT_CAR_COLLISION) {
					ctx->ai_cars[i].state =
						AI_CAR_STATE_SPEED_BEHIND_PLAYER;
					ctx->ai_cars[i].behind_player_frames =
						0;
					ctx->ai_cars[i].speed_slow_straight =
						ctx->speed * .9f;
					ctx->ai_cars[i].speed_slow_curve =
						ctx->ai_cars[i]
							.speed_slow_straight;
				}


				/* TODO : maybe give a little temporary
				 * speed boost */
			}
		}
	}

	return 0;
}

static int logic_race_check_collision_with_scene(struct game_context *ctx)
{

	for (int i = 0; i < 3; i++) {

		int idx = (ctx->player_segment + i) % ctx->nb_segments;
		struct road_segment *seg = &ctx->segments[idx];
		struct scene_sprite_desc *sprite_left = NULL;
		struct scene_sprite_desc *sprite_right = NULL;
		float closest_right_position = 100.f;
		float closest_left_position = -100.f;

		if (!seg->scene)
			continue;

		for (int j = 0; j < seg->scene->nb_sprites; j++) {
			if (seg->scene->sprite[j]->position > 0) {
				if (seg->scene->sprite[j]->position <
				    closest_right_position) {
					sprite_right = seg->scene->sprite[j];
					closest_right_position =
						seg->scene->sprite[j]->position;
				}
			} else {
				if (seg->scene->sprite[j]->position >
				    closest_left_position) {
					sprite_left = seg->scene->sprite[j];
					closest_left_position =
						seg->scene->sprite[j]->position;
				}
			}
		}

		int sprite_left_hb_x = 0;
		int sprite_right_hb_x = SCREEN_WIDTH;

		if (sprite_left->scaled_x < SCREEN_WIDTH &&
		    sprite_right->scale > 0) {
			if (sprite_left->hitbox)
				if (sprite_left->flip == SDL_FLIP_HORIZONTAL)
					sprite_left_hb_x =
						sprite_left->scaled_x +
						(int)((float)(sprite_left->t
								      ->w -
							      sprite_left
								      ->hitbox
								      ->x) *
						      sprite_left->scale);
				else /* SDL_FLIP_NONE */
					sprite_left_hb_x =
						sprite_left->scaled_x +
						(int)((float)(sprite_left
								      ->hitbox
								      ->x +
							      sprite_left
								      ->hitbox
								      ->w) *
						      sprite_left->scale);
			else
				// if (sprite_left->scaled_x < SCREEN_WIDTH)
				sprite_left_hb_x =
					sprite_left->scaled_x +
					(int)((float)sprite_left->t->w *
					      sprite_left->scale);
		}

		if (sprite_right->scaled_x > 0 &&
		    sprite_right->scaled_x < SCREEN_WIDTH &&
		    sprite_right->scale > 0) {
			if (sprite_right->hitbox)
				sprite_right_hb_x =
					sprite_right->scaled_x +
					(int)((float)sprite_right->hitbox->x *
					      sprite_right->scale);
			else /*if (sprite_right->scaled_x > 0 &&
				 sprite_right->scaled_x < SCREEN_WIDTH)*/
				sprite_right_hb_x = sprite_right->scaled_x;
		}
		// check car collision with sprite on left
		if (ctx->player_car_x_in_pixels < sprite_left_hb_x) {
			SDL_Log("[%s] collision detected on LEFT\n", __func__);
			//} else if (ctx->player_car_x_in_pixels +
			//(float)ctx->gfx.car_player.w * PLAYER_CAR_SPRITE_ZOOM
			//>

			ctx->collision_dst_x =
				ctx->player_x + COLLIONSION_SCENE_SHIFT;

			ctx->speed = ctx->speed * 0.75f;

			ctx->status_cur = GAME_STATE_RACE_COLLISION_SCENE;

			break;

		} else if (
			ctx->player_car_x_in_pixels +
				(int)((float)ctx->gfx
					      .cars[ctx->car_player_model]
						   [ctx->car_player_sprite_idx]
					      .w *
				      ctx->scale_player_car
					      [ctx->car_player_model])
			/* TODO : CHECK this coef is rightly used !!!! */
			> sprite_right_hb_x) {
			SDL_Log("[%s] collision detected on RIGHT\n", __func__);

			ctx->collision_dst_x =
				ctx->player_x - COLLIONSION_SCENE_SHIFT;

			ctx->speed = ctx->speed * 0.75f;

			ctx->status_cur = GAME_STATE_RACE_COLLISION_SCENE;
			break;
		}
		/*if (sprite_right_hb_x < SCREEN_WIDTH)
			SDL_Log("[%s] car_x (%d) + car_w (%d) = %d,
		   sprite_right_hb_x = %d\n",
				__func__,
				ctx->player_car_x_in_pixels,
				ctx->gfx.car_player.w / 2,
				ctx->player_car_x_in_pixels +
		   ctx->gfx.car_player.w / 2, sprite_right_hb_x);*/
	}

	return 0;
}


static int logic_race_control(struct game_context *ctx)
{

	float max_speed, accel;

	if (ctx->keys.nitro && ctx->nb_nitro > 0 &&
	    ctx->status_cur != GAME_STATE_RACE_NITRO) {
		ctx->status_cur = GAME_STATE_RACE_NITRO;
		ctx->nitro_nb_frame = 0;
		ctx->nb_nitro--;
	}

	if (ctx->status_cur == GAME_STATE_RACE_NITRO) {
		max_speed = ctx->max_speed_nitro;
		accel = ctx->accel_nitro;
		ctx->nitro_nb_frame++;
		if (ctx->nitro_nb_frame > NITRO_DURATION * FPS)
			ctx->status_cur = GAME_STATE_RACE;
	} else {
		max_speed = ctx->max_speed;
		accel = ctx->accel;
	}

	float speed_ratio = ctx->speed / max_speed;
	float player_ratio =
		(float)((ctx->position + ctx->player_z) % ROAD_SEGMENT_LENGTH) /
		(float)ROAD_SEGMENT_LENGTH;

	ctx->ts_cur = SDL_GetTicks();
	ctx->dt = (float)(ctx->ts_cur - ctx->ts_prev);
	ctx->ts_prev = ctx->ts_cur;

	// TODO: remove ?
	// cap delta t
	if (ctx->dt > 35) {
		ctx->dt = 35;
	}

	int step = (int)(ctx->dt * ctx->speed);
	ctx->position = inline_increase(ctx->position, step, ctx->track_length);
	ctx->player_distance_ran += step;

	// screen crossing should take 1sec at top speed
	float dx = (ctx->dt * 2 * (ctx->speed / max_speed)) / 3000;

	if (ctx->keys.left) {
		ctx->player_x = ctx->player_x - dx;
		if (ctx->car_orientation_cur == PLAYER_SPRITE_STRAIGHT ||
		    ctx->car_orientation_cur == PLAYER_SPRITE_LIGHT_RIGHT ||
		    ctx->car_orientation_cur == PLAYER_SPRITE_HARD_RIGHT) {
			ctx->car_orientation_cur = PLAYER_SPRITE_LIGHT_LEFT;
			ctx->same_car_orientation_in_frame = 0;
		} else if (ctx->car_orientation_cur ==
				   PLAYER_SPRITE_LIGHT_LEFT &&
			   ctx->same_car_orientation_in_frame > 5) {
			ctx->car_orientation_cur = PLAYER_SPRITE_HARD_LEFT;
		}
	} else if (ctx->keys.right) {
		ctx->player_x = ctx->player_x + dx;
		if (ctx->car_orientation_cur == PLAYER_SPRITE_STRAIGHT ||
		    ctx->car_orientation_cur == PLAYER_SPRITE_LIGHT_LEFT ||
		    ctx->car_orientation_cur == PLAYER_SPRITE_HARD_LEFT) {
			ctx->car_orientation_cur = PLAYER_SPRITE_LIGHT_RIGHT;
			ctx->same_car_orientation_in_frame = 0;
		} else if (ctx->car_orientation_cur ==
				   PLAYER_SPRITE_LIGHT_RIGHT &&
			   ctx->same_car_orientation_in_frame > 5) {
			ctx->car_orientation_cur = PLAYER_SPRITE_HARD_RIGHT;
		}
	}
	// no dir key pressed
	else {
		ctx->car_orientation_cur = PLAYER_SPRITE_STRAIGHT;
		ctx->same_car_orientation_in_frame = 0;
	}

	if (ctx->car_orientation_cur != ctx->car_orientation_prev) {
		ctx->car_orientation_prev = ctx->car_orientation_cur;
		logic_set_player_sprite(ctx);
	} else {
		ctx->same_car_orientation_in_frame++;
	}

	ctx->player_x =
		ctx->player_x -
		(dx * speed_ratio * ctx->segments[ctx->player_segment].curve *
		 ctx->centrifugal);

	if (ctx->keys.accel) {
		ctx->speed = inline_accelerate(ctx->speed, accel, ctx->dt);
	} else if (ctx->keys.brake) {
		ctx->speed =
			inline_accelerate(ctx->speed, ctx->breaking, ctx->dt);
	} else {
		ctx->speed = inline_accelerate(ctx->speed, ctx->decel, ctx->dt);
	}

	if ((ctx->player_x < -1 || ctx->player_x > 1) &&
	    ctx->speed > ctx->off_road_limit) {
		ctx->speed = inline_accelerate(
			ctx->speed, ctx->off_road_decel, ctx->dt);
	}

	// don't let player go out of bounds
	ctx->player_x = inline_limit(ctx->player_x, -2, 2);
	// cap player speed
	ctx->speed = inline_limit(ctx->speed, 0, max_speed);

	ctx->player_y = (int)inline_interpolate(
		ctx->segments[ctx->player_segment].p1.world.y,
		ctx->segments[ctx->player_segment].p2.world.y,
		player_ratio);

	return 0;
}


static int logic_race(struct game_context *ctx)
{
	int ret;

	ctx->player_segment_prev = ctx->player_segment;
	ctx->player_segment =
		inline_get_segment_idx(ctx, ctx->position + ctx->player_z);

	/*ret = logic_race_check_collision_with_scene(ctx);
	ret = logic_race_check_collision_with_cars(ctx);*/
	ret = logic_race_control(ctx);
	ret = logic_race_ai_cars(ctx);
	ret = logic_race_check_collision_with_scene(ctx);
	ret = logic_race_check_collision_with_cars(ctx);

	return ret;
}


static int logic_race_collision_scene(struct game_context *ctx)
{
	int ret;

	ctx->player_segment_prev = ctx->player_segment;
	ctx->player_segment =
		inline_get_segment_idx(ctx, ctx->position + ctx->player_z);

	ret = logic_race_control(ctx);

	if (ctx->collision_dst_x < 0) {
		ctx->player_x = ctx->player_x + COLLIONSION_SCENE_SHIFT / 10.f;
		if (ctx->player_x >= ctx->collision_dst_x)
			ctx->status_cur = GAME_STATE_RACE;
	} else {
		ctx->player_x = ctx->player_x - COLLIONSION_SCENE_SHIFT / 10.f;
		if (ctx->player_x <= ctx->collision_dst_x)
			ctx->status_cur = GAME_STATE_RACE;
	}

	return ret;
}

int logic_project_coord(struct segment_point *p,
			int first_segments_z_offset,
			int camera_x,
			int camera_y,
			int camera_z,
			float camera_depth,
			int width,
			int height,
			int road_width)
{
	// translate coordinates from world to camera
	p->camera.x = p->world.x - camera_x;
	p->camera.y = p->world.y - (float)camera_y;
	p->camera.z =
		p->world.z - (float)camera_z + (float)first_segments_z_offset;

	// compute scaling factor
	if (p->camera.z != 0) // TODO: what about this case ?
		p->screen.scale = camera_depth / p->camera.z;
	else
		p->screen.scale = 1;

	// TODO: scaling num/den, rounding
	// scale coordinate to screen
	p->screen.x = (width / 2) + (int)(p->screen.scale * (float)p->camera.x *
					  (float)width / 2.f);
	p->screen.y = ((float)height / 2.f) -
		      (p->screen.scale * p->camera.y * (float)height / 2.f);
	p->screen.w =
		(int)(p->screen.scale * (float)road_width * (float)width / 2.f);

	return 0;
}

// TODO static inline in utilitary function file
int logic_get_player_place_nb(struct game_context *ctx)
{
	int pos = 1;
	for (int i = 0; i < NB_AI_CARS; i++) {
		if (ctx->ai_cars[i].distance > ctx->player_distance_ran)
			pos++;
	}
	return pos;
}

char *logic_get_player_place_suffix(int pos)
{
	switch (pos) {
	case 1:
		return "st";
	case 2:
		return "nd";
	case 3:
		return "rd";
	default:
		return "th";
	}
}

int logic_get_player_lap_nb(struct game_context *ctx)
{
	static int last_lap = 0;

	if (ctx->player_segment_prev > ctx->player_segment)
		last_lap++;

	if (last_lap == 0)
		return 1;
	else if (last_lap > ctx->nb_lap)
		return ctx->nb_lap;
	else
		return last_lap;
}


int main_logic(struct game_context *ctx)
{

	if (!ctx) {
		printf("invalid parameter\n");
		return -EINVAL;
	}

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_RACE:
	case GAME_STATE_RACE_NITRO:
		logic_race(ctx);
		break;
	case GAME_STATE_RACE_COLLISION_SCENE:
		logic_race_collision_scene(ctx);
		break;
	case GAME_STATE_QUIT:
	case GAME_STATE_PAUSE:
	case GAME_STATE_GAMEOVER:
	default:
		break;
	}

	return 0;
}
