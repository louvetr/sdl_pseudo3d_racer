#include "common.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////


static int logic_game(struct game_context *ctx)
{

	int player_segment =
		inline_get_segment_idx(ctx, ctx->position + ctx->player_z);
	float speed_ratio = ctx->speed / ctx->max_speed;
	float player_ratio =
		(float)((ctx->position + ctx->player_z) % ROAD_SEGMENT_LENGTH) /
		(float) ROAD_SEGMENT_LENGTH;

	ctx->ts_cur = SDL_GetTicks();
	ctx->dt = ctx->ts_cur - ctx->ts_prev;

	/*SDL_Log("[%s][position = %d] ENTER with accel = %d, dt = %d, speed =
	   %d\n",
		__func__,
		ctx->position,
		ctx->accel,
		ctx->dt,
		ctx->speed);*/

	ctx->ts_prev = ctx->ts_cur;

	// TODO: remove ?
	if (ctx->dt > 35) {
		ctx->dt = 35;
	}

	// TODO: DEBUG
	/*if (ctx->action != ACTION_UP)
		return 0;*/

	/*SDL_Log("[%s][position = %d] ENTER with accel = %d, dt = %d, speed =
	   %d\n",
		__func__,
		ctx->position,
		ctx->accel,
		ctx->dt,
		ctx->speed);*/

	static float player_x_prev;
	player_x_prev = ctx->player_x;
	static float speed_prev;
	speed_prev = ctx->speed;

	ctx->position = inline_increase(
		ctx->position, ctx->dt * ctx->speed, ctx->track_length);

	// screen crossing should take 1sec at top speed
	float dx = (ctx->dt * 2 * (ctx->speed / ctx->max_speed)) / 3000;

	if (ctx->keys.left)
		ctx->player_x = ctx->player_x - dx;
	else if (ctx->keys.right)
		ctx->player_x = ctx->player_x + dx;

	ctx->player_x = ctx->player_x - (dx * speed_ratio *
					 ctx->segments[player_segment].curve *
					 ctx->centrifugal);

	// if (!(cpt % 30))
	// if (player_x_prev != ctx->player_x) {
	/*SDL_Log("[%s]dx : %f = %f  * 2 * (%f / %f))\n",
		__func__,
		dx,
		ctx->dt,
		ctx->speed,
		ctx->max_speed);
	SDL_Log("[%s] ctx->player_x : %f = %f - %f\n",
		__func__,
		ctx->player_x,
		player_x_prev,
		dx);*/
	//}

	if (ctx->keys.accel) {
		ctx->speed = inline_accelerate(ctx->speed, ctx->accel, ctx->dt);
		/*if (ctx->speed != speed_prev)
		SDL_Log("[accel] speed : %f = %f + %f * %f\n",
			ctx->speed,
			speed_prev,
			ctx->accel,
			ctx->dt);*/
	} else if (ctx->keys.brake) {
		ctx->speed =
			inline_accelerate(ctx->speed, ctx->breaking, ctx->dt);
		/*if (ctx->speed != speed_prev)
			SDL_Log("[breaking] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);*/
	} else {
		ctx->speed = inline_accelerate(ctx->speed, ctx->decel, ctx->dt);
		/*if (ctx->speed != speed_prev)
			SDL_Log("[decel] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);*/
	}


	/*SDL_Log("[offroad] off_road_limit=%f, dt = %f, speed_prev = %f,
	   ctx->dt = %f, ctx->off_road_decel = %f\n", ctx->off_road_limit,
		ctx->dt,
		speed_prev,
		ctx->dt,
		ctx->off_road_decel);*/


	// SDL_Log("[offroad] player_x = %f\n", ctx->player_x);


	speed_prev = ctx->speed;
	if ((ctx->player_x < -1 || ctx->player_x > 1) &&
	    ctx->speed > ctx->off_road_limit) {
		ctx->speed = inline_accelerate(
			ctx->speed, ctx->off_road_decel, ctx->dt);


		/*if (ctx->speed != speed_prev)
			SDL_Log("[offroad][off_road_limit=%f] speed : %f = %f +
		   %f * %f\n", ctx->off_road_limit, ctx->speed, speed_prev,
				ctx->dt,
				ctx->off_road_decel);*/
	}
	// SDL_Log("[%s] MID with speed = %d\n", __func__, ctx->speed);

	// don't let player go out of bounds
	ctx->player_x = inline_limit(ctx->player_x, -2, 2);
	// cap player speed
	ctx->speed = inline_limit(ctx->speed, 0, ctx->max_speed);


	/*SDL_Log("[%s] EXIT with player_x = %f, speed = %f\n",
		__func__,
		ctx->player_x,
		ctx->speed);*/


	ctx->player_y = /*ctx->segments[player_segment].p2.world.y;*/
		inline_interpolate(ctx->segments[player_segment].p1.world.y,
				   ctx->segments[player_segment].p2.world.y,
				   player_ratio);

	if (ctx->player_y - ctx->segments[player_segment].p2.world.y != 0)
		SDL_Log("[%s] player_y - p2.world.y = %f \n", __func__, ctx->player_y - ctx->segments[player_segment].p2.world.y);


	return 0;
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
	/*p->camera.x = (p->world.x || 0) - camera_x;
	p->camera.y = (p->world.y || 0) - camera_y;
	p->camera.z = (p->world.z || 0) - camera_z;*/
	p->camera.x = p->world.x - camera_x;
	p->camera.y = p->world.y - camera_y;
	p->camera.z = p->world.z - camera_z + first_segments_z_offset;

	/*if (p->camera.z < 0) {
		SDL_Log("[%s] p->camera.z = %f, p->world.z = %f, camera_z
	=%d\n",
		__func__, p->camera.z, p->world.z, camera_z);
	}*/


	// compute scaling factor
	if (p->camera.z != 0) // TODO: what about this case ?
		p->screen.scale = camera_depth / p->camera.z;
	else
		p->screen.scale = 1;


	// TODO: scaling num/den, rounding
	// scale coordinate to screen
	p->screen.x = /*Math.round(*/
		(width / 2) + (p->screen.scale * p->camera.x * width / 2) /*)*/;
	p->screen.y = /*Math.round(*/ (height / 2) -
		      (p->screen.scale * p->camera.y * height / 2) /*)*/;
	p->screen.w =
		/*Math.round(*/ (p->screen.scale * road_width * width /
				 2) /*)*/;

	// p->screen.y = p->screen.y * 98 / 100;
	// p->screen.y = p->screen.y;

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
	case GAME_STATE_GAME:
		logic_game(ctx);
		break;
	case GAME_STATE_QUIT:
	case GAME_STATE_PAUSE:
	case GAME_STATE_GAMEOVER:
	default:
		break;
	}

	return 0;
}