#include "main.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

static int event_race(struct game_context *ctx)
{
	ctx->keys.back = 0;

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
			case SDLK_ESCAPE:
				exit(0);
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
			case SDLK_KP_ENTER:
				ctx->keys.option = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}


static int event_menu_select_car(struct game_context *ctx)
{

	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ctx->action = ACTION_ESCAPE;
				break;
			case SDLK_RETURN:
				ctx->action = ACTION_ENTER;
				break;
			case SDLK_SPACE:
				ctx->keys.select = 1;
				break;
			case SDLK_UP:
			case SDLK_z:
				ctx->keys.up = 1;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->keys.down = 1;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->keys.left = 1;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->keys.right = 1;
				break;
			case SDLK_BACKSPACE:
				ctx->keys.back = 1;
				break;
			case SDLK_c:
				ctx->keys.credit = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}

static int event_menu_option(struct game_context *ctx)
{

	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ctx->action = ACTION_ESCAPE;
				break;
			case SDLK_RETURN:
				ctx->action = ACTION_ENTER;
				break;
			case SDLK_SPACE:
				ctx->keys.select = 1;
				break;
			case SDLK_UP:
			case SDLK_z:
				ctx->keys.up = 1;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->keys.down = 1;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->keys.left = 1;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->keys.right = 1;
				break;
			case SDLK_8:
			case SDLK_KP_8:
				ctx->keys.volume_music = 1;
				break;
			case SDLK_5:
			case SDLK_KP_5:
				ctx->keys.volume_sfx = 1;
				break;
			case SDLK_2:
			case SDLK_KP_2:
				ctx->keys.reset_save = 1;
				break;
			case SDLK_BACKSPACE:
				ctx->keys.back = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}

static int event_menu_credit(struct game_context *ctx)
{

	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_BACKSPACE:
				ctx->keys.back = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}

static int event_race_option(struct game_context *ctx)
{

	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_8:
			case SDLK_KP_8:
				ctx->keys.volume_music = 1;
				break;
			case SDLK_5:
			case SDLK_KP_5:
				ctx->keys.volume_sfx = 1;
				break;
			case SDLK_2:
			case SDLK_KP_2:
				ctx->keys.exit = 1;
				break;
			case SDLK_KP_ENTER:
				ctx->keys.back = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}

static int event_race_anim_end(struct game_context *ctx)
{
	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		/*if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;*/

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				ctx->keys.exit = 1;
				break;
			default:
				continue;
			}
		}
	}

	return 0;
}



static int event_menu_title(struct game_context *ctx)
{

	memset(&ctx->keys, 0, sizeof(struct keys_status));

	while (SDL_PollEvent(&ctx->event) != 0) {
		if (ctx->event.type == SDL_QUIT)
			ctx->exit = 1;

		if (ctx->event.type == SDL_KEYUP) {
			switch (ctx->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ctx->action = ACTION_ESCAPE;
				break;
			/*case SDLK_RETURN:
				ctx->action = ACTION_ENTER;
				break;*/
			case SDLK_SPACE:
				ctx->keys.select = 1;
				break;
			/*case SDLK_UP:
			case SDLK_z:
				ctx->keys.up = 1;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				ctx->keys.down = 1;
				break;
			case SDLK_LEFT:
			case SDLK_q:
				ctx->keys.left = 1;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				ctx->keys.right = 1;
				break;
			case SDLK_BACKSPACE:
				ctx->keys.back = 1;
				break;*/
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

int event_update_game_state(struct game_context *ctx, enum game_status state)
{
	SDL_Log("[%s] switch state from #%d to #%d\n",
		__func__,
		ctx->status_cur,
		state);
	ctx->status_prev = ctx->status_cur;
	ctx->status_cur = state;
	return 0;
}

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
		event_menu_title(ctx);
		break;
	case GAME_STATE_QUIT:
		break;
	case GAME_STATE_MENU_MAIN:
	case GAME_STATE_MENU_SELECT_TRACK:
	case GAME_STATE_MENU_SELECT_CAR:
		event_menu_select_car(ctx);
		break;
	case GAME_STATE_MENU_OPTION:
		event_menu_option(ctx);
		break;
	case GAME_STATE_MENU_CREDIT:
		event_menu_credit(ctx);
		break;
	case GAME_STATE_RACE_OPTION:
		event_race_option(ctx);
		break;
	case GAME_STATE_RACE:
	case GAME_STATE_RACE_NITRO:
	case GAME_STATE_RACE_COLLISION_SCENE:
		event_race(ctx);
		break;
	case GAME_STATE_RACE_ANIM_UNLOCK:
	case GAME_STATE_RACE_ANIM_END:
		event_race_anim_end(ctx);
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
