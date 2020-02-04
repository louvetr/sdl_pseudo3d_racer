#include "common.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


static int event_game(struct game_context *ctx)
{
	ctx->ts_cur = SDL_GetTicks();
	ctx->dt = ctx->ts_cur - ctx->ts_prev;
	ctx->ts_prev = ctx->ts_cur;

	// TODO: DEBUG
	if (ctx->action != ACTION_UP)
		return 0;

	/*SDL_Log("[%s][position = %d] ENTER with accel = %d, dt = %d, speed = %d\n",
		__func__,
		ctx->position,
		ctx->accel,
		ctx->dt,
		ctx->speed);*/

	ctx->position = inline_increase(
		ctx->position, ctx->dt * ctx->speed, ctx->track_length);

	// scrren crossing should take 1sec at top speed
	int dx = ctx->dt * 2 * (ctx->speed / ctx->max_speed);


	if (ctx->action == ACTION_LEFT)
		ctx->player_x = ctx->player_x - dx;
	else if (ctx->action == ACTION_RIGHT)
		ctx->player_x = ctx->player_x + dx;

	if (ctx->action == ACTION_UP)
		ctx->speed = inline_accelerate(ctx->speed, ctx->accel, ctx->dt);
	else if (ctx->action == ACTION_DOWN)
		ctx->speed =
			inline_accelerate(ctx->speed, ctx->breaking, ctx->dt);
	else
		ctx->speed = inline_accelerate(ctx->speed, ctx->decel, ctx->dt);

	if ((ctx->player_x < -1 || ctx->player_x > 1) &&
	    ctx->speed > ctx->off_road_limit)
		ctx->speed = inline_accelerate(
			ctx->speed, ctx->off_road_decel, ctx->dt);

	//SDL_Log("[%s] MID with speed = %d\n", __func__, ctx->speed);

	// don't let player go out of bounds
	ctx->player_x = inline_limit(ctx->player_x, -2, 2);
	// cap player speed
	ctx->speed = inline_limit(ctx->speed, 0, ctx->max_speed);


	//SDL_Log("[%s] EXIT with speed = %d\n", __func__, ctx->speed);

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
		//SDL_Log("[%s] event ACTION_UP\n", __func__);
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

	// SDL_Log("[%s] line %d\n", __func__, __LINE__);

	// special case for when entering the game
	if (ctx->status_cur == GAME_STATE_TITLE &&
	    ctx->status_prev == GAME_STATE_UNKNOWN) {
		// event_enter_title(ctx);
		ctx->status_prev = GAME_STATE_TITLE;
	}

	// SDL_Log("[%s] line %d\n", __func__, __LINE__);

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

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_DOWN:
			case SDLK_s:
				ctx->action = ACTION_DOWN_RELEASED;
				break;
			default:
				continue;
			}
		}
		// SDL_Log("[%s] line %d\n", __func__, __LINE__);

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
			continue;
		}
	}

	// SDL_Log("[%s] EXIT\n", __func__);
	return 0;
}