#include "common.h"

#define BORDER 0


enum another_bg_type { ANOTHER_BG_NONE, ANOTHER_BG_LEFT, ANOTHER_BG_RIGHT };


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

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////

static int texture_render(struct game_context *ctx,
			  struct texture *t,
			  int x,
			  int y,
			  SDL_Rect *clip,
			  int scale_num,
			  int scale_den)
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
	render_quad.w = render_quad.w * scale_num / scale_den;
	render_quad.h = render_quad.h * scale_num / scale_den;

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


static int display_render_road(struct game_context *ctx)
{

	int base_segment_idx = inline_get_segment_idx(ctx, ctx->position);
	float ratio_modulus =
		(ctx->position % ROAD_SEGMENT_LENGTH) / ROAD_SEGMENT_LENGTH;
	float dx = -(ctx->segments[base_segment_idx].curve * ratio_modulus);
	float x = 0;

	int max_y = SCREEN_HEIGHT;
	static int dbgcpt = 0;

	char seglist[2048];
	memset(seglist, 0, 2048);

	/*SDL_Log("[%s] ENTER, base_segment_idx = %d\n",
		__func__,
		base_segment_idx);*/

	int last_seg_idx_lane = 0;
	int last_seg_idx = 0;

	for (int i = 0; i < ctx->draw_distance; i++) {

		int add_z_offset_to_first_segments = 0;
		int cam_position = ctx->position;
		int idx = (base_segment_idx + i) % ctx->nb_segments;

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

		// skip segment behind camera and thoses already
		// rendered
		if (ctx->segments[idx].p1.camera.z <= ctx->camera_depth ||
		    ctx->segments[idx].p2.screen.y >= max_y)
			continue;

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

		max_y = ctx->segments[idx].p2.screen.y;
	}

	/*SDL_Log("[%s] last_seg_idx_lane = %d, last_seg_idx = %d\n",
		__func__,
		last_seg_idx_lane,
		last_seg_idx);*/

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

static int display_screen_game(struct game_context *ctx)
{
	int ret = 0;
	int player_x_in_pixels;

	static int bg_mountains_x = 0;
	static int bg_mountains_x_prev = 0;


	// SDL_Log("[%s] ENTER\n", __func__);

	// clear screen
	SDL_SetRenderDrawColor(ctx->renderer, 135, 206, 235, 0xFF); // blue sky
	SDL_RenderClear(ctx->renderer);

	// render back ground
	// 1 --- mountains

	static SDL_Rect bg_clip_rect = {.x = 0, .y = 0, .h = 0, .w = 0};
	static int bg_mountains_scrolling_offset = 0;

	bg_mountains_scrolling_offset -=
		ctx->segments[ctx->player_segment].curve * 4;
	if (bg_mountains_scrolling_offset < -ctx->gfx.bg_mountains.w)
		bg_mountains_scrolling_offset = 0;

	bg_clip_rect.h = ctx->gfx.bg_mountains.h;
	// bg_clip_rect.w = SCREEN_WIDTH + bg_mountains_scrolling_offset;
	bg_clip_rect.w = SCREEN_WIDTH;
	// bg_clip_rect.w = ctx->gfx.bg_mountains.w;

	bg_clip_rect.y =
		0; // SCREEN_HEIGHT * 59 / 100 - ctx->gfx.bg_mountains.h;


	// init bg_clip_rect.x the 1st time
	if (!bg_mountains_x_prev)
		bg_mountains_x_prev = ctx->gfx.bg_mountains.w / 2 - SCREEN_WIDTH / 2;

	// TODO : BG rotation % speed, no rotation if speed == 0
	bg_mountains_x_prev += ctx->segments[ctx->player_segment].curve * 4;
	bg_clip_rect.x = bg_mountains_x_prev;

	enum another_bg_type another_bg;
	int bg_x1, bg_x2;

	if (bg_clip_rect.x > ctx->gfx.bg_mountains.w - SCREEN_WIDTH) {
		bg_x1 = 0;
		bg_clip_rect.w = ctx->gfx.bg_mountains.w - bg_clip_rect.x;
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

	/*if (bg_clip_rect.x + SCREEN_WIDTH > ctx->gfx.bg_mountains.w)
		bg_clip_rect.w = ctx->gfx.bg_mountains.w - bg_clip_rect.x;*/

	ret = texture_render(ctx,
			     &ctx->gfx.bg_mountains,
			     bg_x1, // bg_mountains_scrolling_offset,
			     SCREEN_HEIGHT * 59 / 100 - ctx->gfx.bg_mountains.h,
			     &bg_clip_rect,
			     1,
			     1);

	SDL_Log("[Rect_1] x = %d, clip { x = %d, w = %d }\n",
		bg_x1,
		bg_clip_rect.x,
		bg_clip_rect.w);

	// bg_clip_rect.w = SCREEN_WIDTH + bg_mountains_scrolling_offset;
	if (another_bg == ANOTHER_BG_RIGHT) {
		bg_x2 = bg_clip_rect.w;
		bg_clip_rect.x = 0;
		bg_clip_rect.w = SCREEN_WIDTH - bg_clip_rect.w;
	} else if (another_bg == ANOTHER_BG_LEFT) {
		bg_x2 = 0;
		bg_clip_rect.w = bg_x1;
		bg_clip_rect.x = ctx->gfx.bg_mountains.w - bg_clip_rect.x;
	}

	if (another_bg != ANOTHER_BG_NONE) {
		ret = texture_render(
			ctx,
			&ctx->gfx.bg_mountains,
			bg_x2, // bg_mountains_scrolling_offset + SCREEN_WIDTH,
			SCREEN_HEIGHT * 59 / 100 - ctx->gfx.bg_mountains.h,
			&bg_clip_rect,
			1,
			1);

		SDL_Log("[Rect_2] x = %d, clip { x = %d, w = %d }\n",
			bg_x2,
			bg_clip_rect.x,
			bg_clip_rect.w);
	}

	// render the road
	ret = display_render_road(ctx);

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
			     1,
			     2);
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
