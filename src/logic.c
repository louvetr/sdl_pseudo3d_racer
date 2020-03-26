#include "common.h"


static float COLLIONSION_SCENE_SHIFT = 0.5f;

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////


static int logic_race_collision(struct game_context *ctx)
{

	for (size_t i = 0; i < 3; i++) {

		size_t idx = (ctx->player_segment + i) % ctx->nb_segments;
		struct road_segment *seg = &ctx->segments[idx];
		struct scene_sprite_desc *sprite_left = NULL;
		struct scene_sprite_desc *sprite_right = NULL;
		float closest_right_position = 100.f;
		float closest_left_position = -100.f;

		if (!seg->scene)
			// return 0;
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
						(int)((float)(sprite_left->t->w -
						 sprite_left->hitbox->x) *
							sprite_left->scale);
				else /* SDL_FLIP_NONE */
					sprite_left_hb_x =
						sprite_left->scaled_x +
						(int)((float)(sprite_left->hitbox->x +
						 sprite_left->hitbox->w) *
							sprite_left->scale);
			else
				// if (sprite_left->scaled_x < SCREEN_WIDTH)
				sprite_left_hb_x =
					sprite_left->scaled_x +
					(int)((float)sprite_left->t->w * sprite_left->scale);
		}

		if (sprite_right->scaled_x > 0 &&
		    sprite_right->scaled_x < SCREEN_WIDTH &&
		    sprite_right->scale > 0) {
			if (sprite_right->hitbox)
				sprite_right_hb_x = sprite_right->scaled_x +
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

		} else if (ctx->player_car_x_in_pixels +
				   ctx->gfx.car_player.w /
					   2 /* TODO: use player car zoom define
					      */
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
	float speed_ratio = ctx->speed / ctx->max_speed;
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

	ctx->position = inline_increase(ctx->position,
					(size_t)(ctx->dt * ctx->speed),
					ctx->track_length);

	// screen crossing should take 1sec at top speed
	float dx = (ctx->dt * 2 * (ctx->speed / ctx->max_speed)) / 3000;

	if (ctx->keys.left)
		ctx->player_x = ctx->player_x - dx;
	else if (ctx->keys.right)
		ctx->player_x = ctx->player_x + dx;

	ctx->player_x =
		ctx->player_x -
		(dx * speed_ratio * ctx->segments[ctx->player_segment].curve *
		 ctx->centrifugal);

	if (ctx->keys.accel) {
		ctx->speed = inline_accelerate(ctx->speed, ctx->accel, ctx->dt);
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
	ctx->speed = inline_limit(ctx->speed, 0, ctx->max_speed);

	ctx->player_y = (int)inline_interpolate(
		ctx->segments[ctx->player_segment].p1.world.y,
		ctx->segments[ctx->player_segment].p2.world.y,
		player_ratio);

	return 0;
}


static int logic_race(struct game_context *ctx)
{
	int ret;

	ctx->player_segment =
		inline_get_segment_idx(ctx, ctx->position + ctx->player_z);

	ret = logic_race_collision(ctx);
	ret = logic_race_control(ctx);
	ret = logic_race_ai_cars(ctx);

	return ret;
}

static int logic_race_collision_scene(struct game_context *ctx)
{
	int ret;

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
