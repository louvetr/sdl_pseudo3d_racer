#include "common.h"

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

struct color_desc color_lane = {
	.r = 255,
	.g = 255,
	.b = 255,
	.a = 255,
};

/* TODO: several lanes styles
		- 1 cental yellow
		- 2 central yellow
*/


/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


static int load_text_message(struct game_context *ctx,
			     TTF_Font *font,
			     struct texture *t,
			     char *string,
			     SDL_Color text_color)
{
	if (t->texture)
		SDL_DestroyTexture(t->texture);

	SDL_Surface *text_surface =
		TTF_RenderText_Solid(font, string, text_color);

	if (!text_surface) {
		SDL_Log("[%s] Unable to render text surface! SDL_ttf Error: %s\n",
			__func__,
			TTF_GetError());
		return -EINVAL;
	}

	t->texture = SDL_CreateTextureFromSurface(ctx->renderer, text_surface);
	if (!t->texture) {
		SDL_Log("[%s] Unable to create texture from rendered text! SDL Error: %s\n",
			__func__,
			SDL_GetError());
		return -EINVAL;
	}

	t->w = text_surface->w;
	t->h = text_surface->h;

	SDL_FreeSurface(text_surface);

	return 0;
}


static int texture_render(struct game_context *ctx,
			  struct texture *t,
			  int x,
			  int y,
			  SDL_Rect *clip,
			  /*int scale_num,
			  int scale_den*/
			  float scale,
			  SDL_RendererFlip flip)
{
	if (!t || !ctx) {
		SDL_Log("[%s] invalid param\n", __func__);
		return -EINVAL;
	}

	// set rendering space and render to screen
	SDL_Rect render_quad = {x, y, t->w, t->h};

	if (clip != NULL) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}

	// scaling
	/*render_quad.w = render_quad.w * scale_num / scale_den;
	render_quad.h = render_quad.h * scale_num / scale_den;*/
	render_quad.w = (int)((float)render_quad.w * scale);
	render_quad.h = (int)((float)render_quad.h * scale);

	// fix a glich: sprite seems to float 1 pixel above the road
	if (clip != NULL)
		render_quad.h++;

	// SET 3rd PARAM to 'clip'
	// SDL_RenderCopy(ctx->renderer, t->texture, clip, &render_quad);
	SDL_RenderCopyEx(
		ctx->renderer, t->texture, clip, &render_quad, 0, NULL, flip);

	return 0;
}


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
	Sint16 x[4] = {x1, x2, x3, x4};
	Sint16 y[4] = {y1, y2, y3, y4};

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
	int r1 = inline_rumble_width(w1, lanes);
	int r2 = inline_rumble_width(w2, lanes);
	int l1 = inline_lane_marker_width(w1, lanes);
	int l2 = inline_lane_marker_width(w2, lanes);

	int last_seg_idx_lane = 0;
	int last_seg_idx = 0;

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
	if (seg_idx < 3) {
		road_color = &color_road_yellow;
	} else {
		if (color == COLOR_DARK)
			road_color = &color_dark_road_asphalt;
		else
			road_color = &color_bright_road_asphalt;
	}


	display_render_quad(ctx,
			    x1 - w1,
			    y1,
			    x1 + w1,
			    y1,
			    x2 + w2,
			    y2,
			    x2 - w2,
			    y2,
				road_color/*
			    color == COLOR_DARK ? &color_dark_road_asphalt
						: &color_bright_road_asphalt*/);

	// render lanes
	if (color == COLOR_DARK && lanes > 0) {
		int lane_w1 = (w1 * 2) / lanes;
		int lane_w2 = (w2 * 2) / lanes;
		int lane_x1 = x1 - w1 + lane_w1;
		int lane_x2 = x2 - w2 + lane_w2;

		/*if(lane_w1 == 0)
			 lane_w1 = 1;
		if(lane_w2 == 0)
			 lane_w2 = 1;*/

		for (int lane = 1; lane < lanes;
		     lane_x1 += lane_w1, lane_x2 += lane_w2, lane++) {

			/*if (y1 > 700) {
				SDL_Log("[%s] draw lane
			(%d,%d),(%d,%d),(%d,%d),(%d,%d)\n",
					__func__,
					lane_x1 - l1 / 2,
					y1,
					lane_x1 + l1 / 2,
					y1,
					lane_x2 + l2 / 2,
					y2,
					lane_x2 - l2 / 2,
					y2);
			}*/

			if (l1 <= 1) {
				// far away lanes are simplified into rect
				r.x = lane_x2 - l2 / 2;
				r.y = y2;
				r.h = 2;
				r.w = 2;

				SDL_SetRenderDrawColor(ctx->renderer,
						       color_lane.r,
						       color_lane.g,
						       color_lane.b,
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
						    &color_lane);
			}
		}
	}

	// TODO: draw fog
	// Render.fog(ctx, 0, y1, width, y2-y1, fog);

	return 0;
}


static int display_load_render_text(struct game_context *ctx,
				    TTF_Font *font,
				    struct texture *t,
				    char *msg,
				    SDL_Color *color,
				    int x,
				    int y)
{
	int ret;

	ret = load_text_message(ctx, font, t, msg, *color);
	ret = texture_render(ctx, t, x, y, NULL, 1, SDL_FLIP_NONE);

	// TODO: manage error

	return ret;
}

static int display_render_text(struct game_context *ctx)
{
	int ret;
	SDL_Rect r;
	SDL_Color text_color = {0, 0, 0};
	char speed[8];
	sprintf(speed,
		"%03d",
		(int)(ctx->speed * 240.f /
		      ctx->max_speed)); // TODO: set max_speed in kph per car

	// Right
	// part///////////////////////////////////////////////////////////////
	// speed
	/*display_load_render_text(
		ctx,
		ctx->sc_font_medium,
		&ctx->gfx.font_game_speed_title,
		"speed:",
		&text_color,
		SCREEN_WIDTH - ctx->gfx.font_game_speed_title.w * 15 / 10,
		0);*/
	display_load_render_text(ctx,
				 ctx->sc_font_medium,
				 &ctx->gfx.font_game_speed_unit,
				 "kph",
				 &text_color,
				 SCREEN_WIDTH - ctx->gfx.font_game_speed_unit.w,
				 0 /*ctx->gfx.font_game_speed_title.h*/);
	display_load_render_text(ctx,
				 ctx->sc_font_big,
				 &ctx->gfx.font_game_speed_value,
				 speed,
				 &text_color,
				 SCREEN_WIDTH -
					 ctx->gfx.font_game_speed_value.w -
					 ctx->gfx.font_game_speed_unit.w,
				 0 /*ctx->gfx.font_game_speed_title.h*/);


	// Mid
	// part///////////////////////////////////////////////////////////////
	// position
	/*display_load_render_text(
		ctx,
		ctx->sc_font_medium,
		&ctx->gfx.font_game_position_title,
		"position:",
		&text_color,
		SCREEN_WIDTH / 2 - ctx->gfx.font_game_position_title.w / 2,
		0);*/
	display_load_render_text(
		ctx,
		ctx->sc_font_big,
		&ctx->gfx.font_game_position_value,
		" 1",
		&text_color,
		SCREEN_WIDTH / 2 - ctx->gfx.font_game_position_value.w / 2,
		0 /*ctx->gfx.font_game_position_title.h*/);
	display_load_render_text(
		ctx,
		ctx->sc_font_medium,
		&ctx->gfx.font_game_position_unit,
		"st",
		&text_color,
		SCREEN_WIDTH / 2 - ctx->gfx.font_game_position_value.w / 2 +
			ctx->gfx.font_game_position_value.w,
		0 /*ctx->gfx.font_game_position_unit.h*/);

	// Left
	// part///////////////////////////////////////////////////////////////
	// lap
	/*display_load_render_text(ctx,
				 ctx->sc_font_medium,
				 &ctx->gfx.font_game_lap_title,
				 "lap:",
				 &text_color,
				 0,
				 0);*/
	display_load_render_text(ctx,
				 ctx->sc_font_big,
				 &ctx->gfx.font_game_lap_value,
				 "1/5",
				 &text_color,
				 0,
				 0 /*ctx->gfx.font_game_lap_title.h*/);
	display_load_render_text(ctx,
				 ctx->sc_font_medium,
				 &ctx->gfx.font_game_lap_title,
				 "lap",
				 &text_color,
				 ctx->gfx.font_game_lap_value.w,
				 0 /*ctx->gfx.font_game_lap_title.h*/);

	return 0;
}


static int display_render_scenery(struct game_context *ctx)
{
	int ret;
	int base_segment_idx = inline_get_segment_idx(ctx, ctx->position);
	int last_idx =
		(base_segment_idx + ctx->draw_distance) % ctx->nb_segments;


	for (int i = ctx->draw_distance; i >= 0; i--) {

		int cam_position = ctx->position;
		int idx = (base_segment_idx + i) % ctx->nb_segments;
		struct road_segment *seg = &ctx->segments[idx];

		////////////////////////////////////////////////////
		int tmp_idx;
		int tmp_max_y_idx;
		int tmp_max_y_bis_idx;
		if (ctx->max_y_idx > base_segment_idx) {
			tmp_max_y_idx = ctx->max_y_idx;
		} else {
			tmp_max_y_idx = ctx->max_y_idx + ctx->nb_segments;
		}
		if (ctx->max_y_bis_idx > base_segment_idx) {
			tmp_max_y_bis_idx = ctx->max_y_bis_idx;
		} else {
			tmp_max_y_bis_idx =
				ctx->max_y_bis_idx + ctx->nb_segments;
		}
		if (idx > base_segment_idx) {
			tmp_idx = idx;
		} else {
			tmp_idx = idx + ctx->nb_segments;
		}
		////////////////////////////////////////////////////

		float screen_scale = seg->p1.screen.scale;
		float x_scale = screen_scale * SCREEN_WIDTH * 2;

		if (!seg->scene)
			goto display_ai_cars;

		for (int j = 0; j < seg->scene->nb_sprites; j++) {

			// ignore segments without sprite
			if (!seg->scene->sprite[j]->t)
				continue;

			seg->scene->sprite[j]->scale = x_scale;

			if (seg->scene->sprite[j]->position >= 0)
				seg->scene->sprite[j]->scaled_x =
					seg->p1.screen.x +
					(int)(screen_scale *
					      seg->scene->sprite[j]->position *
					      (float)ctx->road_width *
					      (float)SCREEN_WIDTH / 2.f);
			else
				seg->scene->sprite[j]->scaled_x =
					seg->p1.screen.x +
					(int)(screen_scale *
					      seg->scene->sprite[j]->position *
					      (float)ctx->road_width *
					      (float)SCREEN_WIDTH / 2.f) -
					seg->scene->sprite[j]->t->w *
						seg->scene->sprite[j]->scale;

			// TODO: filter porperly % sprite width ?
			if (seg->scene->sprite[j]->scaled_x > SCREEN_WIDTH)
				continue;

			int sprite_y = (float)seg->p1.screen.y -
				       (float)seg->scene->sprite[j]->t->h *
					       seg->scene->sprite[j]->scale;

			SDL_Rect *r = NULL;

			// if sprite is behind a hill, set a clip to crop its
			// lower part
			if (tmp_idx > tmp_max_y_idx) {

				if (sprite_y >= ctx->max_y) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->x = 0;
				r->y = 0;
				r->w = (float)seg->scene->sprite[j]->t->w;
				int clip_h = ctx->max_y - sprite_y;
				int clip_h_inv_scale =
					(float)(ctx->max_y - sprite_y) /
					seg->scene->sprite[j]->scale;
				if (clip_h < seg->scene->sprite[j]->t->h *
						     seg->scene->sprite[j]
							     ->scale &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = seg->scene->sprite[j]->t->h;
				}
				// sprite is behind a hill, crop it accodingly
			} else if (tmp_idx > tmp_max_y_bis_idx) {
				if (sprite_y >= ctx->max_y_bis) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->x = 0;
				r->y = 0;
				r->w = (float)seg->scene->sprite[j]->t->w;
				int clip_h = ctx->max_y_bis - sprite_y;
				int clip_h_inv_scale =
					(float)(ctx->max_y_bis - sprite_y) /
					seg->scene->sprite[j]->scale;
				if (clip_h < seg->scene->sprite[j]->t->h *
						     seg->scene->sprite[j]
							     ->scale &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = seg->scene->sprite[j]->t->h;
				}
			}

			ret = texture_render(ctx,
					     seg->scene->sprite[j]->t,
					     seg->scene->sprite[j]->scaled_x,
					     sprite_y,
					     r,
					     seg->scene->sprite[j]->scale,
					     seg->scene->sprite[j]->flip);

			if (r)
				free(r);
		}

	// TODO: separate in a function
	display_ai_cars:
		// TODO: display ai cars here
		// TODO: add a ref to the ai car in the segment info struct
		if (idx == ctx->ai_cars[0].segment) {

			struct road_segment *seg = &ctx->segments[idx];
			int sprite_x, sprite_y;


			float car_screen_scale =
				seg->p1.screen.scale -
				(seg->p1.screen.scale - seg->p2.screen.scale) *
					ctx->ai_cars[0].pos_z_rest_percent;

			float car_x_scale = car_screen_scale * SCREEN_WIDTH * 2;
			car_x_scale = car_x_scale * (float)AI_CAR_SPRITE_ZOOM;

			if (ctx->ai_cars[0].pos_x >= 0)
				sprite_x = seg->p1.screen.x +
					   (int)(car_screen_scale *
						 ctx->ai_cars[0].pos_x *
						 (float)ctx->road_width *
						 (float)SCREEN_WIDTH / 2.f) -
					   (float)ctx->ai_cars[0].t.w *
						   /*AI_CAR_SPRITE_ZOOM **/
						   car_x_scale / 2.f;
			else
				sprite_x = seg->p1.screen.x +
					   (int)(car_screen_scale *
						 ctx->ai_cars[0].pos_x *
						 (float)ctx->road_width *
						 (float)SCREEN_WIDTH / 2.f) -
					   (float)ctx->ai_cars[0].t.w *
						   /*AI_CAR_SPRITE_ZOOM **/
						   car_x_scale / 2.f;

			// TODO: filter porperly % sprite width ?
			if (sprite_x > SCREEN_WIDTH)
				continue;

			sprite_y = seg->p1.screen.y -
				   (seg->p1.screen.y - seg->p2.screen.y) *
					   ctx->ai_cars[0].pos_z_rest_percent -
				   (float)ctx->ai_cars[0].t.h * car_x_scale;

			//////////////////////////////////////////////////////////////////////////////////////////
			SDL_Rect *r = NULL;

			// if sprite is behind a hill, set a clip to crop its
			// lower part
			if (tmp_idx > tmp_max_y_idx) {
				if (sprite_y >= ctx->max_y) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->x = 0;
				r->y = 0;
				r->w = (float)ctx->ai_cars[0].t.w;
				int clip_h = ctx->max_y - sprite_y;
				int clip_h_inv_scale =
					(float)(ctx->max_y - sprite_y) /
					car_x_scale;
				if (clip_h <
					    ctx->ai_cars[0].t.h * car_x_scale &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = ctx->ai_cars[0].t.h;
				}
				// sprite is behind a hill, crop it accodingly
			} else if (tmp_idx > tmp_max_y_bis_idx) {
				if (sprite_y >= ctx->max_y_bis) {
					continue;
				}

				r = calloc(1, sizeof(SDL_Rect));
				r->x = 0;
				r->y = 0;
				r->w = (float)ctx->ai_cars[0].t.w;
				int clip_h = ctx->max_y_bis - sprite_y;
				int clip_h_inv_scale =
					(float)(ctx->max_y_bis - sprite_y) /
					car_x_scale;
				if (clip_h <
					    ctx->ai_cars[0].t.h * car_x_scale &&
				    clip_h > 0) {
					r->h = clip_h_inv_scale;
				} else {
					r->h = ctx->ai_cars[0].t.h;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////

			static uint32_t ticks_now = 0;
			static uint32_t ticks_prev = 0;
			static uint32_t ticks_diff = 0;
			ticks_now = SDL_GetTicks();
			ticks_diff = ticks_now - ticks_prev;
			ticks_prev = ticks_now;

			SDL_Log("[ia_car][%u][%d][%f] x=%d, y=%d, x_scale=%f, h=%f\n",
				ticks_diff,
				ctx->ai_cars[0].segment,
				ctx->ai_cars[0].pos_z_rest_percent,
				sprite_x,
				sprite_y,
				car_x_scale,
				r ? (float)r->h * car_screen_scale *
						(float)SCREEN_WIDTH * 2.f *
						(float)AI_CAR_SPRITE_ZOOM
				  : (float)ctx->ai_cars[0].t.h *
						(float)car_screen_scale *
						(float)SCREEN_WIDTH * 2.f *
						(float)AI_CAR_SPRITE_ZOOM);

			// TODO : why  ai car sprit 'h' is so jumpy ? lessen
			// this effect

			ret = texture_render(ctx,
					     &ctx->ai_cars[0].t,
					     sprite_x,
					     sprite_y,
					     r,
					     car_screen_scale * SCREEN_WIDTH *
						     2 * AI_CAR_SPRITE_ZOOM,
					     SDL_FLIP_NONE);

			if (r)
				free(r);
		}
	}

	return 0;
}


#if 0
static int display_render_ai_cars(struct game_context *ctx)
{
	int ret;
	int base_segment_idx = inline_get_segment_idx(ctx, ctx->position);
	int last_idx =
		(base_segment_idx + ctx->draw_distance) % ctx->nb_segments;


	for (int i = ctx->draw_distance; i >= 0; i--) {

		int cam_position = ctx->position;
		int idx = (base_segment_idx + i) % ctx->nb_segments;

		// TODO: add a ref to the ai car in the segment info struct
		if (idx == ctx->ai_cars[0].segment) {

			struct road_segment *seg = &ctx->segments[idx];
			int sprite_x, sprite_y;

			if (ctx->ai_cars[0].position >= 0)
				sprite_x = seg->p1.screen.x +
					   (int)(seg->p1.screen.scale *
						 ctx->ai_cars[0].position *
						 (float)ctx->road_width *
						 (float)SCREEN_WIDTH / 2.f);
			else
				sprite_x = seg->p1.screen.x +
					   (int)(seg->p1.screen.scale *
						 ctx->ai_cars[0].position *
						 (float)ctx->road_width *
						 (float)SCREEN_WIDTH / 2.f) -
					   ctx->ai_cars[0].t.w *
						   PLAYER_CAR_SPRITE_ZOOM /**
				     seg->scene->sprite[j]->scale*/
					;


			// TODO: filter porperly % sprite width ?
			if (sprite_x > SCREEN_WIDTH)
				continue;


			sprite_y = (float)seg->p1.screen.y -
				   (float)ctx->ai_cars[0].t.h *
					   seg->p1.screen.scale;

			ret = texture_render(ctx,
					     &ctx->ai_cars[0].t,
					     sprite_x,
					     sprite_y,
					     NULL,
					     seg->p1.screen.scale *
						     SCREEN_WIDTH * 2 *
						     PLAYER_CAR_SPRITE_ZOOM,
					     SDL_FLIP_NONE);

			/*ret = texture_render(ctx,
					     &ctx->ai_cars[0].t,
					     ctx->player_car_x_in_pixels,
					     ctx->player_sprite_y,
					     NULL,
					     PLAYER_CAR_SPRITE_ZOOM,
					     SDL_FLIP_NONE);*/
		}
	}

	return 0;
}
#endif

static int display_render_road(struct game_context *ctx)
{

	int base_segment_idx = inline_get_segment_idx(ctx, ctx->position);
	float ratio_modulus =
		(ctx->position % ROAD_SEGMENT_LENGTH) / ROAD_SEGMENT_LENGTH;
	float dx = -(ctx->segments[base_segment_idx].curve * ratio_modulus);
	float x = 0;
	int i, idx;

	ctx->max_y = SCREEN_HEIGHT;
	ctx->max_y_idx = 0;
	ctx->max_y_bis = SCREEN_HEIGHT;
	ctx->max_y_bis_idx = 0;

	static int dbgcpt = 0;

	float highest_world_y = 0;

	/*SDL_Log("[%s] ENTER, base_segment_idx = %d\n",
		__func__,
		base_segment_idx);*/

	int last_seg_idx_lane = 0;
	int last_seg_idx = 0;

	for (i = 0; i < ctx->draw_distance; i++) {

		int add_z_offset_to_first_segments = 0;
		int cam_position = ctx->position;
		idx = (base_segment_idx + i) % ctx->nb_segments;

		// fix transition from high to low idx segments.
		if (idx < base_segment_idx) {
			// continue;
			/*cam_position =
				ctx->position + ctx->player_z -
				ctx->segments[base_segment_idx].p1.world.z;*/
			add_z_offset_to_first_segments = 1;
		}

		// world to screen conversion
		logic_project_coord(
			&ctx->segments[idx].p1,
			add_z_offset_to_first_segments
				? ctx->segments[ctx->nb_segments - 1]
					  .p1.world
					  .z /* + ctx->segment_length */
				: 0,
			(ctx->player_x * ctx->road_width) - x,
			ctx->player_y + ctx->camera_height,
			// cam_position,
			ctx->position,
			ctx->camera_depth,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			ctx->road_width);

		logic_project_coord(
			&ctx->segments[idx].p2,
			add_z_offset_to_first_segments
				? ctx->segments[ctx->nb_segments - 1].p2.world.z
				: 0,
			(ctx->player_x * ctx->road_width) - x - dx,
			ctx->player_y + ctx->camera_height,
			// cam_position,
			ctx->position,
			ctx->camera_depth,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			ctx->road_width);

		x += dx;
		dx += ctx->segments[idx].curve;

		// if (idx == 499 || idx == 0 || idx == 1)
		/*SDL_Log("[%s][idx=%d] cam_pos=%d, p1.w.z=%f, p1.scr.z=%f",
			__func__,
			idx,
			cam_position,
			ctx->segments[idx].p1.world.z,
			ctx->segments[idx].p1.screen.z);*/

		int static cpt = 0;

		// if (/*!(cpt % 30) && */ idx < 11) {
		/*if (!(cpt % 30) &&
		    idx == inline_get_segment_idx(
				   ctx, ctx->position + ctx->player_z)) {
			SDL_Log("[%s][idx=%d] p1: world(%d, %f, %f), "
				"cam(%d, %f, %f), "
				"screen(% d, %f, %f)\n ",
				__func__,
				idx,
				ctx->segments[idx].p1.world.x,
				ctx->segments[idx].p1.world.y,
				ctx->segments[idx].p1.world.z,
				ctx->segments[idx].p1.camera.x,
				ctx->segments[idx].p1.camera.y,
				ctx->segments[idx].p1.camera.z,
				ctx->segments[idx].p1.screen.x,
				ctx->segments[idx].p1.screen.y,
				ctx->segments[idx].p1.screen.z);
			SDL_Log("[%s][idx=%d] p2: world(%d, %f, %f), "
				"cam(%d, %f, %f), "
				"screen(%d, %f, %f)\n ",
				__func__,
				idx,
				ctx->segments[idx].p2.world.x,
				ctx->segments[idx].p2.world.y,
				ctx->segments[idx].p2.world.z,
				ctx->segments[idx].p2.camera.x,
				ctx->segments[idx].p2.camera.y,
				ctx->segments[idx].p2.camera.z,
				ctx->segments[idx].p2.screen.x,
				ctx->segments[idx].p2.screen.y,
				ctx->segments[idx].p2.screen.z);
		}*/

		if (idx ==
		    inline_get_segment_idx(ctx, ctx->position + ctx->player_z))
			cpt++;


		// skip segment behind hills
		if (ctx->segments[idx].p2.screen.y >=
			    ctx->segments[idx].p1.screen.y ||
		    ctx->segments[idx].p2.screen.y >= ctx->max_y) {

			/*if (ctx->segments[idx].p1.screen.y < ctx->max_y_bis &&
			    ctx->segments[idx].p1.screen.y > ctx->max_y)*/
			/*if (!ctx->max_y_bis_idx &&
			    ctx->segments[idx].p1.screen.y > 0 &&
			    ctx->segments[idx].p1.screen.y < ctx->max_y)*/
			if (!ctx->max_y_bis_idx && ctx->max_y_idx) {
				ctx->max_y_bis = ctx->max_y;
				ctx->max_y_bis_idx = idx;
			}
			continue;
		} else if (ctx->segments[idx].p1.camera.z <=
			   ctx->camera_depth) {
			// skip segment behind camera and thoses already
			continue;
		}

		if (ctx->segments[idx].p2.world.y > highest_world_y)
			highest_world_y = ctx->segments[idx].p2.world.y;

		display_render_segment(ctx,
				       idx,
				       SCREEN_WIDTH,
				       ctx->lanes,
				       ctx->segments[idx].p1.screen.x,
				       ctx->segments[idx].p1.screen.y,
				       ctx->segments[idx].p1.screen.w,
				       ctx->segments[idx].p2.screen.x,
				       ctx->segments[idx].p2.screen.y,
				       ctx->segments[idx].p2.screen.w,
				       0, // TODO: fog
				       ctx->segments[idx].color);

		if (ctx->segments[idx].color == COLOR_DARK && ctx->lanes)
			last_seg_idx_lane = idx;

		last_seg_idx = idx;

		// if(ctx->segments[idx].p2.screen.y > ctx->max_y) {
		ctx->max_y = ctx->segments[idx].p1.screen.y;
		ctx->max_y_idx = idx;
		// if (base_segment_idx + i < ctx->nb_segments) {
		/*ctx->max_y =
			ctx->segments[base_segment_idx + i].p1.screen.y;
		ctx->max_y_idx = base_segment_idx + i;*/
		/*} else if (ctx->max_y_idx < ctx->nb_segments - 1) {
			// ctx->max_y_idx++;
			ctx->max_y_idx++;
			ctx->max_y = ctx->segments[ctx->max_y_idx].p1.screen.y;
		}*/ /*else {
			ctx->max_y = ctx->segments[idx].p1.screen.y;
			ctx->max_y_idx = idx;
		}*/
		//}
	}

	/*SDL_Log("[%s] last_seg_idx_lane = %d, last_seg_idx = %d,
	   highest_world_y = %f\n",
		__func__,
		last_seg_idx_lane,
		last_seg_idx,
		highest_world_y);*/

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
	*texture_x_offset += ctx->segments[ctx->player_segment].curve *
			     bg_layer * ctx->speed / ctx->max_speed;

	/*SDL_Log("speed = %f, texture_x_offset = %d, delta_x = %d\n",
		ctx->speed,
		*texture_x_offset,
		(int) (ctx->segments[ctx->player_segment].curve * bg_layer *
			ctx->speed / ctx->max_speed));*/


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
			     // 1,
			     1,
			     SDL_FLIP_NONE);

	/*SDL_Log("[Rect_1] x = %d, clip { x = %d, w = %d }\n",
		bg_x1,
		bg_clip_rect.x,
		bg_clip_rect.w);*/

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
				     // 1,
				     1,
				     SDL_FLIP_NONE);

		/*SDL_Log("[Rect_2] x = %d, clip { x = %d, w = %d }\n",
			bg_x2,
			bg_clip_rect.x,
			bg_clip_rect.w);*/
	}

	return 0;
}


static int display_render_backgrounds(struct game_context *ctx)
{
	int ret;

	ret = display_render_background_layer(ctx,
					      BG_LAYER_SKY_FAR,
					      &ctx->layers_x_offset.sky_far,
					      &ctx->gfx.bg_sky_far);

	ret = display_render_background_layer(
		ctx,
		BG_LAYER_LANDSCAPE_FAR,
		&ctx->layers_x_offset.landscape_far,
		&ctx->gfx.bg_mountains);

	/*
	ret = display_render_background_layer(
		ctx,
		BG_LAYER_LANDSCAPE_NEAR,
		&ctx->layers_x_offset.landscape_near,
		&ctx->gfx.bg_?);*/

	ret = display_render_background_layer(ctx,
					      BG_LAYER_SKY_NEAR,
					      &ctx->layers_x_offset.sky_near,
					      &ctx->gfx.bg_sky_near);

	return 0;
}


static int display_screen_race(struct game_context *ctx)
{
	int ret = 0;
	// int player_car_x_in_pixels;

	// SDL_Log("[%s] ENTER\n", __func__);

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 135, 206, 235, 0xFF); // blue sky
	SDL_RenderClear(ctx->renderer);

	// render the different layers of background
	ret = display_render_backgrounds(ctx);

	// render the road
	ret = display_render_road(ctx);

	// render scenery sprites
	ret = display_render_scenery(ctx);

	// render ai cars sprites
	// ret = display_render_ai_cars(ctx);

	// just draw the player in middle of the screen. It doesn't move, that's
	// the world around it which moves.
	ctx->player_car_x_in_pixels =
		(int)(SCREEN_WIDTH / 2) -
		(ctx->gfx.car_player.w * 1 /
		 (2 * 2)); // reduce texture by 2 then remove it half width

	//////////////// render player car
	// TODO put somewhere else
	if (!ctx->player_sprite_y)
		ctx->player_sprite_y =
			SCREEN_HEIGHT - (ctx->gfx.car_player.h * 1 / 2) - 30;

	/*SDL_Log("[%s] car_player y = %d => %d\n",
		__func__,
		ctx->player_y,
		ctx->player_sprite_y);*/


	// TODO : "zoom" car sprite on HIGH downhill
	int player_segment =
		inline_get_segment_idx(ctx, ctx->position + ctx->player_z);

	/*float delta_y = ctx->player_y -
	ctx->segments[player_segment].p2.world.y; if (fabsf(delta_y) < 20 ) {*/

	ret = texture_render(ctx,
			     &ctx->gfx.car_player,
			     ctx->player_car_x_in_pixels,
			     ctx->player_sprite_y,
			     NULL,
			     PLAYER_CAR_SPRITE_ZOOM,
			     SDL_FLIP_NONE);

	// render scenery text message
	ret = display_render_text(ctx);

	if (ret < 0)
		SDL_Log("[%s:%d] texture_render FAILED\n", __func__, __LINE__);

	// update screen
	SDL_RenderPresent(ctx->renderer);

	return ret;
}

/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////


int main_display(struct game_context *ctx)
{

	// SDL_Log("[%s] ENTER\n", __func__);

	if (!ctx) {
		printf("invalid parameter\n");
		return -EINVAL;
	}

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_QUIT:
		break;
	case GAME_STATE_RACE:
	case GAME_STATE_RACE_COLLISION_SCENE:
		display_screen_race(ctx);
		break;
	case GAME_STATE_PAUSE:
		break;
	case GAME_STATE_GAMEOVER:
		break;
	default:
		SDL_Log("[%s] invalid state = %d\n", __func__, ctx->status_cur);
		break;
	}

	return 0;
}
