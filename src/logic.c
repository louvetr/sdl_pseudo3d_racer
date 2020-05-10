#include "main.h"

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
	switch (ctx->pcar.car_orientation_cur) {
	case PLAYER_SPRITE_HARD_LEFT:
		ctx->pcar.car_player_sprite_idx = CAR_SPRITE_RIGHT2;
		ctx->pcar.car_player_flip = SDL_FLIP_HORIZONTAL;
		break;
	case PLAYER_SPRITE_LIGHT_LEFT:
		ctx->pcar.car_player_sprite_idx = CAR_SPRITE_RIGHT1;
		ctx->pcar.car_player_flip = SDL_FLIP_HORIZONTAL;
		break;
	case PLAYER_SPRITE_STRAIGHT:
		ctx->pcar.car_player_sprite_idx = CAR_SPRITE_REAR;
		ctx->pcar.car_player_flip = SDL_FLIP_NONE;
		break;
	case PLAYER_SPRITE_LIGHT_RIGHT:
		ctx->pcar.car_player_sprite_idx = CAR_SPRITE_RIGHT1;
		ctx->pcar.car_player_flip = SDL_FLIP_NONE;
		break;
	case PLAYER_SPRITE_HARD_RIGHT:
		ctx->pcar.car_player_sprite_idx = CAR_SPRITE_RIGHT2;
		ctx->pcar.car_player_flip = SDL_FLIP_NONE;
		break;
	}

	return 0;
}


static int logic_race_check_collision_with_cars(struct game_context *ctx)
{
	for (int i = 0; i < NB_AI_CARS; i++) {
		int ai_max_x =
			ctx->ai_cars[i].hitbox.x + ctx->ai_cars[i].hitbox.w;
		int ai_max_y =
			ctx->ai_cars[i].hitbox.y + ctx->ai_cars[i].hitbox.h;

		// Xs collides
		if ((ctx->pcar.player_max_x > ctx->ai_cars[i].hitbox.x &&
		     ctx->pcar.player_max_x < ai_max_x) ||
		    (ctx->pcar.player_sprite_x < ai_max_x &&
		     ctx->pcar.player_sprite_x > ctx->ai_cars[i].hitbox.x)) {

			// Front collision
			if (ai_max_y > ctx->pcar.player_sprite_y &&
			    ai_max_y < ctx->pcar.player_max_y) {

				if (ctx->ai_cars[i].segment -
					    ctx->pcar.player_segment <
				    NB_SEGMENT_CAR_COLLISION) {
					SDL_Log("[%s] COLLISON CAR FRONT\n",
						__func__);
					ctx->sound.collision_detected = 1;
					if (ctx->pcar.speed >= ctx->pcar.max_speed / 4)
						ctx->pcar.speed /= 2.f;
				} else if (ctx->track.nb_segments -
						   ctx->pcar.player_segment +
						   ctx->ai_cars[i].segment <
					   NB_SEGMENT_CAR_COLLISION) {
					SDL_Log("[%s] COLLISON CAR FRONT\n",
						__func__);
					ctx->sound.collision_detected = 1;
					if (ctx->pcar.speed >= ctx->pcar.max_speed / 4)
						ctx->pcar.speed /= 2.f;
				}
			}

			if (ctx->ai_cars[i].hitbox.y < ctx->pcar.player_max_y &&
			    ctx->ai_cars[i].hitbox.y > ctx->pcar.player_sprite_y) {

				int back_impact = 0;

				if (ctx->pcar.player_segment >
				    ctx->ai_cars[i].segment) {
					back_impact = 1;
				} else if (ctx->track.nb_segments -
						   ctx->ai_cars[i].segment +
						   ctx->pcar.player_segment <
					   NB_SEGMENT_CAR_COLLISION) {
					back_impact = 1;
				}

				if (back_impact == 0) {
					continue;
				}

				ctx->sound.collision_detected = 1;
				SDL_Log("[%s] COLLISON CAR BACK\n", __func__);

				ctx->ai_cars[i].state =
					AI_CAR_STATE_SPEED_BEHIND_PLAYER;
				ctx->ai_cars[i].behind_player_frames = 0;

				if (ctx->pcar.speed) {
					ctx->ai_cars[i].speed_slow_straight =
						ctx->pcar.speed * .5f;

					float speed_boost =
						ctx->ai_cars[i]
							.speed_max_straight *
						.05f;

					if (ctx->pcar.speed + speed_boost <
					    ctx->pcar.max_speed)
						ctx->pcar.speed += speed_boost;
				} else {
					ctx->ai_cars[i].speed_slow_straight =
						0.f;
					ctx->pcar.speed =
						ctx->ai_cars[i]
							.speed_max_straight *
						.05f;
				}

				ctx->ai_cars[i].speed_slow_curve =
					ctx->ai_cars[i].speed_slow_straight;
			}
		}
	}

	return 0;
}

static int logic_race_check_collision_with_scene(struct game_context *ctx)
{

	for (int i = 0; i < 3; i++) {

		int idx = (ctx->pcar.player_segment + i) % ctx->track.nb_segments;
		struct road_segment *seg = &ctx->track.segments[idx];
		struct scene_sprite_desc *sprite_left = NULL;
		struct scene_sprite_desc *sprite_right = NULL;
		float closest_right_position = 100.f;
		float closest_left_position = -100.f;

		if (!seg->scene)
			continue;

		// TODO: preset the index of closest scene spite of the road to
		// avoid this computation

		for (int j = 0; j < seg->scene->nb_sprites; j++) {
			if (seg->scene->sprite[j].position > 0) {
				if (seg->scene->sprite[j].position <
				    closest_right_position) {
					sprite_right = &seg->scene->sprite[j];
					closest_right_position =
						seg->scene->sprite[j].position;
				}
			} else {
				if (seg->scene->sprite[j].position >
				    closest_left_position) {
					sprite_left = &seg->scene->sprite[j];
					closest_left_position =
						seg->scene->sprite[j].position;
				}
			}
		}

		int sprite_left_hb_x = 0;
		int sprite_right_hb_x = SCREEN_WIDTH;

		// TODO: recheck hitbox
		if (sprite_left->collide &&
		    sprite_left->scaled_x < SCREEN_WIDTH &&
		    sprite_left->scale > 0) {
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

		if (sprite_right->collide && sprite_right->scaled_x > 0 &&
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
		if (ctx->pcar.player_sprite_x < sprite_left_hb_x) {
			SDL_Log("[%s] collision detected on LEFT\n", __func__);

			ctx->pcar.collision_dst_x =
				ctx->pcar.player_x + COLLIONSION_SCENE_SHIFT;

			ctx->pcar.speed = ctx->pcar.speed * 0.75f;

			SDL_Log("[%s] COLLISON CAR SCENE\n", __func__);
			ctx->sound.collision_detected = 1;
			ctx->status_cur = GAME_STATE_RACE_COLLISION_SCENE;

			break;

		} else if (ctx->pcar.player_max_y
			   /* TODO : CHECK this coef is rightly used !!!! */
			   > sprite_right_hb_x) {
			SDL_Log("[%s] collision detected on RIGHT\n", __func__);

			ctx->pcar.collision_dst_x =
				ctx->pcar.player_x - COLLIONSION_SCENE_SHIFT;

			ctx->pcar.speed = ctx->pcar.speed * 0.75f;

			SDL_Log("[%s] COLLISON CAR SCENE\n", __func__);
			ctx->sound.collision_detected = 1;
			ctx->status_cur = GAME_STATE_RACE_COLLISION_SCENE;
			break;
		}
		/*if (sprite_right_hb_x < SCREEN_WIDTH)
			SDL_Log("[%s] car_x (%d) + car_w (%d) = %d,
		   sprite_right_hb_x = %d\n",
				__func__,
				ctx->pcar.player_sprite_x,
				ctx->gfx.car_player.w / 2,
				ctx->pcar.player_sprite_x +
		   ctx->gfx.car_player.w / 2, sprite_right_hb_x);*/
	}

	return 0;
}


static int logic_race_particles(struct game_context *ctx, float drift)
{
	// SDL_Log("[%s] drift = %f\n", __func__, drift);
	if (drift > 0.025f || drift < -0.025f) {
		int smoke_idx = -1;
		for (int k = 0; k < NB_PARTICLES_SMOKE_DISPLAY; k++) {
			if (ctx->gfx.part_smoke[k].pos_x == 0) {
				smoke_idx = k;
				break;
			}
		}

		if (smoke_idx >= 0) {
			ctx->gfx.part_smoke[smoke_idx].frame = rand() % 5;

			ctx->gfx.part_smoke[smoke_idx].t =
				&ctx->gfx.t_smoke
					 [rand() %
					  NB_PARTICLES_SMOKE_AVAILABLE];

			int smoke_w =
				(int)((float)ctx->gfx.part_smoke[smoke_idx].t->w *
				      PARTICLE_SMOKE_SCALE);
			int smoke_w_rnd = rand() % (smoke_w * 2);

			if (drift > 0)
				ctx->gfx.part_smoke[smoke_idx].pos_x =
					ctx->pcar.player_sprite_x - smoke_w +
					smoke_w_rnd;
			else
				ctx->gfx.part_smoke[smoke_idx].pos_x =
					ctx->pcar.player_max_x - smoke_w_rnd;

			ctx->gfx.part_smoke[smoke_idx].pos_y =
				ctx->pcar.player_max_y -
				(int)((float)ctx->gfx.part_smoke[smoke_idx].t->h *
				      PARTICLE_SMOKE_SCALE);
		}
	}

	if (ctx->status_cur == GAME_STATE_RACE_NITRO) {

		int nitro_idx = -1;
		for (int k = 0; k < NB_PARTICLES_NITRO_DISPLAY; k++) {
			if (ctx->gfx.part_nitro[k].pos_x == 0) {
				nitro_idx = k;
				break;
			}
		}

		if (nitro_idx >= 0) {
			ctx->gfx.part_nitro[nitro_idx].frame = rand() % 5;

			ctx->gfx.part_nitro[nitro_idx].t =
				&ctx->gfx.t_nitro
					 [rand() %
					  NB_PARTICLES_NITRO_AVAILABLE];

			int nitro_w =
				(int)((float)ctx->gfx.part_nitro[nitro_idx].t->w *
				      PARTICLE_NITRO_SCALE);
			int nitro_w_rnd =
				rand() % (ctx->pcar.player_sprite_w - nitro_w);

			ctx->gfx.part_nitro[nitro_idx].pos_x =
				ctx->pcar.player_sprite_x + nitro_w_rnd;

			ctx->gfx.part_nitro[nitro_idx].pos_y =
				ctx->pcar.player_max_y -
				(int)((float)ctx->gfx.part_nitro[nitro_idx].t->h *
				      PARTICLE_NITRO_SCALE * 0.85f);
		}
	}

	return 0;
}


static int logic_race_dt(struct game_context *ctx)
{
	ctx->ts_cur = SDL_GetTicks();
	ctx->dt = (float)(ctx->ts_cur - ctx->ts_prev);
	ctx->ts_prev = ctx->ts_cur;

	// TODO: remove ?
	// cap delta t
	if (ctx->dt > 35) {
		ctx->dt = 35;
	}

	return 0;
}

static int logic_race_control(struct game_context *ctx)
{

	float max_speed, accel;

	if (ctx->keys.nitro && ctx->pcar.nb_nitro > 0 &&
	    ctx->status_cur != GAME_STATE_RACE_NITRO) {
		ctx->status_cur = GAME_STATE_RACE_NITRO;
		ctx->pcar.nitro_nb_frame = NITRO_DURATION * FPS;
		ctx->pcar.nb_nitro--;
	} else {
		// workaroud to correct a nitro SFX activation issue
		ctx->keys.nitro = 0;
	}

	if (ctx->status_cur == GAME_STATE_RACE_NITRO) {
		max_speed = ctx->pcar.max_speed_nitro;
		accel = ctx->pcar.accel_nitro;
		ctx->pcar.nitro_nb_frame--;
		if (ctx->pcar.nitro_nb_frame == 0) {
			event_update_game_state(ctx, GAME_STATE_RACE);
		}
	} else {
		max_speed = ctx->pcar.max_speed;
		accel = ctx->pcar.accel;
	}

	float speed_ratio = ctx->pcar.speed / max_speed;
	float player_ratio =
		(float)((ctx->pcar.position + ctx->pcar.player_z) % ROAD_SEGMENT_LENGTH) /
		(float)ROAD_SEGMENT_LENGTH;

	int step = (int)(ctx->dt * ctx->pcar.speed);
	ctx->pcar.position = inline_increase(ctx->pcar.position, step, ctx->track.track_length);
	ctx->pcar.player_distance_ran += step;

	// screen crossing should take 1sec at top speed
	float dx = (ctx->dt * 2 * (ctx->pcar.speed / max_speed)) / 3000;

	if (ctx->status_cur != GAME_STATE_RACE_ANIM_END) {
		if (ctx->keys.left) {
			ctx->pcar.player_x = ctx->pcar.player_x - dx;
			if (ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_STRAIGHT ||
			    ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_LIGHT_RIGHT ||
			    ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_HARD_RIGHT) {
				ctx->pcar.car_orientation_cur =
					PLAYER_SPRITE_LIGHT_LEFT;
				ctx->pcar.same_car_orientation_in_frame = 0;
			} else if (ctx->pcar.car_orientation_cur ==
					   PLAYER_SPRITE_LIGHT_LEFT &&
				   ctx->pcar.same_car_orientation_in_frame > 5) {
				ctx->pcar.car_orientation_cur =
					PLAYER_SPRITE_HARD_LEFT;
			}
		} else if (ctx->keys.right) {
			ctx->pcar.player_x = ctx->pcar.player_x + dx;
			if (ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_STRAIGHT ||
			    ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_LIGHT_LEFT ||
			    ctx->pcar.car_orientation_cur ==
				    PLAYER_SPRITE_HARD_LEFT) {
				ctx->pcar.car_orientation_cur =
					PLAYER_SPRITE_LIGHT_RIGHT;
				ctx->pcar.same_car_orientation_in_frame = 0;
			} else if (ctx->pcar.car_orientation_cur ==
					   PLAYER_SPRITE_LIGHT_RIGHT &&
				   ctx->pcar.same_car_orientation_in_frame > 5) {
				ctx->pcar.car_orientation_cur =
					PLAYER_SPRITE_HARD_RIGHT;
			}
		}
		// no dir key pressed
		else {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_STRAIGHT;
			ctx->pcar.same_car_orientation_in_frame = 0;
		}
	} else {
		struct road_segment *seg = &ctx->track.segments[ctx->pcar.player_segment];
		// select sprite to simulate a steering in curves
		if (seg->curve > 2.f) {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_HARD_RIGHT;
		} else if (seg->curve > 0.5f) {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_LIGHT_RIGHT;
		} else if (seg->curve < -2.f) {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_HARD_LEFT;
		} else if (seg->curve < -0.5f) {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_LIGHT_LEFT;
		} else {
			ctx->pcar.car_orientation_cur = PLAYER_SPRITE_STRAIGHT;
		}
	}

	if (ctx->pcar.car_orientation_cur != ctx->pcar.car_orientation_prev) {
		ctx->pcar.car_orientation_prev = ctx->pcar.car_orientation_cur;
		logic_set_player_sprite(ctx);
	} else {
		ctx->pcar.same_car_orientation_in_frame++;
	}

	if (ctx->status_cur != GAME_STATE_RACE_ANIM_END) {
		ctx->sound.drift = dx * speed_ratio *
			     ctx->track.segments[ctx->pcar.player_segment].curve *
			     ctx->pcar.centrifugal;
		ctx->pcar.player_x = ctx->pcar.player_x - ctx->sound.drift;

		logic_race_particles(ctx, ctx->sound.drift);
	}

	///////////////////////////////////////////////////////////////

	if (ctx->keys.accel || ctx->status_cur == GAME_STATE_RACE_ANIM_END)
		ctx->pcar.speed = inline_accelerate(ctx->pcar.speed, accel, ctx->dt);
	else if (ctx->keys.brake)
		ctx->pcar.speed =
			inline_accelerate(ctx->pcar.speed, ctx->pcar.breaking, ctx->dt);
	else
		ctx->pcar.speed = inline_accelerate(ctx->pcar.speed, ctx->pcar.decel, ctx->dt);


	if ((ctx->pcar.player_x < -1 || ctx->pcar.player_x > 1) &&
	    ctx->pcar.speed > ctx->pcar.off_road_limit) {
		ctx->pcar.speed = inline_accelerate(
			ctx->pcar.speed, ctx->pcar.off_road_decel, ctx->dt);
	}

	// don't let player go out of bounds
	ctx->pcar.player_x = inline_limit(ctx->pcar.player_x, -2, 2);
	// cap player speed
	ctx->pcar.speed = inline_limit(ctx->pcar.speed, 0, max_speed);

	ctx->pcar.player_y = (int)inline_interpolate(
		ctx->track.segments[ctx->pcar.player_segment].p1.world.y,
		ctx->track.segments[ctx->pcar.player_segment].p2.world.y,
		player_ratio);

	return 0;
}


static int logic_race_collision_scene_ongoing(struct game_context *ctx)
{
	if (ctx->pcar.collision_dst_x < 0) {
		ctx->pcar.player_x = ctx->pcar.player_x + COLLIONSION_SCENE_SHIFT / 10.f;
		if (ctx->pcar.player_x >= ctx->pcar.collision_dst_x)
			event_update_game_state(ctx, GAME_STATE_RACE);
	} else {
		ctx->pcar.player_x = ctx->pcar.player_x - COLLIONSION_SCENE_SHIFT / 10.f;
		if (ctx->pcar.player_x <= ctx->pcar.collision_dst_x)
			event_update_game_state(ctx, GAME_STATE_RACE);
	}

	return 0;
}


static int logic_race(struct game_context *ctx)
{
	int ret;

	ctx->sound.collision_detected = 0;
	ctx->sound.drift = 0.f;

	// update player segment
	ctx->pcar.player_segment_prev = ctx->pcar.player_segment;
	ctx->pcar.player_segment =
		inline_get_segment_idx(ctx, ctx->pcar.position + ctx->pcar.player_z);

	// compute time since last frame
	ret = logic_race_dt(ctx);

	// manage car movement according control input
	ret = logic_race_control(ctx);

	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START) {
		// TODO: change nb_frame_anim into a countdown to 0
		// some computation specific to start animation
		if (ctx->race.nb_frame_anim > FPS * START_ANIM_DURATION) {
			event_update_game_state(ctx, GAME_STATE_RACE);
			ctx->race.nb_frame_anim = 0;
			ctx->race.race_time_ms = 0;
			ctx->race.bgm_name_dislayed = 0;
			ctx->sound.bgm_idx = rand() % NB_BGM;
		}

		// TODO: used define values
		if (ctx->race.camera_height > CAMERA_HEIGHT_RACE) {
			ctx->race.camera_height -=
				(CAMERA_HEIGHT_START - CAMERA_HEIGHT_RACE) /
				((START_ANIM_DURATION - 2) * FPS);
		}
	} else {
		// perform ai car logic
		ret = logic_race_ai_cars(ctx);
	}

	// Either check collision with scene or manage collision state
	if (ctx->status_cur == GAME_STATE_RACE_COLLISION_SCENE)
		ret = logic_race_collision_scene_ongoing(ctx);
	else
		ret = logic_race_check_collision_with_scene(ctx);

	if (ctx->status_cur != GAME_STATE_RACE_ANIM_START) {
		// check collision with other cars
		ret = logic_race_check_collision_with_cars(ctx);
	}

	// compute current lap number
	ctx->race.player_lap = logic_get_player_lap_nb(ctx);

	// increase clock
	if (ctx->status_cur == GAME_STATE_RACE ||
	    ctx->status_cur == GAME_STATE_RACE_COLLISION_SCENE ||
	    ctx->status_cur == GAME_STATE_RACE_NITRO)
		ctx->race.race_time_ms += (int)ctx->dt;

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
		if (ctx->ai_cars[i].distance > ctx->pcar.player_distance_ran)
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
	static int lap = 0;

	ctx->sound.lap_sfx = 0;

	if ((ctx->status_cur == GAME_STATE_RACE ||
	     ctx->status_cur == GAME_STATE_RACE_COLLISION_SCENE ||
	     ctx->status_cur == GAME_STATE_RACE_NITRO) &&
	    ctx->pcar.player_segment_prev > ctx->pcar.player_segment) {
		lap++;

		if (lap > 1)
			ctx->sound.lap_sfx = 1;
	}

	if (lap == 0) {
		return 1;
	} else if (lap > ctx->race.nb_lap) {
		if (ctx->status_cur != GAME_STATE_RACE_ANIM_END)
			ctx->race.nb_frame_anim = 0;
		event_update_game_state(ctx, GAME_STATE_RACE_ANIM_END);
		return ctx->race.nb_lap;
	} else {
		return lap;
	}
}


int main_logic(struct game_context *ctx)
{
	int ret = 0;

	if (!ctx) {
		SDL_Log("invalid parameter\n");
		return -EINVAL;
	}

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_RACE_ANIM_START:
	case GAME_STATE_RACE_ANIM_END:
	case GAME_STATE_RACE:
	case GAME_STATE_RACE_NITRO:
	case GAME_STATE_RACE_COLLISION_SCENE:
		logic_race(ctx);
		break;
	case GAME_STATE_QUIT:
	case GAME_STATE_PAUSE:
	case GAME_STATE_GAMEOVER:
	default:
		break;
	}

	return ret;
}
