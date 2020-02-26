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


char seglist_prev[2048];

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

static int RLTDBG_texture_render_log = 0;

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

static int texture_render(struct game_context *ctx,
			  struct texture *t,
			  int x,
			  int y,
			  SDL_Rect *clip,
			  /*int scale_num,
			  int scale_den*/
			  float scale)
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

	if (RLTDBG_texture_render_log)
		SDL_Log("[%s] clip = %p, render sprite with y = %d, w = %d, h = %d, zoom = %f\n",
			__func__,
			clip,
			y,
			render_quad.w,
			render_quad.h,
			scale);

	// SET 3rd PARAM to 'clip'
	SDL_RenderCopy(ctx->renderer, t->texture, clip, &render_quad);

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
	display_render_quad(ctx,
			    x1 - w1,
			    y1,
			    x1 + w1,
			    y1,
			    x2 + w2,
			    y2,
			    x2 - w2,
			    y2,
			    color == COLOR_DARK ? &color_dark_road_asphalt
						: &color_bright_road_asphalt);

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

static int display_render_scenery(struct game_context *ctx)
{
	int ret;
	int base_segment_idx = inline_get_segment_idx(ctx, ctx->position);
	int last_idx =
		(base_segment_idx + ctx->draw_distance) % ctx->nb_segments;
	/*int first_idx =
		(base_segment_idx + ctx->draw_distance) % ctx->nb_segments;*/

	for (int i = ctx->draw_distance; i >= 0; i--) {


		int add_z_offset_to_first_segments = 0;
		int cam_position = ctx->position;
		int idx = (base_segment_idx + i) % ctx->nb_segments;

		// fix transition from high to low idx segments.
		if (idx < base_segment_idx) {
			add_z_offset_to_first_segments = 1; // TODO: use this
		}

		// ignore segments without sprite
		if (!ctx->segments[idx].sprite_desc.t)
			continue;

		float screen_scale = ctx->segments[idx].p1.screen.scale;
		int sprite_x = ctx->segments[idx].p1.screen.x +
			       (int)(screen_scale *
				     ctx->segments[idx].sprite_desc.position *
				     (float)ctx->road_width /*2100*/ *
				     (float)SCREEN_WIDTH / 2.f);

		// TODO: filter porperly % sprite width ?
		if (sprite_x > SCREEN_WIDTH)
			continue;

		float zoom = (1.f - (float)i / (float)ctx->draw_distance) *
			     (float)0.5;
		zoom = screen_scale * SCREEN_WIDTH * 2;

		float SPRITES_SCALE = 0.3 * (1.f / 80.f);

		int destW = (ctx->segments[idx].sprite_desc.t->w *
			     screen_scale * SCREEN_WIDTH / 2) *
			    (SPRITES_SCALE * (float)ctx->road_width);

		// TODO: apply 0.9 coeff only for trees
		int sprite_y = (float)ctx->segments[idx].p1.screen.y -
			       (float)ctx->segments[idx].sprite_desc.t->h *
				       zoom /** .9f*/ /*+ 10*/;

		RLTDBG_texture_render_log = 1;

		SDL_Rect *r = NULL;

		if (idx == 1575) {
			idx++;
			idx--;
		}


		int tmp_idx;
		int tmp_max_y_idx;
		int tmp_max_y_bis_idx;
		if (ctx->max_y_idx > base_segment_idx) {
			tmp_max_y_idx = ctx->max_y_idx; 
		}
		else {
			tmp_max_y_idx = ctx->max_y_idx + ctx->nb_segments; 
		}
		if (ctx->max_y_bis_idx > base_segment_idx) {
			tmp_max_y_bis_idx = ctx->max_y_bis_idx; 
		}
		else {
			tmp_max_y_bis_idx = ctx->max_y_bis_idx + ctx->nb_segments; 
		}				
		if (idx > base_segment_idx) {
			tmp_idx = idx; 
		}
		else {
			tmp_idx = idx + ctx->nb_segments; 
		}
		// if sprite is behind a hill, set a clip to crop its lower part
		// if ((idx > ctx->max_y_idx && idx < last_idx) || (idx <
		// ctx->max_y_idx && idx > last_idx)) {
		if (tmp_idx > tmp_max_y_idx /*&& base_segment_idx < last_idx*/) {

			if (sprite_y >= ctx->max_y) {
				SDL_Log("[%s:%d] no CLIPPING\n",
					__func__,
					__LINE__);
				continue;
			}

			r = calloc(1, sizeof(SDL_Rect));
			r->x = 0;
			r->y = 0;
			r->w = (float)ctx->segments[idx]
				       .sprite_desc.t->w /**
	      zoom*/;
			int clip_h = ctx->max_y - sprite_y;
			int clip_h_inv_scale =
				// int clip_h =
				(float)(ctx->max_y - sprite_y) / zoom;
			// int clip_h = /*ctx->max_y*/ real_max_y - sprite_y;
			if (clip_h < ctx->segments[idx].sprite_desc.t->h *
					     zoom &&
			    clip_h > 0) {
				// r->h = clip_h;
				r->h = clip_h_inv_scale;
				SDL_Log("[%s] CLIPPING --- idx = %d, y_max_idx = %d, y_max = %d, sprite_y = %d, clip_h = %d, clip_h_inv_h = %d ------------------------\n",
					__func__,
					idx,
					ctx->max_y_idx,
					/*real_max_y*/ ctx->max_y,
					sprite_y,
					clip_h,
					clip_h_inv_scale);
			} else {
				r->h = ctx->segments[idx].sprite_desc.t->h;
				// continue;
			}
		} else if (tmp_idx > tmp_max_y_bis_idx /*&& base_segment_idx < last_idx*/) {
			if (sprite_y >= ctx->max_y_bis) {
				SDL_Log("[%s:%d] no CLIPPING\n",
					__func__,
					__LINE__);
				continue;
			}

			r = calloc(1, sizeof(SDL_Rect));
			r->x = 0;
			r->y = 0;
			r->w = (float)ctx->segments[idx]
				       .sprite_desc.t->w /**
	      zoom*/;
			int clip_h = ctx->max_y_bis - sprite_y;
			int clip_h_inv_scale =
				// int clip_h =
				(float)(ctx->max_y_bis - sprite_y) / zoom;
			// int clip_h = /*ctx->max_y*/ real_max_y - sprite_y;
			if (clip_h < ctx->segments[idx].sprite_desc.t->h *
					     zoom &&
			    clip_h > 0) {
				// r->h = clip_h;
				r->h = clip_h_inv_scale;
				/*SDL_Log("[%s] CLIPPING --- idx = %d, y_max_idx = %d, y_max = %d, sprite_y = %d, clip_h = %d, clip_h_inv_h = %d ------------------------\n",
					__func__,
					idx,
					ctx->max_y_idx,
					ctx->max_y,
					sprite_y,
					clip_h,
					clip_h_inv_scale);*/
			} else {
				r->h = ctx->segments[idx].sprite_desc.t->h;
				// continue;
			}
		} else {
			SDL_Log("[%s:%d] no CLIPPING\n", __func__, __LINE__);
		}

		ret = texture_render(
			ctx,
			ctx->segments[idx].sprite_desc.t,
			// sprite_x + destW,
			ctx->segments[idx].p1.screen.x +
				((float)ctx->segments[idx].p1.screen.w) * 1.3,
			sprite_y,
			r,
			zoom);

		if (r)
			free(r);

		RLTDBG_texture_render_log = 0;

		/*SDL_Log("[%s] idx = %d, screen_scale=%f, p1.screen.x = %d,
		road_width = %d, x_test = %d\n",
			__func__,
			idx,
			screen_scale,
			ctx->segments[idx].p1.screen.x,
			ctx->road_width,
			ctx->segments[idx].p1.screen.x +
				ctx->segments[idx].p1.screen.w);
		SDL_Log("[%s] idx = %d, x = %d, destW = %d, x + destW = %d, y =
		%d, scale = %f, zoom = %f\n",
			__func__,
			idx,
			sprite_x,
			destW,
			sprite_x + destW,
			sprite_y,
			screen_scale,
			zoom);*/
		SDL_Log("[%s] idx = %d, i = %d, zoom = %f, max_y_idx = %d, max_y = %d\n",
			__func__,
			idx,
			i,
			zoom,
			ctx->max_y_idx,
			ctx->max_y);
	}

	return 0;
}

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

	char seglist[2048];
	memset(seglist, 0, 2048);

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

		sprintf(seglist, "%s%03d,", seglist, idx);

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
			if (!ctx->max_y_bis_idx && ctx->max_y_idx)
			{
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

	SDL_Log("[%s] last_seg_idx_lane = %d, last_seg_idx = %d, highest_world_y = %f\n",
		__func__,
		last_seg_idx_lane,
		last_seg_idx,
		highest_world_y);

	// if (dbgcpt % 10)
	/*if (memcmp(seglist_prev, seglist, 2048))
		SDL_Log("%s\n", seglist);

	memcpy(seglist_prev, seglist, 2048);
	dbgcpt++;*/

	return 0;
}

#if 0
static int display_screen_game_test(struct game_context *ctx)
{
	int ret = 0;


	// clear screen
	// SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderClear(ctx->renderer);

	SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 0xFF);
	// SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ctx->renderer);

	// draw a rectangle
	/*SDL_Color text_color = {255, 255, 255};
	SDL_Rect r;
	// outer border
	r.w = SCREEN_WIDTH * 2 / 3;
	r.h = SCREEN_HEIGHT / 4;
	r.x = SCREEN_WIDTH / 2 - r.w / 2;
	r.y = SCREEN_HEIGHT / 2 - r.h / 2;*/
	/*SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(ctx->renderer, &r);*/


	Sint16 s[4] = {400, 800, 1000, 200};
	Sint16 t[4] = {150, 150, 580, 580};

	filledPolygonRGBA(ctx->renderer, s, t, 4, 100, 100, 100, 255);

	// SetViewport(ctx->renderer,0,60,SCREEN_WIDTH/2,60+(SCREEN_HEIGHT-80)/2);
	// SetViewport(ctx->renderer, 300, 500, 1100 , 700);
	/*filledTrigonRGBA (ctx->renderer, 700, 500, 300, 700, 1100, 700,
		200, 200, 200, 255);*/

	filledTrigonRGBA(
		ctx->renderer, 100, 50, 50, 100, 150, 100, 200, 200, 200, 255);

	// filledTrigonColor (ctx->renderer, 100, 50, 50, 100, 150, 100,
	// 0xff00ffcc);

	filledCircleColor(ctx->renderer,
			  SCREEN_WIDTH / 4,
			  SCREEN_HEIGHT / 4,
			  30,
			  0xff00ffcc);

	// update screen
	SDL_RenderPresent(ctx->renderer);

	return ret;
}
#endif


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
			     1);

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
				     1);

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


static int display_screen_game(struct game_context *ctx)
{
	int ret = 0;
	int player_x_in_pixels;

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

	// just draw the player in middle of the screen. It doesn't move, that's
	// the world around it which moves.
	player_x_in_pixels =
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
			     player_x_in_pixels,
			     ctx->player_sprite_y,
			     NULL,
			     /*1,
			     2*/
			     0.5);
	/*} else {
		ret = texture_render(ctx,
				     &ctx->gfx.car_player,
				     player_x_in_pixels,
				     ctx->player_sprite_y,
				     NULL,
				     60,
				     100);
	}*/

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
	case GAME_STATE_GAME:
		display_screen_game(ctx);
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
