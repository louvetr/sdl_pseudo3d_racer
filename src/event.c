#include "common.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

#if 0
static int event_game(struct game_context *ctx)
{
	static int cpt = 0;

	ctx->ts_cur = SDL_GetTicks();
	ctx->dt = (ctx->ts_cur - ctx->ts_prev);

	/*SDL_Log("[%s][position = %d] ENTER with accel = %d, dt = %d, speed =
	   %d\n",
		__func__,
		ctx->position,
		ctx->accel,
		ctx->dt,
		ctx->speed);*/

	if (ctx->action == ACTION_LEFT)
		cpt++;

	ctx->ts_prev = ctx->ts_cur;

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

	if (ctx->action == ACTION_LEFT)
		ctx->player_x = ctx->player_x - dx;
	else if (ctx->action == ACTION_RIGHT)
		ctx->player_x = ctx->player_x + dx;

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

	if (ctx->action == ACTION_UP) {
		ctx->speed = inline_accelerate(ctx->speed, ctx->accel, ctx->dt);
		if (ctx->speed != speed_prev)
			SDL_Log("[accel] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);
	} else if (ctx->action == ACTION_DOWN) {
		ctx->speed =
			inline_accelerate(ctx->speed, ctx->breaking, ctx->dt);
		if (ctx->speed != speed_prev)
			SDL_Log("[breaking] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);
	} else {
		ctx->speed = inline_accelerate(ctx->speed, ctx->decel, ctx->dt);
		/*if (ctx->speed != speed_prev)
			SDL_Log("[decel] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);*/
	}

	if ((ctx->player_x < -1 || ctx->player_x > 1) &&
	    ctx->speed > ctx->off_road_limit) {
		ctx->speed = inline_accelerate(
			ctx->speed, ctx->off_road_decel, ctx->dt);
		if (ctx->speed != speed_prev)
			SDL_Log("[offroad] speed : %f = %f + %f * %f\n",
				ctx->speed,
				speed_prev,
				ctx->accel,
				ctx->dt);
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

	switch (ctx->action) {
	case ACTION_ESCAPE:
		// go back to title
		SDL_Log("[%s] event ACTION_ESCAPE\n", __func__);
		break;
	case ACTION_ENTER:
		break;
	case ACTION_PAUSE:
		break;
	case ACTION_UP:
		SDL_Log("[%s] event ACTION_UP\n", __func__);
		break;
	case ACTION_DOWN:
		SDL_Log("[%s] event ACTION_DOWN\n", __func__);
		break;
	case ACTION_DOWN_RELEASED:
		SDL_Log("[%s] event ACTION_DOWN_RELEASED\n", __func__);
		break;
	case ACTION_LEFT:
		SDL_Log("[%s] event ACTION_LEFT\n", __func__);
		break;
	case ACTION_RIGHT:
		SDL_Log("[%s] event ACTION_RIGHT\n", __func__);
		break;
	default:
		break;
	}

	cpt++;

	return 0;
}
#endif

static int event_game(struct game_context *ctx)
{
	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYDOWN) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_SPACE:
				ctx->keys.nitro = 1;
				break;
			case SDLK_UP:
			case SDLK_z:
				ctx->keys.accel = 1;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->keys.brake = 1;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->keys.left = 1;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->keys.right = 1;
				break;
			default:
				continue;
			}
		}

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ctx->action = ACTION_ESCAPE;
				break;
			case SDLK_RETURN:
				ctx->action = ACTION_ENTER;
				break;
			case SDLK_SPACE:
				ctx->keys.nitro = 0;
				break;
			case SDLK_UP:
			case SDLK_z:
				ctx->keys.accel = 0;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->keys.brake = 0;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->keys.left = 0;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->keys.right = 0;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////

int main_event(struct game_context *ctx)
{

	// SDL_Log("[%s] ENTER\n", __func__);

	if (!ctx) {
		SDL_Log("invalid parameter\n");
		return -EINVAL;
	}

#if 0
	// SDL_Log("[%s] line %d\n", __func__, __LINE__);

	// special case for when entering the game
	if (ctx->status_cur == GAME_STATE_TITLE &&
	    ctx->status_prev == GAME_STATE_UNKNOWN) {
		// event_enter_title(ctx);
		ctx->status_prev = GAME_STATE_TITLE;
	}

	// SDL_Log("[%s] line %d\n", __func__, __LINE__);
	int nb_actions = 0;

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYDOWN) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ctx->action = ACTION_ESCAPE;
				break;
			case SDLK_RETURN:
				ctx->action = ACTION_ENTER;
				break;
			case SDLK_SPACE:
				ctx->action = ACTION_PAUSE;
				break;
			case SDLK_UP:
			case SDLK_z:
				ctx->action = ACTION_UP;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->action = ACTION_DOWN;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->action = ACTION_LEFT;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->action = ACTION_RIGHT;
				break;
			default:
				if (ctx->status_cur != GAME_STATE_GAME)
					continue;
			}
		}
		// SDL_Log("[%s] line %d\n", __func__, __LINE__);

		/*if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_DOWN:
			case SDLK_s:
				ctx->action = ACTION_DOWN_RELEASED;
				break;
			default:
				continue;
			}
		}*/
		// SDL_Log("[%s] line %d\n", __func__, __LINE__);

		switch (ctx->status_cur) {
		case GAME_STATE_TITLE:
			break;
		case GAME_STATE_QUIT:
			break;
		case GAME_STATE_GAME:
			event_game(ctx);
			//nb_actions++;
			break;
		case GAME_STATE_PAUSE:
			break;
		case GAME_STATE_GAMEOVER:
			break;
		default:
			continue;
		}
	}
#endif

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_QUIT:
		break;
	case GAME_STATE_GAME:
		event_game(ctx);
		break;
	case GAME_STATE_PAUSE:
		break;
	case GAME_STATE_GAMEOVER:
		break;
	default:
		break;
	}

	// SDL_Log("[%s] EXIT, nb_actions = %d\n", __func__, nb_actions);
	return 0;
}