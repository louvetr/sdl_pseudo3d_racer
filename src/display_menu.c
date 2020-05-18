#include "main.h"

int display_screen_menu_select_car(struct game_context *ctx)
{
	int ret = 0;
	float scale_car = 0.33f;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 200, 200, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {
		.x = SCREEN_WIDTH / 4 - SCREEN_WIDTH * 10 / 100,
		.y = 0,
		.w = SCREEN_WIDTH * 20 / 100,
		.h = SCREEN_HEIGHT
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	ret = texture_render(
		ctx,
		&ctx->gfx.cars_side[ctx->pcar.car_player_model],
		SCREEN_WIDTH / 4 -
			(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].w *
				scale_car / 2),
		SCREEN_HEIGHT / 2 -
			(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].h *
				scale_car / 2.f),
		NULL,
		0.f,
		scale_car,
		0,
		NULL);

	SDL_RenderPresent(ctx->renderer);

	return ret;
}


int display_screen_menu_select_track(struct game_context *ctx)
{
	int ret = 0;
	float scale_track = 0.33f;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 200, 200, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {
		.x = SCREEN_WIDTH * 3 / 4 - SCREEN_WIDTH * 10 / 100,
		.y = 0,
		.w = SCREEN_WIDTH * 20 / 100,
		.h = SCREEN_HEIGHT
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	ret = texture_render(
		ctx,
		&ctx->gfx.track_thumbnail[ctx->track.track_selected],
		SCREEN_WIDTH * 3 / 4 -
			(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected].w *
				scale_track / 2),
		SCREEN_HEIGHT / 2 -
			(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected].h *
				scale_track / 2.f),
		NULL,
		0.f,
		scale_track,
		0,
		NULL);


	SDL_RenderPresent(ctx->renderer);

	return ret;
}


int display_screen_menu_main(struct game_context *ctx)
{
	int ret = 0;
	float scale_track = 0.33f;
	float scale_car = 0.33f;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 200, 200, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {
		.x = 0,
		.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT * 10 / 100,
		.w = SCREEN_WIDTH,
		.h = SCREEN_HEIGHT * 20 / 100,
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	ret = texture_render(
		ctx,
		&ctx->gfx.cars_side[ctx->pcar.car_player_model],
		SCREEN_WIDTH / 4 -
			(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].w *
				scale_car / 2.f),
		SCREEN_HEIGHT / 2 -
			(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].h *
				scale_car / 2.f),
		NULL,
		0.f,
		scale_car,
		0,
		NULL);

	ret = texture_render(
		ctx,
		&ctx->gfx.track_thumbnail[ctx->track.track_selected],
		SCREEN_WIDTH * 3 / 4 -
			(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected].w *
				scale_track / 2.f),
		SCREEN_HEIGHT / 2 -
			(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected].h *
				scale_track / 2.f),
		NULL,
		0.f,
		scale_track,
		0,
		NULL);


	SDL_RenderPresent(ctx->renderer);

	return ret;
}