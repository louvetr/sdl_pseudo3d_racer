#include "main.h"

static int display_screen_rect_border(struct game_context *ctx,
				      int x0,
				      int y0,
				      int x1,
				      int y1,
				      int x2,
				      int y2,
				      int x3,
				      int y3,
				      int width,
				      int R,
				      int G,
				      int B)
{
	SDL_Rect r;

	SDL_SetRenderDrawColor(
		ctx->renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);

	r.x = x0 - width;
	r.y = y0 - width;
	r.w = width;
	r.h = y2 - y0 + width * 2;
	SDL_RenderFillRect(ctx->renderer, &r);

	r.x = x1;
	r.y = y1 - width;
	r.w = width;
	r.h = y2 - y1 + width * 2;
	SDL_RenderFillRect(ctx->renderer, &r);

	r.x = x0;
	r.y = y0 - width;
	r.w = x1 - x0;
	r.h = width;
	SDL_RenderFillRect(ctx->renderer, &r);

	r.x = x2;
	r.y = y2;
	r.w = x3 - x2;
	r.h = width;
	SDL_RenderFillRect(ctx->renderer, &r);

	return 0;
}

static int display_menu_car_bordered_pict(struct game_context *ctx)
{
	int bwidth = 5;

	float scale_car =
		(float)SCREEN_WIDTH / 1.8f /
		(float)ctx->gfx.cars_side[ctx->pcar.car_player_model].w;

	int car_x =
		SCREEN_WIDTH * 30 / 100 -
		(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].w *
		      scale_car / 2.f);
	int car_y =
		SCREEN_HEIGHT / 2 -
		(int)((float)ctx->gfx.cars_side[ctx->pcar.car_player_model].h *
		      scale_car / 2.f);

	texture_render(ctx,
			     &ctx->gfx.cars_side[ctx->pcar.car_player_model],
			     car_x,
			     car_y,
			     NULL,
			     0.f,
			     scale_car,
			     0,
			     NULL);

	display_screen_rect_border(
		ctx,
		car_x,
		car_y,
		car_x + (int)((float)ctx->gfx
				      .cars_side[ctx->pcar.car_player_model]
				      .w *
			      scale_car),
		car_y,
		car_x,
		car_y + (int)((float)ctx->gfx
				      .cars_side[ctx->pcar.car_player_model]
				      .h *
			      scale_car),
		car_x + (int)((float)ctx->gfx
				      .cars_side[ctx->pcar.car_player_model]
				      .w *
			      scale_car),
		car_y,
		bwidth,
		0,
		0,
		0);

	return 0;
}


static int display_menu_track_bordered_pict(struct game_context *ctx)
{
	int bwidth = 5;

	float scale_track =
		(float)SCREEN_WIDTH / 3.0f /
		(float)ctx->gfx.track_thumbnail[ctx->track.track_selected].w;

	int track_x =
		SCREEN_WIDTH * 80 / 100 -
		(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected]
			      .w *
		      scale_track / 2.f);

	int track_y =
		SCREEN_HEIGHT / 2 -
		(int)((float)ctx->gfx.track_thumbnail[ctx->track.track_selected]
			      .h *
		      scale_track / 2.f);

	texture_render(
		ctx,
		&ctx->gfx.track_thumbnail[ctx->track.track_selected],
		track_x,
		track_y,
		NULL,
		0.f,
		scale_track,
		0,
		NULL);

	display_screen_rect_border(
		ctx,
		track_x,
		track_y,
		track_x +
			(int)((float)ctx->gfx
				      .track_thumbnail[ctx->track
							       .track_selected]
				      .w *
			      scale_track),
		track_y,
		track_x,
		track_y +
			(int)((float)ctx->gfx
				      .track_thumbnail[ctx->track
							       .track_selected]
				      .h *
			      scale_track),
		track_x +
			(int)((float)ctx->gfx
				      .track_thumbnail[ctx->track
							       .track_selected]
				      .w *
			      scale_track),
		track_y,
		bwidth,
		0,
		0,
		0);

	return 0;
}


int display_screen_menu_select_car(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {.x = SCREEN_WIDTH * 30 / 100 - SCREEN_WIDTH * 10 / 100,
		      .y = 0,
		      .w = SCREEN_WIDTH * 20 / 100,
		      .h = SCREEN_HEIGHT};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_car_bordered_pict(ctx);

	SDL_RenderPresent(ctx->renderer);

	return ret;
}


int display_screen_menu_select_track(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {.x = SCREEN_WIDTH * 80 / 100 - SCREEN_WIDTH * 10 / 100,
		      .y = 0,
		      .w = SCREEN_WIDTH * 20 / 100,
		      .h = SCREEN_HEIGHT};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_track_bordered_pict(ctx);

	SDL_RenderPresent(ctx->renderer);

	return ret;
}


int display_screen_menu_main(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	SDL_Rect r = {
		.x = 0,
		.y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT * 10 / 100,
		.w = SCREEN_WIDTH,
		.h = SCREEN_HEIGHT * 20 / 100,
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_car_bordered_pict(ctx);
	
	display_menu_track_bordered_pict(ctx);

	SDL_RenderPresent(ctx->renderer);

	return ret;
}