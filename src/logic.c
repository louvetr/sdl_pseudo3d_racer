#include "common.h"

/////////////////////////////////////////////////////////////////
// static functions definition
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// public functions definition
/////////////////////////////////////////////////////////////////


int logic_project_coord(struct segment_point *p,
			int first_segments_z_offset,
			int camera_x,
			int camera_y,
			int camera_z,
			float camera_depth,
			int width,
			int height,
			int road_width)
{
	// translate coordinates from world to camera
	/*p->camera.x = (p->world.x || 0) - camera_x;
	p->camera.y = (p->world.y || 0) - camera_y;
	p->camera.z = (p->world.z || 0) - camera_z;*/
	p->camera.x = p->world.x - camera_x;
	p->camera.y = p->world.y - camera_y;
	p->camera.z = p->world.z - camera_z + first_segments_z_offset;

	/*if (p->camera.z < 0) {
		SDL_Log("[%s] p->camera.z = %f, p->world.z = %f, camera_z =%d\n",
		__func__, p->camera.z, p->world.z, camera_z);
	}*/


	// compute scaling factor
	if (p->camera.z != 0)  // TODO: what about this case ?
		p->screen.scale = camera_depth / p->camera.z;
	else
		p->screen.scale = 1;


	// TODO: scaling num/den, rounding
	// scale coordinate to screen
	p->screen.x = /*Math.round(*/
		(width / 2) + (p->screen.scale * p->camera.x * width / 2) /*)*/;
	p->screen.y = /*Math.round(*/ (height / 2) -
		      (p->screen.scale * p->camera.y * height / 2) /*)*/;
	p->screen.w =
		/*Math.round(*/ (p->screen.scale * road_width * width /
				 2) /*)*/;

	return 0;
}


int main_logic(struct game_context *ctx)
{


	if (!ctx) {
		printf("invalid parameter\n");
		return -EINVAL;
	}

	switch (ctx->status_cur) {
	case GAME_STATE_TITLE:
		break;
	case GAME_STATE_GAME:
		// logic_game(ctx);
		break;
	case GAME_STATE_QUIT:
	case GAME_STATE_PAUSE:
	case GAME_STATE_GAMEOVER:
	default:
		break;
	}

	return 0;
}