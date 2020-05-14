#include "main.h"

#define BORDER 0


enum another_bg_type { ANOTHER_BG_NONE, ANOTHER_BG_LEFT, ANOTHER_BG_RIGHT };

/* identifies the different layers. Their value is the coefficient to which
 * they scroll */
enum background_layer {
	BG_LAYER_SKY_FAR = 2,
	BG_LAYER_LANDSCAPE_FAR = 4,
	BG_LAYER_LANDSCAPE_NEAR = 5,
	BG_LAYER_SKY_NEAR = 6
};

struct color_desc color_road_yellow = {
	.r = 255,
	.g = 234,
	.b = 0,
	.a = 255,
};

/*struct color_desc color_bright_road_asphalt = {
	.r = 169,
	.g = 169,
	.b = 169,
	.a = 255,
};*/

struct color_desc color_bright_road_asphalt = {
	.r = 140,
	.g = 140,
	.b = 140,
	.a = 255,
};

struct color_desc color_dark_road_asphalt = {
	.r = 128,
	.g = 128,
	.b = 128,
	.a = 255,
};

struct color_desc color_bright_grass = {
	.r = 0,
	.g = 169,
	.b = 0,
	.a = 255,
};

struct color_desc color_dark_grass = {
	.r = 0,
	.g = 160,
	.b = 0,
	.a = 255,
};

/*struct color_desc color_bright_rumble = {
	.r = 85,
	.g = 85,
	.b = 85,
	.a = 255,
};

struct color_desc color_dark_rumble = {
	.r = 187,
	.g = 187,
	.b = 187,
	.a = 255,
};*/

struct color_desc color_bright_rumble = {
	.r = 255,
	.g = 255,
	.b = 255,
	.a = 255,
};

struct color_desc color_dark_rumble = {
	.r = 255,
	.g = 0,
	.b = 0,
	.a = 255,
};

struct color_desc color_white = {
	.r = 255,
	.g = 255,
	.b = 255,
	.a = 255,
};


/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

static int display_render_quad(struct game_context *ctx,
			       int x1,
			       int y1,
			       int x2,
			       int y2,
			       int x3,
			       int y3,
			       int x4,
			       int y4,
			       struct color_desc *color)
{
	Sint16 x[4] = {(Sint16)x1, (Sint16)x2, (Sint16)x3, (Sint16)x4};
	Sint16 y[4] = {(Sint16)y1, (Sint16)y2, (Sint16)y3, (Sint16)y4};

	filledPolygonRGBA(
		ctx->renderer, x, y, 4, color->r, color->g, color->b, 255);

	return 0;
}

static int display_render_segment(struct game_context *ctx,
				  int seg_idx,
				  int width,
				  int lanes,
				  int x1,
				  int y1,
				  int w1,
				  int x2,
				  int y2,
				  int w2,
				  int fog,
				  int color)
{
	int grid_per_lane = 4;
	int lane_separator;
	int r1 = inline_rumble_width(w1, lanes);
	int r2 = inline_rumble_width(w2, lanes);
	int l1 = inline_lane_marker_width(w1, lanes);
	int l2 = inline_lane_marker_width(w2, lanes);

	// render grass
	SDL_Rect r = {
		.w = width,
		.h = y1 - y2,
		.x = 0,
		.y = y2,
	};
	if (color == COLOR_DARK)
		SDL_SetRenderDrawColor(ctx->renderer,
				       color_dark_grass.r,
				       color_dark_grass.g,
				       color_dark_grass.b,
				       255);
	else if (color == COLOR_BRIGHT)
		SDL_SetRenderDrawColor(ctx->renderer,
				       color_bright_grass.r,
				       color_bright_grass.g,
				       color_bright_grass.b,
				       255);
	else if (color == COLOR_START)
		SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 0, 255);

	// SDL_SetRenderDrawColor(ctx->renderer, 50, 205, 50,
	// 255);

	SDL_RenderFillRect(ctx->renderer, &r);


	// render rumbles
	display_render_quad(ctx,
			    x1 - w1 - r1,
			    y1,
			    x1 - w1,
			    y1,
			    x2 - w2,
			    y2,
			    x2 - w2 - r2,
			    y2,
			    color == COLOR_DARK ? &color_dark_rumble
						: &color_bright_rumble);
	display_render_quad(ctx,
			    x1 + w1 + r1,
			    y1,
			    x1 + w1,
			    y1,
			    x2 + w2,
			    y2,
			    x2 + w2 + r2,
			    y2,
			    color == COLOR_DARK ? &color_dark_rumble
						: &color_bright_rumble);

	// render road
	struct color_desc *road_color;
	if (color == COLOR_DARK)
		road_color = &color_dark_road_asphalt;
	else
		road_color = &color_bright_road_asphalt;


	display_render_quad(ctx,
			    x1 - w1,
			    y1,
			    x1 + w1,
			    y1,
			    x2 + w2,
			    y2,
			    x2 - w2,
			    y2,
			    road_color);

	switch (ctx->track.lane_type) {
	case LANE_TYPE_NONE:
		lane_separator = 0;
		break;
	case LANE_TYPE_HALF:
		if (color == COLOR_DARK)
			lane_separator = 1;
		else
			lane_separator = 0;
		break;
	case LANE_TYPE_FULL:
		lane_separator = 1;
		break;
	default:
		lane_separator = 0;
	}

	// road_color = &color_lane;

	if (seg_idx < 7) {
		int j_offset = (seg_idx) % 2;
		lane_separator = 0;

		for (int j = 0 + j_offset; j < ctx->track.lanes * grid_per_lane;
		     j += 2) {
			int square_x1 = x1 - w1;
			int square_x2 = x2 - w2;
			int square_w1 =
				2 * w1 / (grid_per_lane * ctx->track.lanes);
			int square_w2 =
				2 * w2 / (grid_per_lane * ctx->track.lanes);
			display_render_quad(ctx,
					    square_x1 + square_w1 * j,
					    y1,
					    square_x1 + square_w1 * (j + 1),
					    y1,
					    square_x2 + square_w2 * (j + 1),
					    y2,
					    square_x2 + square_w2 * j,
					    y2,
					    &color_white);
		}
	}

	// render lanes
	if (lanes > 0 && lane_separator) {
		int lane_w1 = (w1 * 2) / lanes;
		int lane_w2 = (w2 * 2) / lanes;
		int lane_x1 = x1 - w1 + lane_w1;
		int lane_x2 = x2 - w2 + lane_w2;

		for (int lane = 1; lane < lanes;
		     lane_x1 += lane_w1, lane_x2 += lane_w2, lane++) {

			if (l1 <= 1) {
				// far away lanes are simplified into rect
				r.x = lane_x2 - l2 / 2;
				r.y = y2;
				r.h = 2;
				r.w = 2;

				SDL_SetRenderDrawColor(ctx->renderer,
						       ctx->track.lane_color.r,
						       ctx->track.lane_color.g,
						       ctx->track.lane_color.b,
						       255);
				SDL_RenderFillRect(ctx->renderer, &r);
			} else {
				// render lanes with a drawable polygon
				display_render_quad(ctx,
						    lane_x1 - l1 / 2,
						    y1,
						    lane_x1 + l1 / 2,
						    y1,
						    lane_x2 + l2 / 2,
						    y2,
						    lane_x2 - l2 / 2,
						    y2,
						    &ctx->track.lane_color);
			}
		}
	}

	// TODO: draw fog
	// Render.fog(ctx, 0, y1, width, y2-y1, fog);

	return 0;
}


static int display_render_bgm_name(struct game_context *ctx)
{
	if (ctx->race.bgm_name_dislayed)
		return 0;

	// SDL_Color text_color_front_2 = {0, 0, 0};
	SDL_Color text_color_front_2 = {16, 52, 166};
	SDL_Color text_color_shadow = {0xFF, 0xFF, 0xFF};
	// SDL_Color text_color_shadow = {0xFF, 0xFF, 0x0};

	/*SDL_Color text_color_front_2 = {0xFF, 0xFF, 0x0};
	SDL_Color text_color_shadow = {0, 0, 0};*/
	int font_size_2 = 40;
	TTF_Font *bgm_font = NULL;

	ctx->race.nb_frame_anim++;

	bgm_font = TTF_OpenFont(SOFACHROME_FONT, font_size_2);
	if (!bgm_font) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	int bgm_pos_x = SCREEN_WIDTH - ctx->race.nb_frame_anim * 7;
	if (bgm_pos_x < -ctx->gfx.font_race_anim_3.w) {
		bgm_pos_x = -ctx->gfx.font_race_anim_3.w;
		ctx->race.bgm_name_dislayed = 1;
	}

	// glitch fix
	/*if (ctx->race.finish_placed_frame_nb == ctx->race.nb_frame_anim)
		bgm_pos_x = SCREEN_WIDTH;*/

	display_load_render_text_with_shade(
		ctx,
		bgm_font,
		&ctx->gfx.font_race_anim_3,
		ctx->sound.music.bgm_name[ctx->sound.bgm_idx],
		&text_color_front_2,
		&text_color_shadow,
		bgm_pos_x,
		SCREEN_HEIGHT * 20 / 100 - ctx->gfx.font_race_anim_3.h / 2,
		1,
		200,
		0.f);

	TTF_CloseFont(bgm_font);

	ctx->race.nb_frame_anim++;

	return 0;
}


static int display_render_anim_race_end(struct game_context *ctx)
{
	int alpha = ctx->race.nb_frame_anim / 2;
	if (alpha > 200)
		alpha = 200;

	// bright the screen progressively
	boxRGBA(ctx->renderer,
		0,
		0,
		SCREEN_WIDTH - 1,
		SCREEN_HEIGHT - 1,
		200,
		200,
		200,
		(uint8_t)alpha);

	SDL_Color text_color_front_1 = {0xFF, 0xFF, 0xFF};
	SDL_Color text_color_front_2 = {0xFF, 0xFF, 0x00};
	SDL_Color text_color_shadow = {0, 0, 0};
	int finish_font_size;
	int font_size_2 = 100;
	TTF_Font *finish_font = NULL;
	TTF_Font *nb_font = NULL;
	TTF_Font *place_font = NULL;
	float angle;

	ctx->race.nb_frame_anim++;

	finish_font_size = ctx->race.nb_frame_anim;
	if (finish_font_size > 150)
		finish_font_size = 150;

	angle = (float)ctx->race.nb_frame_anim * 4.f;
	if (angle > 360.f) {
		angle = 0.f;
		if (ctx->race.finish_placed_frame_nb == 0) {
			ctx->race.finish_placed_frame_nb = ctx->race.nb_frame_anim;
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
		"FINISH!",
		//&text_color_shadow,
		&text_color_front_1,
		&text_color_shadow,
		SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim.w / 2,
		SCREEN_HEIGHT * 30 / 100 - ctx->gfx.font_race_anim.h / 2,
		4,
		200,
		angle);


	if (ctx->race.finish_placed_frame_nb) {

		char msg[32];
		sprintf(msg,
			"%d%s",
			ctx->pcar.player_place,
			logic_get_player_place_suffix(ctx->pcar.player_place));

		nb_font = TTF_OpenFont(SOFACHROME_FONT, font_size_2);
		if (!nb_font) {
			SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
				__func__,
				TTF_GetError());
			return -EINVAL;
		}

		int nb_pos_x =
			-ctx->gfx.font_race_anim_2.w +
			(ctx->race.nb_frame_anim - ctx->race.finish_placed_frame_nb) * 15;
		/*if (nb_pos_x >
		    SCREEN_WIDTH * 45 / 100 - ctx->gfx.font_race_anim_2.w)
			nb_pos_x = SCREEN_WIDTH * 45 / 100 -
				   ctx->gfx.font_race_anim_2.w;*/
		if (nb_pos_x >
		    SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim_2.w / 2)
			nb_pos_x = SCREEN_WIDTH / 2 -
				   ctx->gfx.font_race_anim_2.w / 2;

		// glitch fix
		if (ctx->race.finish_placed_frame_nb == ctx->race.nb_frame_anim)
			nb_pos_x = -SCREEN_WIDTH;

		display_load_render_text_with_shade(
			ctx,
			nb_font,
			&ctx->gfx.font_race_anim_2,
			msg,
			&text_color_front_2,
			&text_color_shadow,
			nb_pos_x,
			SCREEN_HEIGHT * 55 / 100 -
				ctx->gfx.font_race_anim_2.h / 2,
			5,
			200,
			angle);


		place_font = TTF_OpenFont(SOFACHROME_FONT, font_size_2);
		if (!place_font) {
			SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
				__func__,
				TTF_GetError());
			return -EINVAL;
		}

		int place_pos_x =
			SCREEN_WIDTH -
			(ctx->race.nb_frame_anim - ctx->race.finish_placed_frame_nb) * 15;
		/*if (place_pos_x < SCREEN_WIDTH * 45 / 100)
			place_pos_x = SCREEN_WIDTH * 45 / 100;*/
		if (place_pos_x <
		    SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim_3.w / 2)
			place_pos_x = SCREEN_WIDTH / 2 -
				      ctx->gfx.font_race_anim_3.w / 2;

		// glitch fix
		if (ctx->race.finish_placed_frame_nb == ctx->race.nb_frame_anim)
			nb_pos_x = SCREEN_WIDTH;

		display_load_render_text_with_shade(
			ctx,
			place_font,
			&ctx->gfx.font_race_anim_3,
			"place",
			&text_color_front_2,
			&text_color_shadow,
			place_pos_x,
			SCREEN_HEIGHT * 70 / 100 -
				ctx->gfx.font_race_anim_3.h / 2,
			5,
			200,
			angle);
	}

	TTF_CloseFont(finish_font);
	TTF_CloseFont(nb_font);
	TTF_CloseFont(place_font);

	ctx->race.nb_frame_anim++;

	return 0;
}


static int display_render_anim_race_start(struct game_context *ctx)
{
	SDL_Color text_color_front_1 = {0xFF, 0xFF, 0xFF};
	SDL_Color text_color_front_2 = {0xFF, 0xFF, 0x00};
	SDL_Color text_color_shadow = {0, 0, 0};
	char msg[8];
	int cpt = 0;
	int font_size;
	TTF_Font *font;

	ctx->race.nb_frame_anim++;

	cpt = (START_ANIM_DURATION - 1) - ctx->race.nb_frame_anim / FPS;

	if (cpt > 0)
		sprintf(msg, "%d", cpt);
	else
		sprintf(msg, "%s", "GO!");

	font_size = (ctx->race.nb_frame_anim % FPS) * 5;

	font = TTF_OpenFont(SOFACHROME_FONT, font_size);
	if (!font) {
		SDL_Log("[%s] Failed to load font! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	if (cpt != START_ANIM_DURATION - 1)
		display_load_render_text_with_shade(
			ctx,
			font,
			&ctx->gfx.font_race_anim,
			msg,
			cpt ? &text_color_front_1 : &text_color_front_2,
			&text_color_shadow,
			SCREEN_WIDTH / 2 - ctx->gfx.font_race_anim.w / 2,
			SCREEN_HEIGHT / 2 - ctx->gfx.font_race_anim.h / 2,
			15,
			200,
			0.f);

	TTF_CloseFont(font);

	return 0;
}

static int display_render_hud(struct game_context *ctx)
{
	int ret = 0;
	SDL_Color text_color = {0, 0, 0};
	// SDL_Color text_color = {255, 255, 255};
	// SDL_Color text_color = {230, 230, 230};
	// SDL_Color text_color = {255, 255, 0};

	// SDL_Color text_color_shadow = {0, 0, 0};
	// SDL_Color text_color_shadow = {150, 150, 150};
	// SDL_Color text_color_shadow = {200, 200, 200};
	// SDL_Color text_color_shadow = {255, 0, 0};
	SDL_Color text_color_shadow = {255, 255, 255};
	// SDL_Color text_color_shadow = {230, 230, 230};

	int shadow_num = 3;
	int shadow_den = 100;

	char speed[8];
	sprintf(speed,
		"%03d",
		(int)(ctx->pcar.speed * 240.f /
		      ctx->pcar.max_speed)); // TODO: set max_speed in kph per
					     // car

	// Right
	display_load_render_text_with_shade(
		ctx,
		ctx->sc_font_medium,
		&ctx->gfx.font_game_speed_unit,
		"kph",
		&text_color,
		&text_color_shadow,
		SCREEN_WIDTH - ctx->gfx.font_game_speed_unit.w,
		0,
		shadow_num,
		shadow_den,
		0.f);

	display_load_render_text_with_shade(
		ctx,
		ctx->sc_font_big,
		&ctx->gfx.font_game_speed_value,
		speed,
		&text_color,
		&text_color_shadow,
		SCREEN_WIDTH - ctx->gfx.font_game_speed_value.w -
			ctx->gfx.font_game_speed_unit.w,
		0,
		shadow_num,
		shadow_den,
		0.f);

	// Mid
	ctx->pcar.player_place = logic_get_player_place_nb(ctx);
	char place_str[3];
	if (ctx->pcar.player_place < 10)
		snprintf(place_str, 3, " %d", ctx->pcar.player_place);
	else
		snprintf(place_str, 3, "%d", ctx->pcar.player_place);

	display_load_render_text_with_shade(
		ctx,
		ctx->sc_font_big,
		&ctx->gfx.font_game_position_value,
		place_str,
		&text_color,
		&text_color_shadow,
		SCREEN_WIDTH / 2 - ctx->gfx.font_game_position_value.w / 2,
		0,
		shadow_num,
		shadow_den,
		0.f);

	display_load_render_text_with_shade(
		ctx,
		ctx->sc_font_medium,
		&ctx->gfx.font_game_position_unit,
		logic_get_player_place_suffix(ctx->pcar.player_place),
		&text_color,
		&text_color_shadow,
		SCREEN_WIDTH / 2 - ctx->gfx.font_game_position_value.w / 2 +
			ctx->gfx.font_game_position_value.w,
		0,
		shadow_num,
		shadow_den,
		0.f);

	// Left
	char lap_str[8];
	snprintf(lap_str, 8, "%d/%d", ctx->race.player_lap, ctx->race.nb_lap);

	display_load_render_text_with_shade(ctx,
					    ctx->sc_font_big,
					    &ctx->gfx.font_game_lap_value,
					    lap_str,
					    &text_color,
					    &text_color_shadow,
					    0,
					    0,
					    shadow_num,
					    shadow_den,
					    0.f);
	display_load_render_text_with_shade(ctx,
					    ctx->sc_font_medium,
					    &ctx->gfx.font_game_lap_title,
					    "lap",
					    &text_color,
					    &text_color_shadow,
					    ctx->gfx.font_game_lap_value.w,
					    0,
					    shadow_num * 2,
					    shadow_den * 3,
					    0.f);

	// Nitro
	display_load_render_text_with_shade(ctx,
					    ctx->sc_font_medium,
					    &ctx->gfx.font_game_lap_title,
					    "Nitro",
					    &text_color,
					    &text_color_shadow,
					    SCREEN_WIDTH * 64 / 100,
					    0,
					    shadow_num,
					    shadow_den,
					    0.f);

	// display nitro icons
	for (int i = 0; i < ctx->pcar.nb_nitro; i++) {
		filledCircleRGBA(
			ctx->renderer,
			(int16_t)(SCREEN_WIDTH * (662 + i * 30) / 1000),
			(int16_t)(ctx->gfx.font_game_lap_title.h * 135 / 100),
			15,
			0,
			0,
			0,
			255);
		filledCircleRGBA(
			ctx->renderer,
			(int16_t)(SCREEN_WIDTH * (662 + i * 30) / 1000),
			(int16_t)(ctx->gfx.font_game_lap_title.h * 135 / 100),
			11,
			255,
			0,
			0,
			255);
	}

	// blink current nitro
	if (ctx->status_cur == GAME_STATE_RACE_NITRO) {
		if (ctx->pcar.nitro_nb_frame % (FPS / 2) > FPS / 4) {
			filledCircleRGBA(
				ctx->renderer,
				(int16_t)(SCREEN_WIDTH *
					  (662 + ctx->pcar.nb_nitro * 30) /
					  1000),
				(int16_t)(ctx->gfx.font_game_lap_title.h * 135 /
					  100),
				15,
				0,
				0,
				0,
				255);

			filledCircleRGBA(
				ctx->renderer,
				(int16_t)(SCREEN_WIDTH *
					  (662 + ctx->pcar.nb_nitro * 30) /
					  1000),
				(int16_t)(ctx->gfx.font_game_lap_title.h * 135 /
					  100),
				11,
				255,
				0,
				0,
				255);
		}
	}

	// Clock
	display_load_render_text_with_shade(ctx,
					    ctx->sc_font_medium,
					    &ctx->gfx.font_game_lap_title,
					    "Time",
					    &text_color,
					    &text_color_shadow,
					    SCREEN_WIDTH * 28 / 100,
					    0,
					    shadow_num,
					    shadow_den,
					    0.f);

	char time_str[16];
	int time_min = ctx->race.race_time_ms / 60000;
	int time_sec = (ctx->race.race_time_ms - time_min * 60000) / 1000;
	int time_ms =
		(ctx->race.race_time_ms - time_min * 60000 - time_sec * 1000) / 10;

	sprintf(time_str, "%02d:%02d.%02d", time_min, time_sec, time_ms);

	display_load_render_text_with_shade(ctx,
					    ctx->sc_font_medium,
					    &ctx->gfx.font_game_lap_title,
					    time_str,
					    &text_color,
					    &text_color_shadow,
					    SCREEN_WIDTH * 24 / 100,
					    SCREEN_HEIGHT * 11 / 200,
					    shadow_num,
					    shadow_den,
					    0.f);

	return ret;
}


static int display_render_ai_cars_sprites(struct game_context *ctx,
					  struct road_segment *seg,
					  float screen_scale,
					  float x_scale,
					  int idx,
					  int tmp_idx,
					  int tmp_max_y_idx,
					  int tmp_max_y_bis_idx)
{
	int ret = 0;

	for (int i = 0; i < NB_AI_CARS; i++) {

		if (idx == ctx->ai_cars[i].segment) {

			memset(&ctx->ai_cars[i].hitbox, 0, sizeof(SDL_Rect));

			struct road_segment *seg = &ctx->track.segments[idx];
			int sprite_x, sprite_y;

			float car_screen_scale =
				seg->p1.screen.scale -
				(seg->p1.screen.scale - seg->p2.screen.scale) *
					ctx->ai_cars[i].pos_z_rest_percent;

			float car_x_scale = car_screen_scale *
					    ctx->ai_cars[i].car_x_scale_coef;

			// select sprite to simulate a steering in curves
			if (seg->curve > 2.f) {
				ctx->ai_cars[i].sprite_idx = CAR_SPRITE_RIGHT2;
				ctx->ai_cars[i].car_flip = SDL_FLIP_NONE;
			} else if (seg->curve > 0.5f) {
				ctx->ai_cars[i].sprite_idx = CAR_SPRITE_RIGHT1;
				ctx->ai_cars[i].car_flip = SDL_FLIP_NONE;
			} else if (seg->curve < -2.f) {
				ctx->ai_cars[i].sprite_idx = CAR_SPRITE_RIGHT2;
				ctx->ai_cars[i].car_flip = SDL_FLIP_HORIZONTAL;
			} else if (seg->curve < -0.5f) {
				ctx->ai_cars[i].sprite_idx = CAR_SPRITE_RIGHT1;
				ctx->ai_cars[i].car_flip = SDL_FLIP_HORIZONTAL;
			} else {
				ctx->ai_cars[i].sprite_idx = CAR_SPRITE_REAR;
				ctx->ai_cars[i].car_flip = SDL_FLIP_NONE;
			}

			sprite_x =
				seg->p1.screen.x +
				(int)(car_screen_scale * ctx->ai_cars[i].pos_x *
				      (float)seg->width * (float)SCREEN_WIDTH /
				      2.f) -
				(int)((float)ctx->gfx
					      .cars[ctx->ai_cars[i].car_model]
						   [ctx->ai_cars[i].sprite_idx]
					      .w *
				      car_x_scale / 2.f);

			// Avoid AI cars X jump by smoothering sprite_x
			sprite_x += (int)((float)(seg->p2.screen.x -
						  seg->p1.screen.x) *
					  ctx->ai_cars[i].pos_z_rest_percent);

			// Skip AI cars outside screen (right side)
			if (sprite_x > SCREEN_WIDTH)
				continue;

			sprite_y =
				(int)(seg->p1.screen.y -
				      (seg->p1.screen.y - seg->p2.screen.y) *
					      ctx->ai_cars[i]
						      .pos_z_rest_percent -
				      (float)ctx->gfx.cars[ctx->ai_cars[i]
								   .car_model]
							  [ctx->ai_cars[i]
								   .sprite_idx]
								  .h *
					      car_x_scale);

			SDL_Rect *r = NULL;

			// if sprite is behind a hill, set a clip to
			// crop its lower part
			if (tmp_idx > tmp_max_y_idx) {
				if (sprite_y >= ctx->race.max_y) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->w = ctx->gfx.cars[ctx->ai_cars[i].car_model]
						    [ctx->ai_cars[i].sprite_idx]
							    .w;
				int clip_h = ctx->race.max_y - sprite_y;
				int clip_h_inv_scale =
					(int)((float)(ctx->race.max_y - sprite_y) /
					      car_x_scale);
				if (clip_h <
					    (int)((float)ctx->gfx
							  .cars[ctx->ai_cars[i]
									.car_model]
							       [ctx->ai_cars[i]
									.sprite_idx]
							  .h *
						  car_x_scale) &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = ctx->gfx.cars
						       [ctx->ai_cars[i]
								.car_model]
						       [ctx->ai_cars[i]
								.sprite_idx]
							       .h;
				}
				// sprite is behind a hill, crop it
				// accodingly
			} else if (tmp_idx > tmp_max_y_bis_idx) {
				if (sprite_y >= ctx->race.max_y_bis) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->w = ctx->gfx.cars[ctx->ai_cars[i].car_model]
						    [ctx->ai_cars[i].sprite_idx]
							    .w;
				int clip_h = ctx->race.max_y_bis - sprite_y;
				int clip_h_inv_scale =
					(int)((float)(ctx->race.max_y_bis -
						      sprite_y) /
					      car_x_scale);
				if (clip_h <
					    (int)((float)ctx->gfx
							  .cars[ctx->ai_cars[i]
									.car_model]
							       [ctx->ai_cars[i]
									.sprite_idx]
							  .h *
						  car_x_scale) &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = ctx->gfx.cars
						       [ctx->ai_cars[i]
								.car_model]
						       [ctx->ai_cars[i]
								.sprite_idx]
							       .h;
				}
			}

			ret = texture_render(
				ctx,
				&ctx->gfx.cars[ctx->ai_cars[i].car_model]
					      [ctx->ai_cars[i].sprite_idx],
				sprite_x,
				sprite_y,
				r,
				0.f,
				car_screen_scale *
					ctx->ai_cars[i].ai_car_scale_coef,
				ctx->ai_cars[i].car_flip,
				&ctx->ai_cars[i].hitbox);

			if (r)
				free(r);
		}
	}

	return ret;
}

static int display_render_scene_sprites(struct game_context *ctx,
					struct road_segment *seg,
					float screen_scale,
					float x_scale,
					int tmp_idx,
					int tmp_max_y_idx,
					int tmp_max_y_bis_idx)
{
	int ret = 0;

	for (int j = 0; j < seg->scene->nb_sprites; j++) {

		// ignore segments without sprite
		if (!seg->scene->sprite[j].t)
			continue;

		seg->scene->sprite[j].scale = x_scale;

		seg->scene->sprite[j].scaled_x =
			seg->p1.screen.x +
			(int)(screen_scale * seg->scene->sprite[j].position *
			      ctx->scene_sprite_coef * (float)seg->width);
		if (seg->scene->sprite[j].position < 0)
			seg->scene->sprite[j].scaled_x -=
				(int)((float)seg->scene->sprite[j].t->w *
				      seg->scene->sprite[j].scale);

		if (seg->scene->sprite[j].scaled_x > SCREEN_WIDTH)
			continue;

		int sprite_y = (int)((float)seg->p1.screen.y -
				     (float)seg->scene->sprite[j].t->h *
					     seg->scene->sprite[j].scale);

		SDL_Rect *r = NULL;

		// if sprite is behind a hill, set a clip to crop its
		// lower part
		if (tmp_idx > tmp_max_y_idx) {

			if (sprite_y >= ctx->race.max_y) {
				continue;
			}

			r = calloc(1, sizeof(SDL_Rect));
			r->w = seg->scene->sprite[j].t->w;
			int clip_h = ctx->race.max_y - sprite_y;
			int clip_h_inv_scale =
				(int)((float)(ctx->race.max_y - sprite_y) /
				      seg->scene->sprite[j].scale);
			if (clip_h < (int)((float)seg->scene->sprite[j].t->h *
					   seg->scene->sprite[j].scale) &&
			    clip_h > 0) {
				r->h = clip_h_inv_scale;
			} else {
				r->h = seg->scene->sprite[j].t->h;
			}
			// sprite is behind a hill, crop it accodingly
		} else if (tmp_idx > tmp_max_y_bis_idx) {
			if (sprite_y >= ctx->race.max_y_bis) {
				continue;
			}

			r = calloc(1, sizeof(SDL_Rect));
			r->w = seg->scene->sprite[j].t->w;
			int clip_h = ctx->race.max_y_bis - sprite_y;
			int clip_h_inv_scale =
				(int)((float)(ctx->race.max_y_bis - sprite_y) /
				      seg->scene->sprite[j].scale);
			if (clip_h < (int)((float)seg->scene->sprite[j].t->h *
					   seg->scene->sprite[j].scale) &&
			    clip_h > 0) {
				r->h = clip_h_inv_scale;
			} else {
				r->h = seg->scene->sprite[j].t->h;
			}
		}

		ret = texture_render(ctx,
				     seg->scene->sprite[j].t,
				     seg->scene->sprite[j].scaled_x,
				     sprite_y,
				     r,
				     0.f,
				     seg->scene->sprite[j].scale,
				     seg->scene->sprite[j].flip,
				     NULL);

		if (r)
			free(r);
	}

	return ret;
}


static int display_render_start_line_sprite(struct game_context *ctx,
					    struct road_segment *seg,
					    float screen_scale,
					    float x_scale,
					    int tmp_idx,
					    int tmp_max_y_idx,
					    int tmp_max_y_bis_idx)
{
	int ret = 0;
	SDL_Rect *r = NULL;

	int scaled_x = seg->p1.screen.x -
		       (int)((float)ctx->gfx.scene_start_lane.w * x_scale / 2);

	if (scaled_x > SCREEN_WIDTH)
		return 0;

	int sprite_y = (int)((float)seg->p1.screen.y -
			     (float)ctx->gfx.scene_start_lane.h * x_scale);

	// if sprite is behind a hill, set a clip to crop its
	// lower part
	if (tmp_idx > tmp_max_y_idx) {

		if (sprite_y >= ctx->race.max_y) {
			return 0;
		}

		r = calloc(1, sizeof(SDL_Rect));
		r->w = ctx->gfx.scene_start_lane.w;
		int clip_h = ctx->race.max_y - sprite_y;
		int clip_h_inv_scale =
			(int)((float)(ctx->race.max_y - sprite_y) / x_scale);
		if (clip_h < (int)((float)ctx->gfx.scene_start_lane.h *
				   x_scale) &&
		    clip_h > 0) {
			r->h = clip_h_inv_scale;
		} else {
			r->h = ctx->gfx.scene_start_lane.h;
		}
		// sprite is behind a hill, crop it accodingly
	} else if (tmp_idx > tmp_max_y_bis_idx) {
		if (sprite_y >= ctx->race.max_y_bis) {
			return 0;
		}

		r = calloc(1, sizeof(SDL_Rect));
		r->w = ctx->gfx.scene_start_lane.w;
		int clip_h = ctx->race.max_y_bis - sprite_y;
		int clip_h_inv_scale =
			(int)((float)(ctx->race.max_y_bis - sprite_y) / x_scale);
		if (clip_h < (int)((float)ctx->gfx.scene_start_lane.h *
				   x_scale) &&
		    clip_h > 0) {
			r->h = clip_h_inv_scale;
		} else {
			r->h = ctx->gfx.scene_start_lane.h;
		}
	}

	ret = texture_render(ctx,
			     &ctx->gfx.scene_start_lane,
			     scaled_x,
			     sprite_y,
			     r,
			     0.f,
			     x_scale,
			     SDL_FLIP_NONE,
			     NULL);

	if (r)
		free(r);

	return ret;
}


static int display_render_scaled_sprites(struct game_context *ctx)
{
	int ret;
	int base_segment_idx = inline_get_segment_idx(ctx, ctx->pcar.position);

	for (int i = ctx->race.draw_distance; i >= 0; i--) {

		int idx = (base_segment_idx + i) % ctx->track.nb_segments;
		struct road_segment *seg = &ctx->track.segments[idx];

		/* All this tmp_idx stuff is to detemine the index value of the
		 * 2 highest segments dsiplayes on screen */
		int tmp_idx, tmp_max_y_idx, tmp_max_y_bis_idx;
		if (ctx->race.max_y_idx > base_segment_idx)
			tmp_max_y_idx = ctx->race.max_y_idx;
		else
			tmp_max_y_idx =
				(ctx->race.max_y_idx + ctx->track.nb_segments);
		if (ctx->race.max_y_bis_idx > base_segment_idx)
			tmp_max_y_bis_idx = ctx->race.max_y_bis_idx;
		else
			tmp_max_y_bis_idx =
				(ctx->race.max_y_bis_idx + ctx->track.nb_segments);
		if (idx > base_segment_idx)
			tmp_idx = idx;
		else
			tmp_idx = idx + ctx->track.nb_segments;

		float screen_scale = seg->p1.screen.scale;
		float x_scale = screen_scale * SCREEN_WIDTH * 2;

		if (seg->scene)
			ret = display_render_scene_sprites(ctx,
							   seg,
							   screen_scale,
							   x_scale,
							   tmp_idx,
							   tmp_max_y_idx,
							   tmp_max_y_bis_idx);

		// display start line on 1st segment
		if (idx == 0)
			ret = display_render_start_line_sprite(
				ctx,
				seg,
				screen_scale,
				x_scale,
				tmp_idx,
				tmp_max_y_idx,
				tmp_max_y_bis_idx);

		ret = display_render_ai_cars_sprites(ctx,
						     seg,
						     screen_scale,
						     x_scale,
						     idx,
						     tmp_idx,
						     tmp_max_y_idx,
						     tmp_max_y_bis_idx);
	}

	return ret;
}


static int display_render_road(struct game_context *ctx)
{

	int base_segment_idx = inline_get_segment_idx(ctx, ctx->pcar.position);
	int ratio_modulus = (ctx->pcar.position % ROAD_SEGMENT_LENGTH) /
			    ROAD_SEGMENT_LENGTH;
	float dx = -(ctx->track.segments[base_segment_idx].curve *
		     (float)ratio_modulus);
	float x = 0;
	int i, idx;

	ctx->race.max_y = SCREEN_HEIGHT;
	ctx->race.max_y_idx = 0;
	ctx->race.max_y_bis = SCREEN_HEIGHT;
	ctx->race.max_y_bis_idx = 0;

	float highest_world_y = 0;

	for (i = 0; i < ctx->race.draw_distance; i++) {

		int add_z_offset_to_first_segments = 0;
		idx = (base_segment_idx + i) % ctx->track.nb_segments;

		// fix transition from high to low idx segments.
		if (idx < base_segment_idx) {
			add_z_offset_to_first_segments = 1;
		}

		// world to screen conversion
		logic_project_coord(
			&ctx->track.segments[idx].p1,
			add_z_offset_to_first_segments
				? (int)ctx->track
					  .segments[ctx->track.nb_segments - 1]
					  .p1.world.z
				: 0,
			(int)((ctx->pcar.player_x *
			       (float)ctx->track.segments[idx].width) -
			      x),
			ctx->pcar.player_y + ctx->race.camera_height,
			ctx->pcar.position,
			ctx->race.camera_depth,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			ctx->track.segments[idx].width);

		logic_project_coord(
			&ctx->track.segments[idx].p2,
			add_z_offset_to_first_segments
				? (int)ctx->track
					  .segments[ctx->track.nb_segments - 1]
					  .p2.world.z
				: 0,
			(int)((ctx->pcar.player_x *
			       (float)ctx->track.segments[idx].width) -
			      x - dx),
			ctx->pcar.player_y + ctx->race.camera_height,
			ctx->pcar.position,
			ctx->race.camera_depth,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			ctx->track.segments[idx].width);

		x += dx;
		dx += ctx->track.segments[idx].curve;

		// skip segment behind hills
		if (ctx->track.segments[idx].p2.screen.y >=
			    ctx->track.segments[idx].p1.screen.y ||
		    ctx->track.segments[idx].p2.screen.y >= ctx->race.max_y) {
			if (!ctx->race.max_y_bis_idx && ctx->race.max_y_idx) {
				ctx->race.max_y_bis = ctx->race.max_y;
				ctx->race.max_y_bis_idx = idx;
			}
			continue;
		} else if (ctx->track.segments[idx].p1.camera.z <=
			   ctx->race.camera_depth) {
			// skip segment behind camera and thoses already
			continue;
		}

		if (ctx->track.segments[idx].p2.world.y > highest_world_y)
			highest_world_y = ctx->track.segments[idx].p2.world.y;

		display_render_segment(
			ctx,
			idx,
			SCREEN_WIDTH,
			ctx->track.segments[idx].nb_lanes,
			ctx->track.segments[idx].p1.screen.x,
			(int)ctx->track.segments[idx].p1.screen.y,
			ctx->track.segments[idx].p1.screen.w,
			ctx->track.segments[idx].p2.screen.x,
			(int)ctx->track.segments[idx].p2.screen.y,
			ctx->track.segments[idx].p2.screen.w,
			0, // TODO: fog
			ctx->track.segments[idx].color);

		ctx->race.max_y = (int)ctx->track.segments[idx].p1.screen.y;
		ctx->race.max_y_idx = idx;
	}

	return 0;
}


// render a background layer
static int display_render_background_layer(struct game_context *ctx,
					   enum background_layer bg_layer,
					   int *texture_x_offset,
					   struct texture *bg_texture)
{
	int ret;
	int bg_y_offset_num = 50;
	SDL_Rect bg_clip_rect = {.x = 0, .y = 0, .h = 0, .w = 0};

	bg_clip_rect.h = bg_texture->h;
	bg_clip_rect.w = SCREEN_WIDTH;
	bg_clip_rect.y = 0;

	if (bg_layer == BG_LAYER_LANDSCAPE_FAR)
		bg_y_offset_num = 59;

	// init bg_clip_rect.x the 1st time
	if (!*texture_x_offset)
		*texture_x_offset = bg_texture->w / 2 - SCREEN_WIDTH / 2;

	// TODO : BG rotation % speed, no rotation if speed == 0
	// TODO : do some modulus to avoid going too far
	*texture_x_offset +=
		(int)(ctx->track.segments[ctx->pcar.player_segment].curve *
		      (float)bg_layer * ctx->pcar.speed / ctx->pcar.max_speed);

	if (*texture_x_offset > bg_texture->w)
		*texture_x_offset -= bg_texture->w;
	else if (*texture_x_offset < -SCREEN_WIDTH)
		*texture_x_offset += bg_texture->w;

	bg_clip_rect.x = *texture_x_offset;

	enum another_bg_type another_bg;
	int bg_x1, bg_x2;

	if (bg_clip_rect.x > bg_texture->w - SCREEN_WIDTH) {
		bg_x1 = 0;
		bg_clip_rect.w = bg_texture->w - bg_clip_rect.x;
		another_bg = ANOTHER_BG_RIGHT;
	} else if (bg_clip_rect.x < 0) {
		bg_x1 = -bg_clip_rect.x;
		bg_clip_rect.w = SCREEN_WIDTH + bg_clip_rect.x;
		bg_clip_rect.x = 0;
		another_bg = ANOTHER_BG_LEFT;
	} else {
		bg_x1 = 0;
		another_bg = ANOTHER_BG_NONE;
	}

	ret = texture_render(ctx,
			     bg_texture,
			     bg_x1,
			     SCREEN_HEIGHT * bg_y_offset_num / 100 -
				     bg_texture->h,
			     &bg_clip_rect,
			     0.f,
			     1,
			     SDL_FLIP_NONE,
			     NULL);

	if (another_bg == ANOTHER_BG_RIGHT) {
		bg_x2 = bg_clip_rect.w;
		bg_clip_rect.x = 0;
		bg_clip_rect.w = SCREEN_WIDTH - bg_clip_rect.w;
	} else if (another_bg == ANOTHER_BG_LEFT) {
		bg_x2 = 0;
		bg_clip_rect.w = bg_x1;
		bg_clip_rect.x = bg_texture->w - bg_clip_rect.w;
	}

	if (another_bg != ANOTHER_BG_NONE) {
		ret = texture_render(ctx,
				     bg_texture,
				     bg_x2,
				     SCREEN_HEIGHT * bg_y_offset_num / 100 -
					     bg_texture->h,
				     &bg_clip_rect,
				     0.f,
				     1,
				     SDL_FLIP_NONE,
				     NULL);
	}

	return ret;
}


static int display_render_backgrounds(struct game_context *ctx)
{
	int ret;

	ret = display_render_background_layer(ctx,
					      BG_LAYER_SKY_FAR,
					      &ctx->gfx.layers_x_offset.sky_far,
					      &ctx->gfx.bg_sky_far);

	ret = display_render_background_layer(
		ctx,
		BG_LAYER_LANDSCAPE_FAR,
		&ctx->gfx.layers_x_offset.landscape_far,
		&ctx->gfx.bg_mountains);

	ret = display_render_background_layer(ctx,
					      BG_LAYER_SKY_NEAR,
					      &ctx->gfx.layers_x_offset.sky_near,
					      &ctx->gfx.bg_sky_near);

	return ret;
}

static int display_render_player_car(struct game_context *ctx)
{
	int ret;
	int player_sprite_y = ctx->pcar.player_sprite_y;

	// During start animation car y depends camera height
	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START) {
		if (ctx->race.camera_height > CAMERA_HEIGHT_RACE * 2) {
			player_sprite_y = SCREEN_HEIGHT + 1;
		} else {
			float percent = (float)(CAMERA_HEIGHT_RACE -
						(ctx->race.camera_height -
						 CAMERA_HEIGHT_RACE)) /
					(float)CAMERA_HEIGHT_RACE;
			player_sprite_y =
				SCREEN_HEIGHT -
				(int)((float)(SCREEN_HEIGHT -
					      ctx->pcar.player_sprite_y) *
				      percent);
		}
	}

	/*SDL_Log("[%s][h=%d] ctx->pcar.player_sprite_y = %d, player_sprite_y =
	   %d",
		__func__,
		ctx->race.camera_height,
		ctx->pcar.player_sprite_y,
		player_sprite_y);*/

	ret = texture_render(ctx,
			     &ctx->gfx.cars[ctx->pcar.car_player_model]
					   [ctx->pcar.car_player_sprite_idx],
			     ctx->pcar.player_sprite_x,
			     player_sprite_y,
			     NULL,
			     0.f,
			     ctx->scale_player_car[ctx->pcar.car_player_model],
			     ctx->pcar.car_player_flip,
			     NULL);

	return ret;
}


static int display_render_particles(struct game_context *ctx)
{
	// render flame burst when nitro is on
	if (ctx->status_cur == GAME_STATE_RACE_NITRO && ctx->keys.accel) {
		for (int k = 0; k < NB_PARTICLES_NITRO_DISPLAY; k++) {
			if (ctx->gfx.part_nitro[k].pos_x != 0) {
				ctx->gfx.part_nitro[k].frame++;

				if (ctx->gfx.part_nitro[k].frame % 4)
					texture_render(
						ctx,
						ctx->gfx.part_nitro[k].t,
						ctx->gfx.part_nitro[k].pos_x,
						ctx->gfx.part_nitro[k].pos_y,
						NULL,
						0.f,
						PARTICLE_NITRO_SCALE,
						SDL_FLIP_NONE,
						NULL);

				if (ctx->gfx.part_nitro[k].frame >
				    PARTICLE_NITRO_FRAME_DURATION)
					ctx->gfx.part_nitro[k].pos_x = 0;
			}
		}
	}

	// render smoke when drifting
	for (int k = 0; k < NB_PARTICLES_SMOKE_DISPLAY; k++) {
		if (ctx->gfx.part_smoke[k].pos_x != 0) {
			ctx->gfx.part_smoke[k].frame++;

			if (ctx->gfx.part_smoke[k].frame % 4)
				texture_render(ctx,
					       ctx->gfx.part_smoke[k].t,
					       ctx->gfx.part_smoke[k].pos_x,
					       ctx->gfx.part_smoke[k].pos_y,
					       NULL,
					       0.f,
					       PARTICLE_SMOKE_SCALE,
					       SDL_FLIP_NONE,
					       NULL);

			if (ctx->gfx.part_smoke[k].frame >
			    PARTICLE_SMOKE_FRAME_DURATION)
				ctx->gfx.part_smoke[k].pos_x = 0;
		}
	}

	return 0;
}


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////

int display_screen_race(struct game_context *ctx)
{
	int ret = 0;

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 135, 206, 235, 0xFF); // blue sky
	SDL_RenderClear(ctx->renderer);

	// render the different layers of background
	ret = display_render_backgrounds(ctx);

	// render the road
	ret = display_render_road(ctx);

	// render scenery sprites and AI cars
	ret = display_render_scaled_sprites(ctx);

	// display particles
	ret = display_render_particles(ctx);

	// display player car
	ret = display_render_player_car(ctx);

	// render scenery text message
	ret = display_render_hud(ctx);

	// render animations
	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START)
		ret = display_render_anim_race_start(ctx);
	if (ctx->status_cur == GAME_STATE_RACE_ANIM_END)
		ret = display_render_anim_race_end(ctx);
	if (ctx->status_cur == GAME_STATE_RACE ||
	    ctx->status_cur == GAME_STATE_RACE_COLLISION_SCENE ||
	    ctx->status_cur == GAME_STATE_RACE_NITRO)
		ret = display_render_bgm_name(ctx);

	if (ret < 0)
		SDL_Log("[%s:%d] texture_render FAILED\n", __func__, __LINE__);

	// TODO: put at the end of switch case
	// update screen
	SDL_RenderPresent(ctx->renderer);

	return ret;
}