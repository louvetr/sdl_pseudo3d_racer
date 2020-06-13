#include "main.h"


static int display_menu_sliding_grid(SDL_Renderer *renderer,
				     int width_num,
				     int width_den,
				     int x_gap,
				     int y_gap,
				     int *cpt,
				     int cpt_increment,
				     int x_dir,
				     int y_dir,
				     int R,
				     int G,
				     int B)
{

	// static uint32_t cpt = 0;
	SDL_Rect r;
	int width = SCREEN_HEIGHT * width_num / width_den;

	int i = *cpt % (y_gap);
	int j = *cpt % (x_gap);

	SDL_SetRenderDrawColor(renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);

	if (y_dir > 0) {
		int y = i;
		while (y < SCREEN_HEIGHT + width) {
			r.x = 0;
			r.y = y - width;
			r.w = SCREEN_WIDTH;
			r.h = width;
			SDL_RenderFillRect(renderer, &r);
			y = y + y_gap;
		}
	} else {
		int y = SCREEN_HEIGHT - i + width;
		while (y > 0 - width) {
			r.x = 0;
			r.y = y - width;
			r.w = SCREEN_WIDTH;
			r.h = width;
			SDL_RenderFillRect(renderer, &r);
			y = y - y_gap;
		}
	}

	if (x_dir > 0) {
		int x = j;
		while (x < SCREEN_WIDTH + width) {
			r.x = x - width;
			r.y = 0;
			r.w = width;
			r.h = SCREEN_HEIGHT;
			SDL_RenderFillRect(renderer, &r);
			x = x + x_gap;
		}
	} else {
		int x = SCREEN_WIDTH - j + width;
		while (x > 0 - width) {
			r.x = x - width;
			r.y = 0;
			r.w = width;
			r.h = SCREEN_HEIGHT;
			SDL_RenderFillRect(renderer, &r);
			x = x - x_gap;
		}
	}

	*cpt += cpt_increment;

	if (*cpt < 0)
		*cpt = 0;

	return 0;
}


static int display_menu_animated_background(struct game_context *ctx)
{
	static int cpt1 = 0;
	static int cpt2 = 0;

	/*int y_gap_1 = SCREEN_HEIGHT / 5;
	int x_gap_1 = SCREEN_WIDTH / 7;*/

	int y_gap_2 = SCREEN_HEIGHT / 2;
	int x_gap_2 = SCREEN_WIDTH / 3;

	display_menu_sliding_grid(ctx->renderer,
				  100, // 140,
				  10000,
				  x_gap_2,
				  y_gap_2,
				  &cpt1,
				  2,
				  1,
				  1,
				  0,
				  0,
				  255);

	display_menu_sliding_grid(ctx->renderer,
				  100,
				  10000,
				  x_gap_2,
				  y_gap_2,
				  &cpt2,
				  2,
				  -1,
				  -1,
				  0 /*220*/,
				  0 /*220*/,
				  255 /*0*/);

	return 0;
};

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

	texture_render(ctx,
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

	// animated background
	display_menu_animated_background(ctx);

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

	// animated background
	display_menu_animated_background(ctx);

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

	// animated background
	display_menu_animated_background(ctx);

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


int display_screen_title(struct game_context *ctx)
{
	int ret = 0;
	static int clkcpt = 0;
	static int invcolors = 0;
	int nb_seg = 10;
	int segw = SCREEN_WIDTH / nb_seg;
	SDL_Rect r;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 135, 206, 235, 0xFF); // blue sky
	SDL_RenderClear(ctx->renderer);

	filledCircleRGBA(ctx->renderer,
			 (int16_t)(SCREEN_WIDTH * 85 / 100),
			 (int16_t)(SCREEN_HEIGHT * 15 / 100),
			 SCREEN_HEIGHT * 10 / 100,
			 250,
			 253,
			 15,
			 255);


	// draw grass
	r.x = 0;
	r.y = SCREEN_HEIGHT * 50 / 100;
	r.w = segw;
	r.h = SCREEN_HEIGHT * 7 / 100;

	for (int i = 0; i < nb_seg + nb_seg / 2; i++) {
		if (i % 2 == invcolors)
			SDL_SetRenderDrawColor(ctx->renderer, 0, 160, 0, 255);
		else
			SDL_SetRenderDrawColor(ctx->renderer, 0, 169, 0, 255);

		r.x = i * segw - clkcpt;
		SDL_RenderFillRect(ctx->renderer, &r);
	}

	// draw rumble
	r.x = 0;
	r.y = SCREEN_HEIGHT * 57 / 100;
	r.w = segw;
	r.h = SCREEN_HEIGHT * 4 / 100;
	for (int i = 0; i < nb_seg + nb_seg / 2; i++) {

		if (i % 2 == invcolors)
			SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(
				ctx->renderer, 255, 255, 255, 255);

		r.x = i * segw - clkcpt;
		SDL_RenderFillRect(ctx->renderer, &r);
	}

	// draw road
	r.x = 0;
	r.y = SCREEN_HEIGHT * 60 / 100;
	r.w = segw;
	r.h = SCREEN_HEIGHT * 40 / 100;

	for (int i = 0; i < nb_seg + nb_seg / 2; i++) {
		if (i % 2 == invcolors)
			SDL_SetRenderDrawColor(
				ctx->renderer, 125, 125, 125, 255);
		else
			SDL_SetRenderDrawColor(
				ctx->renderer, 140, 140, 140, 255);

		r.x = i * segw - clkcpt;
		SDL_RenderFillRect(ctx->renderer, &r);
	}

	// draw clouds
	static int cloud_x_offset = 0;

	display_render_background_layer(
		ctx, BG_LAYER_SKY_FAR, &cloud_x_offset, &ctx->gfx.bg_sky_far);

	cloud_x_offset += 4;

	// draw trees
	float scale_oak = 0.5f;
	int nb_oak = 4;
	int segw_oak =
		(int)((float)ctx->gfx.scene_tree_oak.h * scale_oak) * 3 / 2;

	for (int i = 0; i < nb_oak; i++) {
		r.x = i * segw_oak - clkcpt;
		ret = texture_render(
			ctx,
			&ctx->gfx.scene_tree_oak,
			r.x,
			SCREEN_HEIGHT * 53 / 100 -
				(int)((float)ctx->gfx.scene_tree_oak.h *
				      scale_oak),
			NULL,
			0.f,
			scale_oak,
			SDL_FLIP_NONE,
			NULL);
	}

	// draw cars
	static int x_car_cpt = 0;
	float scale_car = 0.33f;
	static int car_model = CAR_MODEL_DELTA;
	static int y_car = 70;
	int x_car =
		-1 * (int)((float)ctx->gfx.cars_side[car_model].w * scale_car);
	x_car += x_car_cpt;

	ret = texture_render(
		ctx,
		&ctx->gfx.cars_side[car_model],
		x_car,
		SCREEN_HEIGHT * y_car / 100 -
			(int)((float)ctx->gfx.cars_side[car_model].h *
			      scale_car),
		NULL,
		0.f,
		scale_car,
		SDL_FLIP_NONE,
		NULL);


	clkcpt += 20;
	if (clkcpt > segw_oak) {
		clkcpt = 0;
		invcolors = invcolors ? 0 : 1;
	}
	if (clkcpt % segw == 0)
		invcolors = invcolors ? 0 : 1;

	x_car_cpt += 80;
	if (x_car_cpt >
	    SCREEN_WIDTH +
		    (int)((float)ctx->gfx.cars_side[car_model].w * scale_car)) {
		x_car_cpt = 0;
		car_model = car_model == CAR_MODEL_IMPREZIA
				    ? CAR_MODEL_DELTA
				    : CAR_MODEL_IMPREZIA;

		y_car = 69 + (rand() % 6) * 5;
	}


	// Title /////////////////////////////////////////

	SDL_Color text_color_front_1 = {0xFF, 0xFF, 0x0};
	SDL_Color text_color_shadow = {0, 0, 0};
	int finish_font_size;
	TTF_Font *finish_font = NULL;
	float angle;

	ctx->race.nb_frame_anim++;

	finish_font_size = ctx->race.nb_frame_anim * 2;
	if (finish_font_size > 150)
		finish_font_size = 150;

	angle = (float)ctx->race.nb_frame_anim * 8.f;
	if (angle > 360.f) {
		angle = 0.f;
		if (ctx->race.finish_placed_frame_nb == 0) {
			ctx->race.finish_placed_frame_nb =
				ctx->race.nb_frame_anim;
		}
	}

	finish_font = TTF_OpenFont(SOFACHROME_FONT, finish_font_size);
	if (!finish_font) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		"Bala ",
		&text_color_front_1,
		&text_color_shadow,
		SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim.w / 2,
		SCREEN_HEIGHT * 40 / 100 - ctx->gfx.font_race_anim.h / 2,
		4,
		200,
		angle);

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		" Race",
		&text_color_front_1,
		&text_color_shadow,
		SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim.w / 2,
		SCREEN_HEIGHT * 40 / 100 + ctx->gfx.font_race_anim.h / 2,
		4,
		200,
		angle);

	SDL_RenderPresent(ctx->renderer);
	TTF_CloseFont(finish_font);

	return ret;
}