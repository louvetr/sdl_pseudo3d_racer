#include "common.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

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