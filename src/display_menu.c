#include "main.h"

int display_screen_menu_car_select(struct game_context *ctx)
{
	int ret;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 100, 100, 100, 0xFF); // blue sky
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