#include "main.h"

int display_screen_menu_select_car(struct game_context *ctx)
{
	int ret;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 255, 0xFF);
	SDL_RenderClear(ctx->renderer);

	ret = texture_render(ctx,
			     &ctx->gfx.cars_side[ctx->pcar.car_player_model],
			     0,
			     0,
			     NULL,
			     0.f,
			     0.5f,
			     0,
			     NULL);


	SDL_RenderPresent(ctx->renderer);

	return ret;
}


int display_screen_menu_select_track(struct game_context *ctx)
{
	int ret;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 255, 0xFF);
	SDL_RenderClear(ctx->renderer);

	ret = texture_render(ctx,
			     &ctx->gfx.track_thumbnail[ctx->track.track_selected],
			     0,
			     0,
			     NULL,
			     0.f,
			     1.f,
			     0,
			     NULL);


	SDL_RenderPresent(ctx->renderer);

	return ret;
}
