#include "main.h"


#define CREDIT_MUSIC_01 "'Infinity' by Aries Beats"
#define CREDIT_MUSIC_02 "'Turbo Rush' by Aries Beats"
#define CREDIT_MUSIC_03 "'In the 1980s' by Simon Bichbihler"
#define CREDIT_MUSIC_04 "'Sunrise Over Los Angeles' by TeknoAXE"
#define CREDIT_MUSIC_05 "'Starting Line' by Eric Matyas"
#define CREDIT_MUSIC_06 "'Racing Menu' by Eric Matyas"

#define CREDIT_SFX_01 "'drifting tires sound' by audible-edge"
#define CREDIT_SFX_02 "'Lap notification sound' from 'stunt rally' game"

#define CREDIT_MUSIC_NB 6
#define CREDIT_SFX_NB 2

#define DEFAULT_BEST_TIME "--'--\"--"
#define DEFAULT_BEST_POSITION "?"


static char *CREDIT_MUSIC_TAB[CREDIT_MUSIC_NB] = {CREDIT_MUSIC_01,
						  CREDIT_MUSIC_02,
						  CREDIT_MUSIC_03,
						  CREDIT_MUSIC_04,
						  CREDIT_MUSIC_05,
						  CREDIT_MUSIC_06};

static char *CREDIT_SFX_TAB[CREDIT_SFX_NB] = {CREDIT_SFX_01, CREDIT_SFX_02};

enum track_desc_item {
	TRACK_DESC_NAME,
	TRACK_DESC_DIFFICULTY,
	TRACK_DESC_LENGTH,
	TRACK_DESC_LAST,
};


static char *track_desc_tab[TRACK_LAST][TRACK_DESC_LAST] = {
	{"Countryside", "Easy", "2.570 km"},
	{"Sea Shore", "Easy", "2.400 km"},
	{"Great Canyon", "Easy", "2.700 km"},
	{"Arctic Circle", "Medium", "3.200 km"},
	{"Ionic Ruins", "Medium", "2.725 km"},
	{"Castle Forest", "Medium", "2.850 km"},
	{"Desert", "Hard", "2.850 km"},
	{"Soopky Woods", "Hard", "3.450 km"},
	{"City", "Expert", "3.080 km"},
	{"Fun Fair", "Expert", "3.300 km"},
};


static int display_menu_sliding_grid(struct display_info display,
				     SDL_Renderer *renderer,
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
	int width = display.screen_height * width_num / width_den;

	int i = *cpt % (y_gap);
	int j = *cpt % (x_gap);

	SDL_SetRenderDrawColor(renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);

	if (y_dir > 0) {
		int y = i;
		while (y < display.screen_height + width) {
			r.x = 0;
			r.y = y - width;
			r.w = display.screen_width;
			r.h = width;
			SDL_RenderFillRect(renderer, &r);
			y = y + y_gap;
		}
	} else {
		int y = display.screen_height - i + width;
		while (y > 0 - width) {
			r.x = 0;
			r.y = y - width;
			r.w = display.screen_width;
			r.h = width;
			SDL_RenderFillRect(renderer, &r);
			y = y - y_gap;
		}
	}

	if (x_dir > 0) {
		int x = j;
		while (x < display.screen_width + width) {
			r.x = x - width;
			r.y = 0;
			r.w = width;
			r.h = display.screen_height;
			SDL_RenderFillRect(renderer, &r);
			x = x + x_gap;
		}
	} else {
		int x = display.screen_width - j + width;
		while (x > 0 - width) {
			r.x = x - width;
			r.y = 0;
			r.w = width;
			r.h = display.screen_height;
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

	int y_gap_2 = ctx->display.screen_height / 2;
	int x_gap_2 = ctx->display.screen_width / 3;

	display_menu_sliding_grid(ctx->display,
				  ctx->renderer,
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

	display_menu_sliding_grid(ctx->display,
				  ctx->renderer,
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

static int display_menu_stats_bordered_pict(struct game_context *ctx)
{
	int bwidth = 5;

	float scale_car =
		(float)ctx->display.screen_width / 3.2f /
		(float)ctx->gfx.cars_stats[ctx->pcar.car_player_model].w;

	int car_x =
		ctx->display.screen_width * 80 / 100 -
		(int)((float)ctx->gfx.cars_stats[ctx->pcar.car_player_model].w *
		      scale_car / 2.f);
	int car_y =
		ctx->display.screen_height / 2 -
		(int)((float)ctx->gfx.cars_stats[ctx->pcar.car_player_model].h *
		      scale_car / 2.f);

	texture_render(ctx,
		       &ctx->gfx.cars_stats[ctx->pcar.car_player_model],
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
				      .cars_stats[ctx->pcar.car_player_model]
				      .w *
			      scale_car),
		car_y,
		car_x,
		car_y + (int)((float)ctx->gfx
				      .cars_stats[ctx->pcar.car_player_model]
				      .h *
			      scale_car),
		car_x + (int)((float)ctx->gfx
				      .cars_stats[ctx->pcar.car_player_model]
				      .w *
			      scale_car),
		car_y,
		bwidth,
		0,
		0,
		0);

	return 0;
}

int display_menu_car_bordered_pict(struct game_context *ctx,
				   enum car_model_type car,
				   int centered)
{
	int bwidth = 5;
	int offset = centered ? 50 : 30;

	int car_bg_x = ctx->display.screen_width * offset / 100 -
		       (int)((float)ctx->gfx.car_side_bg.w / 2.f);
	int car_bg_y = ctx->display.screen_height / 2 -
		       (int)((float)ctx->gfx.car_side_bg.h / 2.f);

	texture_render(ctx,
		       &ctx->gfx.car_side_bg,
		       car_bg_x,
		       car_bg_y,
		       NULL,
		       0.f,
		       1.f,
		       0,
		       NULL);

	float scale_car = (float)ctx->gfx.car_side_bg.w /
			  (float)ctx->gfx.cars_side[car].w;
	int car_x = car_bg_x + ctx->gfx.car_side_bg.w / 2 -
		    ctx->gfx.cars_side[car].w / 2 * ctx->gfx.car_side_bg.w /
			    ctx->gfx.cars_side[car].w;
	int car_y = car_bg_y + ctx->gfx.car_side_bg.h / 2 -
		    ctx->gfx.cars_side[car].h / 2 * ctx->gfx.car_side_bg.w /
			    ctx->gfx.cars_side[car].w;

	texture_render(ctx,
		       &ctx->gfx.cars_side[car],
		       car_x,
		       car_y,
		       NULL,
		       0.f,
		       scale_car,
		       0,
		       NULL);

	display_screen_rect_border(
		ctx,
		car_bg_x,
		car_bg_y,
		car_bg_x + (int)((float)ctx->gfx.car_side_bg.w),
		car_bg_y,
		car_bg_x,
		car_bg_y + (int)((float)ctx->gfx.car_side_bg.h),
		car_bg_x + (int)((float)ctx->gfx.car_side_bg.w),
		car_bg_y,
		bwidth,
		0,
		0,
		0);


	if (!(1 << ctx->pcar.car_player_model & ctx->save.cars_available) &&
	    ctx->status_cur == GAME_STATE_MENU_SELECT_CAR) {

		SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 150);
		/*SDL_BlendMode blendMode;
		SDL_GetRenderDrawBlendMode(ctx->renderer, &blendMode);
		SDL_Log("blendMode = %d\n", blendMode);*/
		SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);
		SDL_Rect r = {
			.x = car_bg_x,
			.y = car_bg_y,
			.w = (int)((float)ctx->gfx.car_side_bg.w),
			.h = (int)((float)ctx->gfx.car_side_bg.h),
		};

		SDL_RenderFillRect(ctx->renderer, &r);

		float scale_lock = 3.f;
		int pos_x = r.x + r.w / 2 -
			    (int)((float)ctx->gfx.gui_lock.w * scale_lock) / 2;
		int pos_y = r.y + r.h / 2 -
			    (int)((float)ctx->gfx.gui_lock.h * scale_lock) / 2;

		texture_render(ctx,
			       &ctx->gfx.gui_lock,
			       pos_x,
			       pos_y,
			       NULL,
			       0.f,
			       scale_lock,
			       0,
			       NULL);
	}

	return 0;
}


int display_menu_track_bordered_pict(struct game_context *ctx,
				     enum track_selection track,
				     int centered)
{
	int bwidth = 5;
	int offset = centered ? 50 : 80;

	float scale_track = (float)ctx->display.screen_width / 3.0f /
			    (float)ctx->gfx.track_thumbnail[track].w;

	int track_x = ctx->display.screen_width * offset / 100 -
		      (int)((float)ctx->gfx.track_thumbnail[track].w *
			    scale_track / 2.f);

	int track_y = ctx->display.screen_height / 2 -
		      (int)((float)ctx->gfx.track_thumbnail[track].h *
			    scale_track / 2.f);

	texture_render(ctx,
		       &ctx->gfx.track_thumbnail[track],
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
		track_x + (int)((float)ctx->gfx.track_thumbnail[track].w *
				scale_track),
		track_y,
		track_x,
		track_y + (int)((float)ctx->gfx.track_thumbnail[track].h *
				scale_track),
		track_x + (int)((float)ctx->gfx.track_thumbnail[track].w *
				scale_track),
		track_y,
		bwidth,
		0,
		0,
		0);


	if (!(1 << ctx->track.track_selected & ctx->save.tracks_available) &&
	    ctx->status_cur == GAME_STATE_MENU_SELECT_TRACK) {

		SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 150);
		/*SDL_BlendMode blendMode;
		SDL_GetRenderDrawBlendMode(ctx->renderer, &blendMode);
		SDL_Log("blendMode = %d\n", blendMode);*/
		SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);
		SDL_Rect r = {
			.x = track_x,
			.y = track_y,
			.w = (int)((float)ctx->gfx
					   .track_thumbnail
						   [ctx->track.track_selected]
					   .w *
				   scale_track),
			.h = (int)((float)ctx->gfx
					   .track_thumbnail
						   [ctx->track.track_selected]
					   .h *
				   scale_track),
		};
		SDL_RenderFillRect(ctx->renderer, &r);

		float scale_lock = 3.f;
		int pos_x = r.x + r.w / 2 -
			    (int)((float)ctx->gfx.gui_lock.w * scale_lock) / 2;
		int pos_y = r.y + r.h / 2 -
			    (int)((float)ctx->gfx.gui_lock.h * scale_lock) / 2;

		texture_render(ctx,
			       &ctx->gfx.gui_lock,
			       pos_x,
			       pos_y,
			       NULL,
			       0.f,
			       scale_lock,
			       0,
			       NULL);
	}


	return 0;
}

int display_menu_track_stats(struct game_context *ctx)
{
	int bwidth = 5;
	int offset = 30;
	struct texture ttext = {.w = 0, .h = 0, .texture = NULL};

	int car_bg_x = ctx->display.screen_width * offset / 100 -
		       (int)((float)ctx->gfx.car_side_bg.w / 2.f);
	int car_bg_y = ctx->display.screen_height / 2 -
		       (int)((float)ctx->gfx.car_side_bg.h / 2.f);

	float scale_car = 1.f;

	SDL_Rect r = {
		.x = car_bg_x,
		.y = car_bg_y,
		.w = (int)((float)ctx->gfx.car_side_bg.w * scale_car),
		.h = (int)((float)ctx->gfx.car_side_bg.h * scale_car),
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);

	SDL_RenderFillRect(ctx->renderer, &r);


	SDL_Color text_color_front_1 = {0x0, 0x0, 0x0};
	int font_size_big = 64;
	int font_size_small = 32;
	TTF_Font *font_big = NULL;
	TTF_Font *font_small = NULL;

	font_big = TTF_OpenFont(SOFACHROME_FONT,
				font_size_big * ctx->display.screen_height /
					SCREEN_HEIGHT_DEFAULT);
	if (!font_big) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}
	font_small = TTF_OpenFont(SOFACHROME_FONT,
				  font_size_small * ctx->display.screen_height /
					  SCREEN_HEIGHT_DEFAULT);
	if (!font_small) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	display_load_render_text(
		ctx,
		font_big,
		&ttext,
		track_desc_tab[ctx->track.track_selected][TRACK_DESC_NAME],
		&text_color_front_1,
		car_bg_x,
		car_bg_y,
		0.f);

	int str_y;

	str_y = car_bg_y + ttext.h * 3 / 2;

	display_load_render_text(ctx,
				 font_small,
				 &ttext,
				 " Lap Length    : ",
				 &text_color_front_1,
				 car_bg_x,
				 str_y,
				 0.f);
	display_load_render_text(
		ctx,
		font_small,
		&ttext,
		track_desc_tab[ctx->track.track_selected][TRACK_DESC_LENGTH],
		&text_color_front_1,
		car_bg_x + ttext.w,
		str_y,
		0.f);


	str_y += ttext.h;
	display_load_render_text(ctx,
				 font_small,
				 &ttext,
				 " Difficulty    : ",
				 &text_color_front_1,
				 car_bg_x,
				 str_y,
				 0.f);
	display_load_render_text(ctx,
				 font_small,
				 &ttext,
				 track_desc_tab[ctx->track.track_selected]
					       [TRACK_DESC_DIFFICULTY],
				 &text_color_front_1,
				 car_bg_x + ttext.w,
				 str_y,
				 0.f);

	str_y += ttext.h;
	display_load_render_text(ctx,
				 font_small,
				 &ttext,
				 " Best Time     : ",
				 &text_color_front_1,
				 car_bg_x,
				 str_y,
				 0.f);

	Uint32 race_time_ms = ctx->save.tracks_time[ctx->track.track_selected];
	char time_str[16];
	Uint32 time_min = race_time_ms / 60000;
	Uint32 time_sec = (race_time_ms - time_min * 60000) / 1000;
	Uint32 time_ms =
		(race_time_ms - time_min * 60000 - time_sec * 1000) / 10;

	sprintf(time_str, "%02d'%02d\"%02d", time_min, time_sec, time_ms);

	display_load_render_text(
		ctx,
		font_small,
		&ttext,
		ctx->save.tracks_time[ctx->track.track_selected] == 0xffffffff
			? DEFAULT_BEST_TIME
			: time_str,
		&text_color_front_1,
		car_bg_x + ttext.w,
		str_y,
		0.f);


	char str_pos[16];
	sprintf(str_pos,
		"%d%s",
		ctx->save.tracks_position[ctx->track.track_selected],
		logic_get_player_place_suffix(
			ctx->save.tracks_position[ctx->track.track_selected]));

	str_y += ttext.h;
	display_load_render_text(ctx,
				 font_small,
				 &ttext,
				 " Best Position : ",
				 &text_color_front_1,
				 car_bg_x,
				 str_y,
				 0.f);
	display_load_render_text(
		ctx,
		font_small,
		&ttext,
		ctx->save.tracks_position[ctx->track.track_selected] == 0xff
			? DEFAULT_BEST_POSITION
			: str_pos,
		&text_color_front_1,
		car_bg_x + ttext.w,
		str_y,
		0.f);

	float scale_trophy = 1.f;
	struct texture *ttrophy;
	switch (ctx->save.tracks_position[ctx->track.track_selected]) {
	case 1:
		ttrophy = &ctx->gfx.gui_trophy_gold;
		break;
	case 2:
		ttrophy = &ctx->gfx.gui_trophy_silver;
		break;
	case 3:
		ttrophy = &ctx->gfx.gui_trophy_bronze;
		break;
	default:
		ttrophy = NULL;
	}

	if (ttrophy) {
		texture_render(ctx,
			       ttrophy,
			       r.x + r.w - ttrophy->w,
			       r.y /*+ r.h - ctx->gfx.gui_trophy_gold.h*/,
			       NULL,
			       0.f,
			       scale_trophy,
			       0,
			       NULL);
	}

	scale_car = 1.f;

	display_screen_rect_border(
		ctx,
		car_bg_x,
		car_bg_y,
		car_bg_x + (int)((float)ctx->gfx.car_side_bg.w * scale_car),
		car_bg_y,
		car_bg_x,
		car_bg_y + (int)((float)ctx->gfx.car_side_bg.h * scale_car),
		car_bg_x + (int)((float)ctx->gfx.car_side_bg.w * scale_car),
		car_bg_y,
		bwidth,
		0,
		0,
		0);


	if (!(1 << ctx->track.track_selected & ctx->save.tracks_available) &&
	    ctx->status_cur == GAME_STATE_MENU_SELECT_TRACK) {

		SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 150);
		SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);
		SDL_Rect r = {
			.x = car_bg_x,
			.y = car_bg_y,
			.w = (int)((float)ctx->gfx.car_side_bg.w * scale_car),
			.h = (int)((float)ctx->gfx.car_side_bg.h * scale_car),
		};
		SDL_RenderFillRect(ctx->renderer, &r);

		float scale_lock = 3.f;
		int pos_x = r.x + r.w / 2 -
			    (int)((float)ctx->gfx.gui_lock.w * scale_lock) / 2;
		int pos_y = r.y + r.h / 2 -
			    (int)((float)ctx->gfx.gui_lock.h * scale_lock) / 2;

		texture_render(ctx,
			       &ctx->gfx.gui_lock,
			       pos_x,
			       pos_y,
			       NULL,
			       0.f,
			       scale_lock,
			       0,
			       NULL);
	}

	TTF_CloseFont(font_big);
	TTF_CloseFont(font_small);

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

	SDL_Rect r = {.x = ctx->display.screen_width * 20 / 100,
		      .y = 0,
		      .w = ctx->display.screen_width * 20 / 100,
		      .h = ctx->display.screen_height};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_car_bordered_pict(ctx, ctx->pcar.car_player_model, 0);
	display_menu_stats_bordered_pict(ctx);

	float scale = 1.f;

	texture_render(ctx,
		       &ctx->gfx.gui_up,
		       ctx->display.screen_width * 30 / 100 -
			       (int)((float)ctx->gfx.gui_up.w / 2.f * scale),
		       ctx->display.screen_height * 15 / 100 -
			       (int)((float)ctx->gfx.gui_up.h / 2.f * scale),
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_down,
		       ctx->display.screen_width * 30 / 100 -
			       (int)((float)ctx->gfx.gui_down.w / 2.f * scale),
		       ctx->display.screen_height * 85 / 100 -
			       (int)((float)ctx->gfx.gui_up.h / 2.f * scale),
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_prev,
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


int display_screen_menu_select_track(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	// animated background
	display_menu_animated_background(ctx);

	SDL_Rect r = {.x = ctx->display.screen_width * 70 / 100,
		      .y = 0,
		      .w = ctx->display.screen_width * 20 / 100,
		      .h = ctx->display.screen_height};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_track_bordered_pict(ctx, ctx->track.track_selected, 0);

	float scale = 1.f;

	texture_render(ctx,
		       &ctx->gfx.gui_up,
		       ctx->display.screen_width * 80 / 100 -
			       (int)((float)ctx->gfx.gui_up.w / 2.f * scale),
		       ctx->display.screen_height * 15 / 100 -
			       (int)((float)ctx->gfx.gui_up.h / 2.f * scale),
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_down,
		       ctx->display.screen_width * 80 / 100 -
			       (int)((float)ctx->gfx.gui_down.w / 2.f * scale),
		       ctx->display.screen_height * 85 / 100 -
			       (int)((float)ctx->gfx.gui_up.h / 2.f * scale),
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_prev,
		       0,
		       0,
		       NULL,
		       0.f,
		       1.f,
		       0,
		       NULL);

	display_menu_track_stats(ctx);

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
		.y = ctx->display.screen_height / 2 -
		     ctx->display.screen_height * 10 / 100,
		.w = ctx->display.screen_width,
		.h = ctx->display.screen_height * 20 / 100,
	};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	display_menu_car_bordered_pict(ctx, ctx->pcar.car_player_model, 0);

	display_menu_track_bordered_pict(ctx, ctx->track.track_selected, 0);

	texture_render(
		ctx, &ctx->gfx.gui_settings, 0, 0, NULL, 0.f, 1.f, 0, NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_credit,
		       (ctx->display.screen_width - ctx->gfx.gui_credit.w) / 2,
		       0,
		       NULL,
		       0.f,
		       1.f,
		       0,
		       NULL);

	texture_render(ctx,
		       &ctx->gfx.gui_exit,
		       ctx->display.screen_width - ctx->gfx.gui_exit.w,
		       0,
		       NULL,
		       0.f,
		       1.f,
		       0,
		       NULL);

	float scale_play = 1.f;

	texture_render(ctx,
		       &ctx->gfx.gui_play,
		       ctx->display.screen_width / 2 -
			       (int)((float)ctx->gfx.gui_play.w / 2.f *
				     scale_play), /* 1/2 * 1.5f*/
		       ctx->display.screen_height * 80 / 100,
		       NULL,
		       0.f,
		       scale_play,
		       0,
		       NULL);

	SDL_RenderPresent(ctx->renderer);

	return ret;
}

int display_screen_menu_option(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	// animated background
	display_menu_animated_background(ctx);

	SDL_Rect r = {.x = ctx->display.screen_width * 40 / 100,
		      .y = 0,
		      .w = ctx->display.screen_width * 20 / 100,
		      .h = ctx->display.screen_height};

	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(ctx->renderer, &r);

	float scale = 1.f;

	////////////////////////////////////////////////////////////
	// music volume

	int pos_x = ctx->display.screen_width * 50 / 100 -
		    (int)((float)ctx->gfx.gui_case.w / 2.f * scale);
	int pos_y = ctx->display.screen_height * 20 / 100 -
		    (int)((float)ctx->gfx.gui_case.h / 2.f * scale);

	texture_render(ctx,
		       &ctx->gfx.gui_case,
		       pos_x,
		       pos_y,
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	SDL_Color text_color_front_1 = {0x0, 0x0, 0x0};
	SDL_Color text_color_shadow = {0xFF, 0xFF, 0xFF};
	int font_size = 64;
	TTF_Font *finish_font = NULL;

	finish_font = TTF_OpenFont(SOFACHROME_FONT,
				   font_size * ctx->display.screen_height /
					   SCREEN_HEIGHT_DEFAULT);
	if (!finish_font) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	display_load_render_text_with_shade(ctx,
					    finish_font,
					    &ctx->gfx.font_race_anim,
					    ":",
					    &text_color_front_1,
					    &text_color_shadow,
					    ctx->display.screen_width,
					    ctx->display.screen_height,
					    4,
					    200,
					    0.f);

	int char_w = ctx->gfx.font_race_anim.w;

	int txt_x_left = pos_x + ctx->gfx.gui_case.w / 2;
	int txt_x = txt_x_left - char_w * (int)strlen("Music:") / 2;

	display_load_render_text_with_shade(ctx,
					    finish_font,
					    &ctx->gfx.font_race_anim,
					    "Music:",
					    &text_color_front_1,
					    &text_color_shadow,
					    txt_x,
					    pos_y * 110 / 100,
					    4,
					    200,
					    0.f);

	txt_x = txt_x_left - char_w *
				     (int)strlen(sound_volume2string(
					     ctx->sound.volume_music)) /
				     2;

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		sound_volume2string(ctx->sound.volume_music),
		&text_color_front_1,
		&text_color_shadow,
		txt_x,
		pos_y * 200 / 100,
		4,
		200,
		0.f);

	////////////////////////////////////////////////////////////
	// SFX volume

	pos_y = ctx->display.screen_height * 50 / 100 -
		(int)((float)ctx->gfx.gui_case.h / 2.f * scale);

	texture_render(ctx,
		       &ctx->gfx.gui_case,
		       pos_x,
		       pos_y,
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	txt_x = txt_x_left - char_w * (int)strlen("SFX:") / 2;

	display_load_render_text_with_shade(ctx,
					    finish_font,
					    &ctx->gfx.font_race_anim,
					    "SFX:",
					    &text_color_front_1,
					    &text_color_shadow,
					    txt_x,
					    pos_y * 102 / 100,
					    4,
					    200,
					    0.f);

	txt_x = txt_x_left - char_w *
				     (int)strlen(sound_volume2string(
					     ctx->sound.volume_sfx)) /
				     2;

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		sound_volume2string(ctx->sound.volume_sfx),
		&text_color_front_1,
		&text_color_shadow,
		txt_x,
		pos_y * 125 / 100,
		4,
		200,
		0.f);

	////////////////////////////////////////////////////////////
	// reset progression

	pos_y = ctx->display.screen_height * 80 / 100 -
		(int)((float)ctx->gfx.gui_case.h / 2.f * scale);

	texture_render(ctx,
		       &ctx->gfx.gui_case,
		       pos_x,
		       pos_y,
		       NULL,
		       0.f,
		       scale,
		       0,
		       NULL);

	txt_x = txt_x_left - char_w * (int)strlen("Delete") / 2;

	display_load_render_text_with_shade(ctx,
					    finish_font,
					    &ctx->gfx.font_race_anim,
					    "Delete",
					    &text_color_front_1,
					    &text_color_shadow,
					    txt_x,
					    pos_y * 102 / 100,
					    4,
					    200,
					    0.f);

	txt_x = txt_x_left - char_w * (int)strlen("Save") / 2;

	display_load_render_text_with_shade(ctx,
					    finish_font,
					    &ctx->gfx.font_race_anim,
					    "Save",
					    &text_color_front_1,
					    &text_color_shadow,
					    txt_x,
					    pos_y * 114 / 100,
					    4,
					    200,
					    0.f);

	texture_render(ctx,
		       &ctx->gfx.gui_prev,
		       0,
		       0,
		       NULL,
		       0.f,
		       1.f,
		       0,
		       NULL);

	SDL_RenderPresent(ctx->renderer);
	TTF_CloseFont(finish_font);

	return ret;
}

int display_screen_menu_credit(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 220, 220, 0, 0xFF);
	SDL_RenderClear(ctx->renderer);

	// animated background
	display_menu_animated_background(ctx);

	SDL_Color text_color_front_1 = {0x0, 0x0, 0x0};
	int font_size_big = 64;
	int font_size_medium = 48;
	int font_size_small = 32;
	TTF_Font *font_big = NULL;
	TTF_Font *font_medium = NULL;
	TTF_Font *font_small = NULL;

	font_big = TTF_OpenFont(SOFACHROME_FONT,
				font_size_big * ctx->display.screen_height /
					SCREEN_HEIGHT_DEFAULT);
	if (!font_big) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}
	font_medium =
		TTF_OpenFont(SOFACHROME_FONT,
			     font_size_medium * ctx->display.screen_height /
				     SCREEN_HEIGHT_DEFAULT);
	if (!font_medium) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}
	font_small = TTF_OpenFont(SOFACHROME_FONT,
				  font_size_small * ctx->display.screen_height /
					  SCREEN_HEIGHT_DEFAULT);
	if (!font_small) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	display_load_render_text(ctx,
				 font_big,
				 &ctx->gfx.font_race_anim,
				 "Credits",
				 &text_color_front_1,
				 ctx->display.screen_width * 40 / 100,
				 ctx->display.screen_height * 2 / 100,
				 0.f);
	display_load_render_text(ctx,
				 font_medium,
				 &ctx->gfx.font_race_anim,
				 "Music:",
				 &text_color_front_1,
				 ctx->display.screen_width * 2 / 100,
				 ctx->display.screen_height * 20 / 100,
				 0.f);

	int offset_num = 28;
	int step = 5;
	SDL_Rect r = {.x = 0,
		      .y = ctx->display.screen_height * offset_num / 100,
		      .w = ctx->display.screen_width,
		      .h = ctx->display.screen_height *
			   (step * CREDIT_MUSIC_NB + 1) / 100};
	SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(ctx->renderer, &r);

	for (int i = 0; i < CREDIT_MUSIC_NB; i++) {
		display_load_render_text(ctx,
					 font_small,
					 &ctx->gfx.font_race_anim,
					 CREDIT_MUSIC_TAB[i],
					 &text_color_front_1,
					 ctx->display.screen_width * 2 / 100,
					 ctx->display.screen_height *
						 (offset_num + step * i) / 100,
					 0.f);
	}

	// Display SFX list
	display_load_render_text(ctx,
				 font_medium,
				 &ctx->gfx.font_race_anim,
				 "SFX:",
				 &text_color_front_1,
				 ctx->display.screen_width * 2 / 100,
				 ctx->display.screen_height * 70 / 100,
				 0.f);

	offset_num = 78;
	r.y = ctx->display.screen_height * offset_num / 100;
	r.h = ctx->display.screen_height * (step * CREDIT_SFX_NB + 1) / 100;
	SDL_RenderFillRect(ctx->renderer, &r);

	for (int i = 0; i < CREDIT_SFX_NB; i++) {
		display_load_render_text(ctx,
					 font_small,
					 &ctx->gfx.font_race_anim,
					 CREDIT_SFX_TAB[i],
					 &text_color_front_1,
					 ctx->display.screen_width * 2 / 100,
					 ctx->display.screen_height *
						 (offset_num + step * i) / 100,
					 0.f);
	}

	// back button
	texture_render(ctx, &ctx->gfx.gui_prev, 0, 0, NULL, 0.f, 1.f, 0, NULL);

	SDL_RenderPresent(ctx->renderer);
	TTF_CloseFont(font_big);
	TTF_CloseFont(font_medium);
	TTF_CloseFont(font_small);

	return ret;
}

int display_screen_title(struct game_context *ctx)
{
	int ret = 0;
	static int clkcpt = 0;
	static int invcolors = 0;
	int nb_seg = 10 * ctx->display.screen_width / SCREEN_WIDTH_DEFAULT;
	int segw = ctx->display.screen_width / nb_seg;
	SDL_Rect r;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 135, 206, 235, 0xFF); // blue sky
	SDL_RenderClear(ctx->renderer);

	filledCircleRGBA(ctx->renderer,
			 (int16_t)(ctx->display.screen_width * 85 / 100),
			 (int16_t)(ctx->display.screen_height * 15 / 100),
			 (Sint16)(ctx->display.screen_height * 10 / 100),
			 250,
			 253,
			 15,
			 255);


	// draw grass
	r.x = 0;
	r.y = ctx->display.screen_height * 50 / 100;
	r.w = segw;
	r.h = ctx->display.screen_height * 7 / 100;

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
	r.y = ctx->display.screen_height * 57 / 100;
	r.w = segw;
	r.h = ctx->display.screen_height * 4 / 100;
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
	r.y = ctx->display.screen_height * 60 / 100;
	r.w = segw;
	r.h = ctx->display.screen_height * 40 / 100;

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
	int nb_oak = 6;
	int segw_oak =
		(int)((float)ctx->gfx.scene_tree_oak.h * scale_oak) * 3 / 2;

	for (int i = 0; i < nb_oak; i++) {
		r.x = i * segw_oak - clkcpt;
		ret = texture_render(
			ctx,
			&ctx->gfx.scene_tree_oak,
			r.x,
			ctx->display.screen_height * 53 / 100 -
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
	float scale_car = 0.66f;
	static int car_model = -1;
	if (car_model < 0)
		car_model = rand() % CAR_MODEL_LAST;
	static int y_car = 70;
	int x_car =
		-1 * (int)((float)ctx->gfx.cars_side[car_model].w * scale_car);
	x_car += x_car_cpt;

	ret = texture_render(
		ctx,
		&ctx->gfx.cars_side[car_model],
		x_car,
		ctx->display.screen_height * y_car / 100 -
			(int)((float)ctx->gfx.cars_side[car_model].h *
			      scale_car),
		NULL,
		0.f,
		scale_car,
		SDL_FLIP_NONE,
		NULL);


	clkcpt += 20 * ctx->display.screen_height / SCREEN_HEIGHT_DEFAULT;
	if (clkcpt > segw_oak) {
		clkcpt = 0;
		invcolors = invcolors ? 0 : 1;
	}
	if (clkcpt % segw == 0)
		invcolors = invcolors ? 0 : 1;

	x_car_cpt += 80 * ctx->display.screen_height / SCREEN_HEIGHT_DEFAULT;
	if (x_car_cpt >
	    ctx->display.screen_width +
		    (int)((float)ctx->gfx.cars_side[car_model].w * scale_car)) {
		x_car_cpt = 0;
		car_model = rand() % CAR_MODEL_LAST;

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

	angle = (float)ctx->race.nb_frame_anim * 5.f;
	if (angle > 360.f) {
		angle = 0.f;
		if (ctx->race.finish_placed_frame_nb == 0) {
			ctx->race.finish_placed_frame_nb =
				ctx->race.nb_frame_anim;
		}
	}

	finish_font =
		TTF_OpenFont(SOFACHROME_FONT,
			     finish_font_size * ctx->display.screen_height /
				     SCREEN_HEIGHT_DEFAULT);
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
		"Thrill",
		&text_color_front_1,
		&text_color_shadow,
		ctx->display.screen_width * 25 /
			100 /*- ctx->gfx.font_race_anim.w / 2*/,
		ctx->display.screen_height * 30 / 100 -
			ctx->gfx.font_race_anim.h / 2,
		4,
		200,
		angle);

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		"of",
		&text_color_front_1,
		&text_color_shadow,
		ctx->display.screen_width * 42 /
			100 /*- ctx->gfx.font_race_anim.w / 2*/,
		ctx->display.screen_height * 43 /
			100 /*+ ctx->gfx.font_race_anim.h / 2*/,
		4,
		200,
		angle);

	display_load_render_text_with_shade(
		ctx,
		finish_font,
		&ctx->gfx.font_race_anim,
		"Speed",
		&text_color_front_1,
		&text_color_shadow,
		ctx->display.screen_width * 30 /
			100 /*- ctx->gfx.font_race_anim.w / 2*/,
		ctx->display.screen_height * 50 / 100 +
			ctx->gfx.font_race_anim.h / 2,
		10,
		200,
		angle);

	SDL_RenderPresent(ctx->renderer);
	TTF_CloseFont(finish_font);

	return ret;
}
