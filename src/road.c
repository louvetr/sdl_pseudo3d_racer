#include "common.h"


static int road_add_segment(struct road_segment *segment,
			    int idx,
			    float y,
			    float prev_y,
			    float curve)
// enum road_curve curve)
{
	memset(&segment->p1, 0, sizeof(segment->p1));
	memset(&segment->p2, 0, sizeof(segment->p2));

	segment->p1.world.z = idx * ROAD_SEGMENT_LENGTH;
	segment->p2.world.z = (idx + 1) * ROAD_SEGMENT_LENGTH;
	segment->p1.world.y = prev_y;
	segment->p2.world.y = y;
	segment->curve = curve;


	/*static float prev_curve;
	if (curve != prev_curve)
		SDL_Log("[%s] curve = %f\n", __func__, curve);
	prev_curve = curve;*/

	// static float prev_p2_y;
	// if (segment->p2.world.y != prev_p2_y)
	// SDL_Log("[%s] p2.w.y = %f\n", __func__, segment->p2.world.y);
	// prev_p2_y = segment->p2.world.y;

	static int local_idx = 0;
	SDL_Log("[%s][%d] idx = %f\n", __func__, local_idx, curve);
	local_idx++;


	/* TODO: use ctx->rumble_length */
	/*if (idx < 10) {
		segment->color = COLOR_START;
	} else {*/

	segment->color = (idx / RUMBLE_LENGTH /*ctx->rumble_length*/) % 2
				 ? COLOR_DARK
				 : COLOR_BRIGHT;
	//}
	return 0;
}


int road_add_sector(struct road_segment *segments,
		    int start_idx,
		    int sector_enter_lg,
		    int sector_hold_lg,
		    int sector_exit_lg,
		    int y,
		    enum road_curve curve)
{
	int i, idx, nb_segment_added, sector_total_lg;
	float start_y, end_y;
	static int prev_y = 0;
	sector_total_lg = sector_enter_lg + sector_hold_lg + sector_exit_lg;
	idx = start_idx;
	if (idx == 0)
		prev_y = 0;

	// TODO: set prev_y properly !
	start_y = prev_y;
	/*
	toInt:
		function(obj, def)
		{
			if (obj != = null) {
				var x = parseInt(obj, 10);
				if (!isNaN(x))
					return x;
			}
			return Util.toInt(def, 0);
		}
	*/

	end_y = start_y + (float)(y * ROAD_SEGMENT_LENGTH);

	SDL_Log("[%s] start_y = %f, end_y = %f\n", __func__, start_y, end_y);

	for (i = 0; i < sector_enter_lg; i++) {
		// main_road_add_segment(&segments[idx], idx, y, prev_y, curve);
		road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(
				start_y,
				end_y,
				(float)i / (float)sector_total_lg), // TODO: BUG
			prev_y,
			inline_curve_inout(
				0, curve, (float)i / (float)sector_enter_lg));
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	SDL_Log("[%s] ---------------------------------------\n", __func__);

	for (i = 0; i < sector_hold_lg; i++) {
		// idx = start_idx + nb_segment_added + i;
		road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(start_y,
					   end_y,
					   (float)(i + sector_enter_lg) /
						   (float)sector_total_lg),
			prev_y,
			curve);
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	SDL_Log("[%s] ---------------------------------------\n", __func__);

	for (i = 0; i < sector_exit_lg; i++) {
		// idx = start_idx + nb_segment_added + i;
		// main_road_add_segment(&segments[idx], idx, y, prev_y, curve);
		road_add_segment(
			&segments[idx],
			idx,
			inline_curve_inout(
				start_y,
				end_y,
				(float)(i + sector_enter_lg + sector_hold_lg) /
					(float)sector_total_lg),
			prev_y,
			inline_curve_inout(
				curve, 0, (float)i / (float)sector_exit_lg));
		prev_y = segments[idx].p2.world.y;
		idx++;
	}
	nb_segment_added += i;

	return (idx - start_idx);
}