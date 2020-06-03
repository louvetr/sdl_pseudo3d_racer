#include "main.h"

#define BORDER 0


//enum another_bg_type { ANOTHER_BG_NONE, ANOTHER_BG_LEFT, ANOTHER_BG_RIGHT };

/* identifies the different layers. Their value is the coefficient to which
 * they scroll */
enum background_layer {
	BG_LAYER_SKY_FAR = 2,
	BG_LAYER_LANDSCAPE_FAR = 4,
	BG_LAYER_LANDSCAPE_NEAR = 5,
	BG_LAYER_SKY_NEAR = 6
};

/*struct color_desc color_road_yellow = {
	.r = 255,
	.g = 234,
	.b = 0,
	.a = 255,
};

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
};*/


/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


int load_text_message(struct game_context *ctx,
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

int display_load_render_text(struct game_context *ctx,
				    TTF_Font *font,
				    struct texture *t,
				    char *msg,
				    SDL_Color *color,
				    int x,
				    int y,
				    float angle)
{
	int ret;

	ret = load_text_message(ctx, font, t, msg, *color);
	ret = texture_render(ctx, t, x, y, NULL, angle, 1, SDL_FLIP_NONE, NULL);

	// TODO: manage error

	return ret;
}


int display_load_render_text_with_shade(struct game_context *ctx,
					       TTF_Font *font,
					       struct texture *t,
					       char *msg,
					       SDL_Color *color_front,
					       SDL_Color *color_shadow,
					       int x_front,
					       int y_front,
					       int shadow_num,
					       int shadow_den,
					       float angle)
{

	display_load_render_text(ctx,
				 font,
				 t,
				 msg,
				 color_shadow,
				 x_front + t->w * shadow_num / shadow_den,
				 y_front + t->h * shadow_num / shadow_den,
				 angle);

	display_load_render_text(
		ctx, font, t, msg, color_front, x_front, y_front, angle);

	return 0;
}


int texture_render(struct game_context *ctx,
			  struct texture *t,
			  int x,
			  int y,
			  SDL_Rect *clip,
			  float angle,
			  float scale,
			  SDL_RendererFlip flip,
			  SDL_Rect *hitbox)
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

	// workaround to avoid random blinking AI car sprite in middle of screen
	if (hitbox && y + render_quad.h < ctx->race.max_y) {
		/*SDL_Log("[%s] AI CAR GLITCH
		   ##################################\n",
			__func__);*/
		return 0;
	}

	SDL_RenderCopyEx(ctx->renderer,
			 t->texture,
			 clip,
			 &render_quad,
			 angle,
			 NULL,
			 flip);


	/* Set hitbox. Only for AI cars since scene sprite hitbox doesn't always
	 * follow the sprite shape (eg. tree with trunk) */
	if (hitbox) {
		memcpy(hitbox, &render_quad, sizeof(SDL_Rect));
	}

	return 0;
}


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////


int main_display(struct game_context *ctx)
{

	// SDL_Log("[%s] ENTER\n", __func__);

	if (!ctx) {
		SDL_Log("invalid parameter\n");
		return -EINVAL;
	}

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_QUIT:
		break;
	case GAME_STATE_MENU_MAIN:
		display_screen_menu_main(ctx);
		break;
	case GAME_STATE_MENU_SELECT_TRACK:
		display_screen_menu_select_track(ctx);
		break;
	case GAME_STATE_MENU_SELECT_CAR:
		display_screen_menu_select_car(ctx);
		break;
	case GAME_STATE_RACE:
	case GAME_STATE_RACE_ANIM_START:
	case GAME_STATE_RACE_ANIM_END:
	case GAME_STATE_RACE_NITRO:
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
