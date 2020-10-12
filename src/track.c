#include "track.h"
#include "main.h"

struct color_desc cd_sky_blue = {.r = 135,
						.g = 206,
						.b = 235};
/*struct color_desc cd_sky_night = {.r = 47,
						.g = 47,
						.b = 119};*/
struct color_desc cd_sky_night = {.r = 17,
						.g = 17,
						.b = 89};

struct color_desc cd_lane_yellow = {.r = 255, .g = 234, .b = 0};
struct color_desc cd_lane_white = {.r = 255, .g = 255, .b = 255};
struct color_desc cd_lane_black = {.r = 0, .g = 0, .b = 0};

struct color_desc cd_road_asphalt_bright = {.r = 140, .g = 140, .b = 140};
struct color_desc cd_road_asphalt_dark = {.r = 128, .g = 128, .b = 128};
struct color_desc cd_road_asphaltdark_bright = {.r = 0x58,
						.g = 0x55,
						.b = 0x54};
struct color_desc cd_road_asphaltdark_dark = {.r = 0x3b, .g = 0x39, .b = 0x38};
struct color_desc cd_road_mud_bright = {.r = 149, .g = 69, .b = 53};
struct color_desc cd_road_mud_dark = {.r = 129, .g = 49, .b = 33};
struct color_desc cd_road_ice_bright = {.r = 81, .g = 115, .b = 176};
struct color_desc cd_road_ice_dark = {.r = 61, .g = 95, .b = 156};
struct color_desc cd_road_stone_bright = {.r = 255, .g = 252, .b = 240};
struct color_desc cd_road_stone_dark = {.r = 235, .g = 232, .b = 220};

struct color_desc cd_grass_bright = {.r = 0, .g = 169, .b = 0};
struct color_desc cd_grass_dark = {.r = 0, .g = 160, .b = 0};
struct color_desc cd_grassdark_bright = {.r = 0, .g = 79, .b = 0};
struct color_desc cd_grassdark_dark = {.r = 0, .g = 70, .b = 0};
struct color_desc cd_rumble_bright = {.r = 255, .g = 255, .b = 255};
struct color_desc cd_rumble_dark = {.r = 255, .g = 0, .b = 0};
struct color_desc cd_rumble_mud_bright = {.r = 123, .g = 63, .b = 0};
struct color_desc cd_rumble_mud_dark = {.r = 103, .g = 43, .b = 0};
struct color_desc cd_rumble_ice_bright = {.r = 141, .g = 175, .b = 236};
struct color_desc cd_rumble_ice_dark = {.r = 121, .g = 155, .b = 216};
struct color_desc cd_rumble_stone_bright = {.r = 195, .g = 192, .b = 180};
struct color_desc cd_rumble_stone_dark = {.r = 175, .g = 172, .b = 160};
/*struct color_desc cd_rumble_mud_bright = {.r = 138, .g = 51, .b = 36};
struct color_desc cd_rumble_mud_dark = {.r = 118, .g = 31, .b = 16};*/
/*struct color_desc cd_rumble_mud_bright = {.r = 130, .g = 102, .b = 68};
struct color_desc cd_rumble_mud_dark = {.r = 110, .g = 82, .b = 48};*/

struct color_desc cd_water_bright = {.r = 38, .g = 75, .b = 106};
struct color_desc cd_water_dark = {.r = 58, .g = 95, .b = 126};
struct color_desc cd_foam_bright = {.r = 240, .g = 240, .b = 240};
struct color_desc cd_foam_dark = {.r = 220, .g = 220, .b = 220};
struct color_desc cd_sand_bright = {.r = 248, .g = 220, .b = 172};
struct color_desc cd_sand_dark = {.r = 228, .g = 200, .b = 152};
struct color_desc cd_desert_bright = {.r = 247, .g = 205, .b = 45};
struct color_desc cd_desert_dark = {.r = 237, .g = 167, .b = 35};
struct color_desc cd_mud_bright = {.r = 193, .g = 154, .b = 107};
struct color_desc cd_mud_dark = {.r = 173, .g = 134, .b = 87};
struct color_desc cd_ice_bright = {.r = 215, .g = 255, .b = 254};
struct color_desc cd_ice_dark = {.r = 195, .g = 235, .b = 234};
/*struct color_desc cd_stone_bright = {.r = 202, .g = 191, .b = 191};
struct color_desc cd_stone_dark = {.r = 182, .g= 171, .b = 171};*/
struct color_desc cd_stone_bright = {.r = 222, .g = 221, .b = 221};
struct color_desc cd_stone_dark = {.r = 202, .g = 191, .b = 191};

static struct track_build_info track_build_tab[TRACK_LAST] = {
	{.nb_sector = NB_SECTOR_DIJON, .nb_segment = NB_SEGMENT_DIJON},
	{.nb_sector = NB_SECTOR_SPEEDWAY, .nb_segment = NB_SEGMENT_SPEEDWAY},
	{.nb_sector = NB_SECTOR_FORK, .nb_segment = NB_SEGMENT_FORK},
	{.nb_sector = NB_SECTOR_FROST, .nb_segment = NB_SEGMENT_FROST},
	{.nb_sector = NB_SECTOR_WHALE, .nb_segment = NB_SEGMENT_WHALE},
	{.nb_sector = NB_SECTOR_CURVES, .nb_segment = NB_SEGMENT_CURVES},
	{.nb_sector = NB_SECTOR_HORNS, .nb_segment = NB_SEGMENT_HORNS},
	{.nb_sector = NB_SECTOR_SQUARES, .nb_segment = NB_SEGMENT_SQUARES},
	{.nb_sector = NB_SECTOR_STONE, .nb_segment = NB_SEGMENT_STONE},
	{.nb_sector = NB_SECTOR_CARMONA, .nb_segment = NB_SEGMENT_CARMONA}};


static int sector_dijon[NB_SECTOR_DIJON][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 3, 2},
	{LG_SHORT, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_UP_LOW, CURVE_L_EASY, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 2, 2},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 3, 2},

	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_R_MEDIUM, 2, 2},
	{LG_LONG, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_MEDIUM, 2, 2},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}


};

static int sector_speedway[NB_SECTOR_SPEEDWAY][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 4},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 4, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 4, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}};


static int sector_fork[NB_SECTOR_FORK][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_L_MEDIUM, 3, 2},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_EASY, 2, 2},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_L_MEDIUM, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}};

static int sector_frost[NB_SECTOR_FROST][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM,
	 LG_MEDIUM,
	 LG_MEDIUM,
	 HILL_NONE /*HILL_DOWN_MEDIUM*/,
	 CURVE_NONE,
	 3,
	 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},
	//{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_L_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 2},
	{LG_MEDIUM,
	 LG_MEDIUM,
	 LG_MEDIUM,
	 /*HILL_UP_MEDIUM*/ HILL_DOWN_MEDIUM /*HILL_NONE*/,
	 CURVE_NONE,
	 2,
	 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 2, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_L_HARD, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_NONE, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_L_HARD, 2, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_R_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};

static int sector_stone[NB_SECTOR_STONE][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_LONG, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 4, 4},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 4, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 2},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_L_MEDIUM, 2, 2},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_L_EASY, 2, 2},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_SHORT, LG_LONG, LG_MEDIUM, HILL_UP_HIGH, CURVE_R_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_horns[NB_SECTOR_HORNS][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_R_HARD, 4, 4},
	{LG_LONG,
	 LG_LONG,
	 LG_LONG,
	 HILL_UP_HIGH /*HILL_DOWN_HIGH*/,
	 CURVE_R_HARD,
	 4,
	 4},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 4, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_L_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_L_HARD, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_R_HARD, 4, 4},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_R_HARD, 4, 4},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 4, 3}};


static int sector_curves[NB_SECTOR_CURVES][NB_SECTOR_PARAM] = {
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_LOW, CURVE_L_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_MEDIUM, CURVE_R_MEDIUM, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 4, 4},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_R_HARD, 4, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_MEDIUM, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_R_HARD, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_NONE, 2, 2},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_MEDIUM, CURVE_L_HARD, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_NONE, 2, 2},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_squares[NB_SECTOR_SQUARES][NB_SECTOR_PARAM] = {

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},


	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 2},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 2, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 4, 4},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 4, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 2},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_UP_SLIGHT, CURVE_L_HARD, 2, 2},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_DOWN_SLIGHT, CURVE_NONE, 2, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},


	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	//{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_whale[NB_SECTOR_WHALE][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_SLIGHT, CURVE_NONE, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_LOW, CURVE_L_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_NONE, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_R_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 2, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_MEDIUM, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_LOW, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_SLIGHT, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 2},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 2, 2},
	{LG_MEDIUM,
	 LG_MEDIUM,
	 LG_MEDIUM,
	 HILL_DOWN_MEDIUM,
	 CURVE_L_MEDIUM,
	 2,
	 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 2, 2},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_carmona[NB_SECTOR_CARMONA][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_MEDIUM,
	 LG_MEDIUM,
	 LG_MEDIUM,
	 HILL_DOWN_MEDIUM,
	 CURVE_R_MEDIUM,
	 4,
	 4},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 4, 4},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 4, 4},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_MEDIUM, CURVE_NONE, 4, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_EASY, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_HIGH, CURVE_NONE, 2, 2},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_LOW, CURVE_NONE, 2, 2},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_EASY, 2, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_LOW, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_UP_MEDIUM, CURVE_R_EASY, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};


static SDL_Rect hitbox_oak = {.x = 262, .y = 0, .w = 240, .h = 711};
static SDL_Rect hitbox_stree = {.x = 477, .y = 0, .w = 300, .h = 1400};
static SDL_Rect hitbox_tunnel_a = {.x = 292, .y = 0, .w = 1700, .h = 0};


static int set_scene_sprite_desc(struct scene_sprite_desc *sprite_desc,
				 struct texture *t,
				 float position,
				 SDL_Rect *hitbox,
				 int collide,
				 SDL_RendererFlip flip)
{
	sprite_desc->position = position;
	sprite_desc->t = t;
	sprite_desc->hitbox = hitbox;
	sprite_desc->collide = collide;
	sprite_desc->flip = flip;

	return 0;
}

// TODO: use realloc at each sector addition instead counting total nb sectors
// in advance

static int track_build_carmona(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_CARMONA; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_carmona[i][SECTOR_PARAM_ENTER_LG],
			sector_carmona[i][SECTOR_PARAM_HOLD_LG],
			sector_carmona[i][SECTOR_PARAM_EXIT_LG],
			sector_carmona[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_carmona[i][SECTOR_PARAM_EXIT_CURVE],
			sector_carmona[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_carmona[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_carmona[i][SECTOR_PARAM_ENTER_LG] +
				sector_carmona[i][SECTOR_PARAM_HOLD_LG] +
				sector_carmona[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_HALF;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_grass_dark;
	ctx->track.cd_road_bright = &cd_road_asphaltdark_bright;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_white;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_grass_bright;
	ctx->track.cds[0].dark = &cd_grass_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	struct scene_seg_desc *scene_circus_n_tree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_circus_n_tree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	float stree_step = 2.f;

	set_scene_sprite_desc(&scene_circus_n_tree->sprite[0],
			      &ctx->gfx.scene_circus,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_circus_n_tree->sprite[1],
			      &ctx->gfx.scene_circus,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE /*SDL_FLIP_HORIZONTAL*/);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_circus_n_tree->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      stree_step * (float)(i) + 4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_circus_n_tree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -stree_step * (float)(i)-4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_carousel_n_tree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_carousel_n_tree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_carousel_n_tree->sprite[0],
			      &ctx->gfx.scene_carousel,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_carousel_n_tree->sprite[1],
			      &ctx->gfx.scene_carousel,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_carousel_n_tree->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      stree_step * (float)(i) + 4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_carousel_n_tree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -stree_step * (float)(i)-4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_rollercoaster_n_tree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rollercoaster_n_tree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_rollercoaster_n_tree->sprite[0],
			      &ctx->gfx.scene_rollercoaster,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_rollercoaster_n_tree->sprite[1],
			      &ctx->gfx.scene_rollercoaster,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_rollercoaster_n_tree->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      stree_step * (float)(i) + 5.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rollercoaster_n_tree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -stree_step * (float)(i) - 5.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_greatwheel_n_tree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_greatwheel_n_tree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_greatwheel_n_tree->sprite[0],
			      &ctx->gfx.scene_greatwheel,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_greatwheel_n_tree->sprite[1],
			      &ctx->gfx.scene_greatwheel,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_greatwheel_n_tree->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      stree_step * (float)(i) + 4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_greatwheel_n_tree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -stree_step * (float)(i) - 4.f,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	int seg_step = 60;

	for (int i = 1; i < nb_segments_added * 3 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_circus_n_tree;

	for (int i = 1 + nb_segments_added * 3 / 16; i < nb_segments_added * 7 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_greatwheel_n_tree;

	for (int i = 1 + nb_segments_added * 7 / 16; i < nb_segments_added * 11 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rollercoaster_n_tree;

	for (int i = 1 + nb_segments_added * 11 / 16; i < nb_segments_added * 15 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_carousel_n_tree;

	for (int i = 1 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_circus_n_tree;

	return 0;
}


static int track_build_whale(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_WHALE; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_whale[i][SECTOR_PARAM_ENTER_LG],
			sector_whale[i][SECTOR_PARAM_HOLD_LG],
			sector_whale[i][SECTOR_PARAM_EXIT_LG],
			sector_whale[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_whale[i][SECTOR_PARAM_EXIT_CURVE],
			sector_whale[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_whale[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_whale[i][SECTOR_PARAM_ENTER_LG] +
				sector_whale[i][SECTOR_PARAM_HOLD_LG] +
				sector_whale[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_HALF;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_road_asphalt_bright;
	ctx->track.cd_road_bright = &cd_road_asphaltdark_bright;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_white;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_road_asphalt_bright;
	ctx->track.cds[0].dark = &cd_road_asphalt_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	////////////////////////
	struct scene_seg_desc *scene_buildine_01 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_buildine_01->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_buildine_01->sprite[0],
			      &ctx->gfx.scene_building_01,
			      -2.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_01->sprite[1],
			      &ctx->gfx.scene_building_01,
			      2.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_01->sprite[2],
			      &ctx->gfx.scene_building_02,
			      -5.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_01->sprite[3],
			      &ctx->gfx.scene_building_02,
			      5.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_01->sprite[4],
			      &ctx->gfx.scene_building_03,
			      -8.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_01->sprite[5],
			      &ctx->gfx.scene_building_03,
			      8.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	///////////////////////
	struct scene_seg_desc *scene_buildine_02 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_buildine_02->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_buildine_02->sprite[0],
			      &ctx->gfx.scene_building_02,
			      -2.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_02->sprite[1],
			      &ctx->gfx.scene_building_02,
			      2.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_02->sprite[2],
			      &ctx->gfx.scene_building_01,
			      -5.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_02->sprite[3],
			      &ctx->gfx.scene_building_01,
			      5.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_02->sprite[4],
			      &ctx->gfx.scene_building_03,
			      -8.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_02->sprite[5],
			      &ctx->gfx.scene_building_03,
			      8.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	//////////////////////////
	struct scene_seg_desc *scene_buildine_03 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_buildine_03->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_buildine_03->sprite[0],
			      &ctx->gfx.scene_building_03,
			      -2.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_03->sprite[1],
			      &ctx->gfx.scene_building_03,
			      2.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_03->sprite[2],
			      &ctx->gfx.scene_building_02,
			      -5.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_03->sprite[3],
			      &ctx->gfx.scene_building_02,
			      5.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_buildine_03->sprite[4],
			      &ctx->gfx.scene_building_01,
			      -8.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_buildine_03->sprite[5],
			      &ctx->gfx.scene_building_01,
			      8.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	//////////////////////////
	struct scene_seg_desc *scene_bench_n_billboard =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_bench_n_billboard->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[0],
			      &ctx->gfx.scene_billboard_beach,
			      -2.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[1],
			      &ctx->gfx.scene_lantern,
			      2.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[2],
			      &ctx->gfx.scene_building_02,
			      -5.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[3],
			      &ctx->gfx.scene_bench,
			      3.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[4],
			      &ctx->gfx.scene_building_01,
			      -8.0f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_bench_n_billboard->sprite[5],
			      &ctx->gfx.scene_bush_flower,
			      4.0f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	float rstep = 1.0f;
	for (int i = 6; i < 20; i++) {
		float position = (float)(i - 5) * rstep + 4.f;
		set_scene_sprite_desc(&scene_bench_n_billboard->sprite[i],
				      &ctx->gfx.scene_tree_willow,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}


	/////////////////////////////////////////////
	struct scene_seg_desc *scene_tunnel_bright =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_tunnel_bright->nb_sprites = 1;
	scene_tunnel_bright->type = SCENE_SPRITE_CENTERED;
	set_scene_sprite_desc(&scene_tunnel_bright->sprite[0],
			      &ctx->gfx.scene_tunnel_a_bright,
			      1.5f,
			      &hitbox_tunnel_a,
			      1,
			      SDL_FLIP_NONE);

	struct scene_seg_desc *scene_tunnel_dark =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_tunnel_dark->nb_sprites = 1;
	scene_tunnel_dark->type = SCENE_SPRITE_CENTERED;
	set_scene_sprite_desc(&scene_tunnel_dark->sprite[0],
			      &ctx->gfx.scene_tunnel_a_dark,
			      1.5f,
			      &hitbox_tunnel_a,
			      1,
			      SDL_FLIP_NONE);


	//////////////////////////////////////////////////////////
	int seg_step = 90;
	for (int i = 1 + nb_segments_added * 0 / 16;
	     i < nb_segments_added * 6 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_01;
	for (int i = 31 + nb_segments_added * 0 / 16;
	     i < nb_segments_added * 6 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_02;
	for (int i = 61 + nb_segments_added * 0 / 16;
	     i < nb_segments_added * 6 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_03;

	for (int i = 1 + nb_segments_added * 6 / 16;
	     i < nb_segments_added * 10 / 16;
	     i += 20)
		ctx->track.segments[i].scene = scene_bench_n_billboard;

	int bg_cpt = 0;
	for (int i = nb_segments_added * 10 / 16 /*+ 20*/;
	     i < nb_segments_added * 15 / 16;
	     i += 3) {
		ctx->track.segments[i].scene =
			i % 2 == 0 ? scene_tunnel_bright : scene_tunnel_dark;
		if (bg_cpt == 0)
			ctx->track.segments[i + 1].scene = scene_buildine_01;
		if (bg_cpt == 7)
			ctx->track.segments[i + 1].scene = scene_buildine_03;
		bg_cpt++;
	}

	for (int i = 1 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_01;
	for (int i = 31 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_02;
	for (int i = 61 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_buildine_03;

	return 0;
}


static int track_build_squares(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_SQUARES; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_squares[i][SECTOR_PARAM_ENTER_LG],
			sector_squares[i][SECTOR_PARAM_HOLD_LG],
			sector_squares[i][SECTOR_PARAM_EXIT_LG],
			sector_squares[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_squares[i][SECTOR_PARAM_EXIT_CURVE],
			sector_squares[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_squares[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_squares[i][SECTOR_PARAM_ENTER_LG] +
				sector_squares[i][SECTOR_PARAM_HOLD_LG] +
				sector_squares[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_HALF;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_night;
	ctx->track.bg_color_ground = &cd_grassdark_dark;
	ctx->track.cd_road_bright = &cd_road_asphaltdark_dark;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_bright;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_white;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_grassdark_bright;
	ctx->track.cds[0].dark = &cd_grassdark_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	struct scene_seg_desc *scene_grave_gates =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_grave_gates->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_grave_gates->sprite[0],
			      &ctx->gfx.scene_grave_fence,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_grave_gates->sprite[1],
			      &ctx->gfx.scene_grave_fence,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	struct scene_seg_desc *scene_grave_lanes_a =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_grave_lanes_a->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	float grave_step = 2.5f;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 6; i++) {

		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i],
				      &ctx->gfx.scene_grave_01,
				      grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i + 1],
				      &ctx->gfx.scene_grave_02,
				      -grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i + 2],
				      &ctx->gfx.scene_grave_02,
				      grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i + 3],
				      &ctx->gfx.scene_grave_03,
				      -grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i + 4],
				      &ctx->gfx.scene_grave_03,
				      grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_a->sprite[6 * i + 5],
				      &ctx->gfx.scene_grave_01,
				      -grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_grave_lanes_b =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_grave_lanes_b->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 6; i++) {

		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i],
				      &ctx->gfx.scene_grave_02,
				      grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i + 1],
				      &ctx->gfx.scene_grave_03,
				      -grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i + 2],
				      &ctx->gfx.scene_grave_03,
				      grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i + 3],
				      &ctx->gfx.scene_grave_01,
				      -grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i + 4],
				      &ctx->gfx.scene_grave_01,
				      grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_b->sprite[6 * i + 5],
				      &ctx->gfx.scene_grave_02,
				      -grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_grave_lanes_c =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_grave_lanes_c->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 6; i++) {

		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i],
				      &ctx->gfx.scene_grave_03,
				      grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i + 1],
				      &ctx->gfx.scene_grave_01,
				      -grave_step * (float)(i * 3 + 1),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i + 2],
				      &ctx->gfx.scene_grave_01,
				      grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i + 3],
				      &ctx->gfx.scene_grave_02,
				      -grave_step * (float)(i * 3 + 2),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);

		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i + 4],
				      &ctx->gfx.scene_grave_02,
				      grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_grave_lanes_c->sprite[6 * i + 5],
				      &ctx->gfx.scene_grave_03,
				      -grave_step * (float)(i * 3 + 3),
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}


	struct scene_seg_desc *scene_stree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_stree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	float stree_step = 3.f;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_stree->sprite[2 * i],
				      &ctx->gfx.scene_tree_spooky,
				      stree_step * (float)(i) + 1.5f,
				      &hitbox_stree,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_stree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_spooky,
				      -stree_step * (float)(i)-1.5f,
				      &hitbox_stree,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *scene_vault_n_stree =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vault_n_stree->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	// float stree_step = 3.f;

	set_scene_sprite_desc(&scene_vault_n_stree->sprite[0],
			      &ctx->gfx.scene_vault,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_vault_n_stree->sprite[1],
			      &ctx->gfx.scene_vault,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {

		set_scene_sprite_desc(&scene_vault_n_stree->sprite[2 * i],
				      &ctx->gfx.scene_tree_spooky,
				      stree_step * (float)(i) + 1.5f,
				      &hitbox_stree,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vault_n_stree->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_spooky,
				      -stree_step * (float)(i)-1.5f,
				      &hitbox_stree,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	int seg_step = 10;
	for (int i = 1 + nb_segments_added * 0 / 16;
	     i < nb_segments_added * 3 / 16;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_grave_gates;

	seg_step = 30;
/*
	int j = 0;
	for (int i = 1 + nb_segments_added * 3 / 16;
	     i < nb_segments_added * 7 / 16;
	     i += seg_step) {
		if (j == 0)
			ctx->track.segments[i].scene = scene_grave_lanes_a;
		else if (j == 1)
			ctx->track.segments[i].scene = scene_grave_lanes_b;
		else if (j == 2)
			ctx->track.segments[i].scene = scene_grave_lanes_c;
		else
			j = -1;
		j++;
	}*/

	for (int i = 1 + nb_segments_added * 3 / 16;
	     i < nb_segments_added * 7 / 16;
	     i += seg_step) 
			ctx->track.segments[i].scene = scene_grave_lanes_a;
	for (int i = 1 + nb_segments_added * 3 / 16 + 10;
	     i < nb_segments_added * 7 / 16;
	     i += seg_step) 
			ctx->track.segments[i].scene = scene_grave_lanes_b;
	for (int i = 1 + nb_segments_added * 3 / 16 + 20;
	     i < nb_segments_added * 7 / 16;
	     i += seg_step) 
			ctx->track.segments[i].scene = scene_grave_lanes_c;

	for (int i = 1 + nb_segments_added * 7 / 16;
	     i < nb_segments_added * 11 / 16;
	     i += 40)
		ctx->track.segments[i].scene = scene_vault_n_stree;

	for (int i = 1 + nb_segments_added * 11 / 16;
	     i < nb_segments_added * 15 / 16;
	     i += 20)
		ctx->track.segments[i].scene = scene_stree;

	seg_step = 10;
	for (int i = 1 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_grave_gates;

	return 0;
}


static int track_build_curves(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_CURVES; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_curves[i][SECTOR_PARAM_ENTER_LG],
			sector_curves[i][SECTOR_PARAM_HOLD_LG],
			sector_curves[i][SECTOR_PARAM_EXIT_LG],
			sector_curves[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_curves[i][SECTOR_PARAM_EXIT_CURVE],
			sector_curves[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_curves[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_curves[i][SECTOR_PARAM_ENTER_LG] +
				sector_curves[i][SECTOR_PARAM_HOLD_LG] +
				sector_curves[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_HALF;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_desert_bright;
	ctx->track.cd_road_bright = &cd_road_asphaltdark_bright;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_white;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_desert_bright;
	ctx->track.cds[0].dark = &cd_desert_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	float rstep = 5.f;

	struct scene_seg_desc *scene_duneline_01 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_duneline_01->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 20; i++) {
		float position = (float)i * rstep + 4.f;
		set_scene_sprite_desc(&scene_duneline_01->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_duneline_01->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_duneline_02 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_duneline_02->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 20; i++) {
		float position = (float)i * rstep + 2.f;
		set_scene_sprite_desc(&scene_duneline_02->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_02,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_duneline_02->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_02,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_duneline_03 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_duneline_03->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 20; i++) {
		float position = (float)i * rstep + 3.f;
		set_scene_sprite_desc(&scene_duneline_03->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_03,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_duneline_03->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_03,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}


	struct scene_seg_desc *scene_ram_statues =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_ram_statues->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	set_scene_sprite_desc(&scene_ram_statues->sprite[0],
			      &ctx->gfx.scene_ram_statue,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);
	set_scene_sprite_desc(&scene_ram_statues->sprite[1],
			      &ctx->gfx.scene_ram_statue,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	for (int i = 1; i < 18; i++) {
		float position = (float)i * rstep + 4.f;
		set_scene_sprite_desc(&scene_ram_statues->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_ram_statues->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}


	struct scene_seg_desc *scene_egypt_columns =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_egypt_columns->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	set_scene_sprite_desc(&scene_egypt_columns->sprite[0],
			      &ctx->gfx.scene_egypt_column,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_egypt_columns->sprite[1],
			      &ctx->gfx.scene_egypt_column,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	for (int i = 1; i < 18; i++) {
		float position = (float)i * rstep + 4.f;
		set_scene_sprite_desc(&scene_egypt_columns->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_egypt_columns->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_egypt_temples =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_egypt_temples->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	set_scene_sprite_desc(&scene_egypt_temples->sprite[0],
			      &ctx->gfx.scene_egypt_temple,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_egypt_temples->sprite[1],
			      &ctx->gfx.scene_egypt_temple,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	for (int i = 1; i < 18; i++) {
		float position = (float)i * rstep + 4.f;
		set_scene_sprite_desc(&scene_egypt_temples->sprite[(2 * i)],
				      &ctx->gfx.scene_dune_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_egypt_temples->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_dune_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	int seg_step = 90;
	for (int i = 1 + nb_segments_added * 0 / 6;
	     i < nb_segments_added * 3 / 15;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_01;
	for (int i = 31 + nb_segments_added * 0 / 6;
	     i < nb_segments_added * 3 / 15;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_02;
	for (int i = 61 + nb_segments_added * 0 / 6;
	     i < nb_segments_added * 3 / 15;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_03;


	for (int i = 1 + nb_segments_added * 3 / 16;
	     i < nb_segments_added * 7 / 16;
	     i += 40)
		ctx->track.segments[i].scene = scene_ram_statues;

	for (int i = 1 + nb_segments_added * 7 / 16;
	     i < nb_segments_added * 11 / 16;
	     i += 40)
		ctx->track.segments[i].scene = scene_egypt_columns;

	for (int i = 1 + nb_segments_added * 11 / 16 + 40;
	     i < nb_segments_added * 15 / 16;
	     i += 80)
		ctx->track.segments[i].scene = scene_egypt_temples;

	for (int i = 1 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_01;
	for (int i = 31 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_02;
	for (int i = 61 + nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_duneline_03;

	return 0;
}


static int track_build_horns(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_HORNS; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_horns[i][SECTOR_PARAM_ENTER_LG],
			sector_horns[i][SECTOR_PARAM_HOLD_LG],
			sector_horns[i][SECTOR_PARAM_EXIT_LG],
			sector_horns[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_horns[i][SECTOR_PARAM_EXIT_CURVE],
			sector_horns[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_horns[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_horns[i][SECTOR_PARAM_ENTER_LG] +
				sector_horns[i][SECTOR_PARAM_HOLD_LG] +
				sector_horns[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_FULL;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_grass_bright;
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_grass_bright;
	ctx->track.cds[0].dark = &cd_grass_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	struct scene_seg_desc *garga_n_well =
		calloc(1, sizeof(struct scene_seg_desc));
	garga_n_well->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 2.f + 3.f * (float)i;
		set_scene_sprite_desc(&garga_n_well->sprite[2 * i],
				      i == 0 ? &ctx->gfx.scene_well
					     : &ctx->gfx.scene_grass,
				      position, // 2.f,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&garga_n_well->sprite[2 * i + 1],
				      i == 0 ? &ctx->gfx.scene_gargamel
					     : &ctx->gfx.scene_bush_flower,
				      -position, //-2.f,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *walls = calloc(1, sizeof(struct scene_seg_desc));
	walls->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	set_scene_sprite_desc(&walls->sprite[0],
			      &ctx->gfx.scene_wall,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&walls->sprite[1],
			      &ctx->gfx.scene_wall,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);


	struct scene_seg_desc *willow_forest_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	willow_forest_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 + 2 * i);
		set_scene_sprite_desc(&willow_forest_1->sprite[2 * i],
				      &ctx->gfx.scene_tree_willow,
				      position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&willow_forest_1->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_willow,
				      -position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *willow_forest_2 =
		calloc(1, sizeof(struct scene_seg_desc));
	willow_forest_2->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(2 + 2 * i);
		set_scene_sprite_desc(&willow_forest_2->sprite[2 * i],
				      &ctx->gfx.scene_tree_willow,
				      position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&willow_forest_2->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_willow,
				      -position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *towers =
		calloc(1, sizeof(struct scene_seg_desc));
	towers->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	set_scene_sprite_desc(&towers->sprite[0],
			      &ctx->gfx.scene_tower,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&towers->sprite[1],
			      &ctx->gfx.scene_tower,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	for (int i = 0; i < nb_segments_added * 3 / 16; i += 8)
		ctx->track.segments[i].scene = willow_forest_1;
	for (int i = 4; i < nb_segments_added * 3 / 16; i += 8)
		ctx->track.segments[i].scene = willow_forest_2;

	for (int i = nb_segments_added * 3 / 16; i < nb_segments_added * 7 / 16;
	     i += 40)
		ctx->track.segments[i].scene = garga_n_well;

	for (int i = nb_segments_added * 7 / 16;
	     i < nb_segments_added * 11 / 16;
	     i += 40)
		ctx->track.segments[i].scene = towers;

	for (int i = nb_segments_added * 11 / 16;
	     i < nb_segments_added * 15 / 16;
	     i += 8)
		ctx->track.segments[i].scene = walls;

	for (int i = nb_segments_added * 15 / 16; i < nb_segments_added; i += 8)
		ctx->track.segments[i].scene = willow_forest_1;
	for (int i = nb_segments_added * 15 / 16 + 4; i < nb_segments_added;
	     i += 8)
		ctx->track.segments[i].scene = willow_forest_2;

	return 0;
}


static int track_build_stone(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_STONE; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_stone[i][SECTOR_PARAM_ENTER_LG],
			sector_stone[i][SECTOR_PARAM_HOLD_LG],
			sector_stone[i][SECTOR_PARAM_EXIT_LG],
			sector_stone[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_stone[i][SECTOR_PARAM_EXIT_CURVE],
			sector_stone[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_stone[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_stone[i][SECTOR_PARAM_ENTER_LG] +
				sector_stone[i][SECTOR_PARAM_HOLD_LG] +
				sector_stone[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_NONE;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_stone_bright;
	ctx->track.cd_road_bright = &cd_road_stone_bright;
	ctx->track.cd_road_dark = &cd_road_stone_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_stone_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_stone_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_black;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_stone_bright;
	ctx->track.cds[0].dark = &cd_stone_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	struct scene_seg_desc *scene_delphi =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_delphi->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_delphi->sprite[0],
			      &ctx->gfx.scene_delphi,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_delphi->sprite[1],
			      &ctx->gfx.scene_delphi,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);

	struct scene_seg_desc *scene_temple =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_temple->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_temple->sprite[0],
			      &ctx->gfx.scene_temple,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_temple->sprite[1],
			      &ctx->gfx.scene_temple,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);


	struct scene_seg_desc *scene_columns_a =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_columns_a->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_columns_a->sprite[0],
			      &ctx->gfx.scene_column_01,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_columns_a->sprite[1],
			      &ctx->gfx.scene_column_01,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);


	float rstep = 3.f;

	struct scene_seg_desc *scene_columns_01 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_columns_01->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 1.5f;
		set_scene_sprite_desc(&scene_columns_01->sprite[(2 * i)],
				      &ctx->gfx.scene_column_02,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_columns_01->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_column_02,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_columns_02 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_columns_02->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 3.f;
		set_scene_sprite_desc(&scene_columns_02->sprite[(2 * i)],
				      &ctx->gfx.scene_column_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_columns_02->sprite[(2 * i) + 0],
				      &ctx->gfx.scene_column_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_columns_03 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_columns_03->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 4.5f;
		set_scene_sprite_desc(&scene_columns_03->sprite[(2 * i)],
				      &ctx->gfx.scene_column_03,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_columns_03->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_column_03,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	for (int i = 0; i < nb_segments_added * 3 / 16; i += 60)
		ctx->track.segments[i].scene = scene_delphi;

	for (int i = nb_segments_added * 3 / 16; i < nb_segments_added * 7 / 16;
	     i += 20)
		ctx->track.segments[i].scene = scene_columns_a;

	for (int i = nb_segments_added * 7 / 16;
	     i < nb_segments_added * /*7*/ 11 / 16;
	     i += 80)
		ctx->track.segments[i].scene = scene_temple;

	for (int i = nb_segments_added * 11 / 16;
	     i < nb_segments_added * 15 / 16;
	     i += 60)
		ctx->track.segments[i].scene = scene_columns_01;
	for (int i = nb_segments_added * 11 / 16 + 20;
	     i < nb_segments_added * 15 / 16;
	     i += 60)
		ctx->track.segments[i].scene = scene_columns_02;
	for (int i = nb_segments_added * 11 / 16 + 40;
	     i < nb_segments_added * 15 / 16;
	     i += 60)
		ctx->track.segments[i].scene = scene_columns_03;

	for (int i = nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += 40)
		ctx->track.segments[i].scene = scene_delphi;

	return 0;
}

static int track_build_frost(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_FROST; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_frost[i][SECTOR_PARAM_ENTER_LG],
			sector_frost[i][SECTOR_PARAM_HOLD_LG],
			sector_frost[i][SECTOR_PARAM_EXIT_LG],
			sector_frost[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_frost[i][SECTOR_PARAM_EXIT_CURVE],
			sector_frost[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_frost[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_frost[i][SECTOR_PARAM_ENTER_LG] +
				sector_frost[i][SECTOR_PARAM_HOLD_LG] +
				sector_frost[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_NONE;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_ice_bright;
	ctx->track.cd_road_bright = &cd_road_ice_bright;
	ctx->track.cd_road_dark = &cd_road_ice_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_ice_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_ice_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_ice_bright;
	ctx->track.cds[0].dark = &cd_ice_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	struct scene_seg_desc *scene_igloo =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_igloo->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_inn =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_inn->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_pine =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_pine->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_snowmen_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_snowmen_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	set_scene_sprite_desc(&scene_igloo->sprite[0],
			      &ctx->gfx.scene_igloo,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_igloo->sprite[1],
			      &ctx->gfx.scene_igloo,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);


	set_scene_sprite_desc(&scene_inn->sprite[0],
			      &ctx->gfx.scene_lantern,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_inn->sprite[1],
			      &ctx->gfx.scene_snow_inn,
			      -3.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_inn->sprite[2],
			      &ctx->gfx.scene_bench,
			      2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_inn->sprite[3],
			      &ctx->gfx.scene_lantern,
			      3.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);

	for (int i = 1; i < (MAX_SCENE_SPRITE_PER_SEG - 4) / 2; i++) {
		float position = (float)i * 1.5f;
		set_scene_sprite_desc(&scene_inn->sprite[2 * i + 4],
				      &ctx->gfx.scene_tree_pine_snow,
				      position + 3.5f,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_inn->sprite[2 * i + 5],
				      &ctx->gfx.scene_tree_pine_snow,
				      -position - 5.f,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)i * 1.5f;
		set_scene_sprite_desc(&scene_pine->sprite[2 * i],
				      &ctx->gfx.scene_tree_pine_snow,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_pine->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_pine_snow,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)i * 2.f;
		set_scene_sprite_desc(&scene_snowmen_1->sprite[2 * i],
				      i == 1 ? &ctx->gfx.scene_snowman
					     : &ctx->gfx.scene_tree_dead_snow,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_snowmen_1->sprite[2 * i + 1],
				      i == 1 ? &ctx->gfx.scene_snowman
					     : &ctx->gfx.scene_tree_dead_snow,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	for (int i = 0; i < nb_segments_added * 2 / 16; i += 50)
		ctx->track.segments[i].scene = scene_inn;

	for (int i = nb_segments_added * 2 / 16; i < nb_segments_added * 6 / 16;
	     i += 15)
		ctx->track.segments[i].scene = scene_pine;

	for (int i = nb_segments_added * 6 / 16;
	     i < nb_segments_added * 10 / 16;
	     i += 15)
		ctx->track.segments[i].scene = scene_snowmen_1;

	for (int i = nb_segments_added * 10 / 16;
	     i < nb_segments_added * 14 / 16;
	     i += 30)
		ctx->track.segments[i].scene = scene_igloo;

	for (int i = nb_segments_added * 14 / 16; i < nb_segments_added;
	     i += 50)
		ctx->track.segments[i].scene = scene_inn;

	return 0;
}


static int track_build_fork(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_FORK; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_fork[i][SECTOR_PARAM_ENTER_LG],
			sector_fork[i][SECTOR_PARAM_HOLD_LG],
			sector_fork[i][SECTOR_PARAM_EXIT_LG],
			sector_fork[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_fork[i][SECTOR_PARAM_EXIT_CURVE],
			sector_fork[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_fork[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_fork[i][SECTOR_PARAM_ENTER_LG] +
				sector_fork[i][SECTOR_PARAM_HOLD_LG] +
				sector_fork[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	ctx->track.lane_type = LANE_TYPE_NONE;

	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_mud_bright;
	ctx->track.cd_road_bright = &cd_road_mud_bright;
	ctx->track.cd_road_dark = &cd_road_mud_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_mud_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_mud_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_mud_bright;
	ctx->track.cds[0].dark = &cd_mud_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	float rstep = 3.f;

	struct scene_seg_desc *scene_rockline_01 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rockline_01->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 1.5f;
		set_scene_sprite_desc(&scene_rockline_01->sprite[(2 * i)],
				      &ctx->gfx.scene_rock_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rockline_01->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_rock_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_rockline_02 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rockline_02->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 3.f;
		set_scene_sprite_desc(&scene_rockline_02->sprite[(2 * i)],
				      &ctx->gfx.scene_rock_02,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rockline_02->sprite[(2 * i) + 0],
				      &ctx->gfx.scene_rock_02,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_rockline_03 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rockline_03->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 4.5f;
		set_scene_sprite_desc(&scene_rockline_03->sprite[(2 * i)],
				      &ctx->gfx.scene_rock_03,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rockline_03->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_rock_03,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_rockline_04 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rockline_04->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 2.f;
		set_scene_sprite_desc(&scene_rockline_04->sprite[(2 * i)],
				      &ctx->gfx.scene_rock_04,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rockline_04->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_rock_04,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_rockline_05 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_rockline_05->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * rstep + 4.f;
		set_scene_sprite_desc(&scene_rockline_05->sprite[(2 * i)],
				      &ctx->gfx.scene_rock_05,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_rockline_05->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_rock_05,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}


	float vstep = 5.f;
	struct scene_seg_desc *scene_vegline_01 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_01->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 2.f;
		set_scene_sprite_desc(&scene_vegline_01->sprite[(2 * i)],
				      &ctx->gfx.scene_cactus_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_01->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_cactus_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_vegline_02 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_02->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 4.f;
		set_scene_sprite_desc(&scene_vegline_02->sprite[(2 * i)],
				      &ctx->gfx.scene_desert_grass_01,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_02->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_desert_grass_01,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_vegline_03 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_03->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 3.f;
		set_scene_sprite_desc(&scene_vegline_03->sprite[(2 * i)],
				      &ctx->gfx.scene_cactus_02,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_03->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_cactus_02,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_vegline_04 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_04->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 5.f;
		set_scene_sprite_desc(&scene_vegline_04->sprite[(2 * i)],
				      &ctx->gfx.scene_cactus_03,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_04->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_cactus_03,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_vegline_05 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_05->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 6.f;
		set_scene_sprite_desc(&scene_vegline_05->sprite[(2 * i)],
				      &ctx->gfx.scene_desert_grass_02,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_05->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_desert_grass_02,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	struct scene_seg_desc *scene_vegline_06 =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_vegline_06->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < 10; i++) {
		float position = (float)i * vstep + 7.f;
		set_scene_sprite_desc(&scene_vegline_06->sprite[(2 * i)],
				      &ctx->gfx.scene_cactus_04,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_vegline_06->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_cactus_04,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}


	struct scene_seg_desc *scene_bigrocks =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_bigrocks->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	for (int i = 0; i < /*2*/ MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(i + 1) * 1.5f;
		set_scene_sprite_desc(&scene_bigrocks->sprite[(2 * i)],
				      &ctx->gfx.scene_big_rock,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&scene_bigrocks->sprite[(2 * i) + 1],
				      &ctx->gfx.scene_big_rock,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL /*SDL_FLIP_NONE*/);
	}

	int seg_step = 100;
	for (int i = 1; i < nb_segments_added * 1 / 6; i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_01;
	for (int i = 21; i < nb_segments_added * 1 / 6; i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_02;
	for (int i = 41; i < nb_segments_added * 1 / 6; i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_03;
	for (int i = 61; i < nb_segments_added * 1 / 6; i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_04;
	for (int i = 81; i < nb_segments_added * 1 / 6; i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_05;


	for (int i = nb_segments_added * 1 / 6; i < nb_segments_added * 3 / 6;
	     i += 10)
		ctx->track.segments[i].scene = scene_bigrocks;

	seg_step = 120;
	for (int i = 1 + nb_segments_added * 3 / 6;
	     i < nb_segments_added * 5 / 6;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_01;
	for (int i = 21 + nb_segments_added * 3 / 6;
	     i < nb_segments_added * 5 / 6;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_02;
	for (int i = 41 + nb_segments_added * 3 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_03;
	for (int i = 61 + nb_segments_added * 3 / 6;
	     i < nb_segments_added * 5 / 6;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_04;
	for (int i = 81 + nb_segments_added * 3 / 6;
	     i < nb_segments_added * 5 / 6;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_05;
	for (int i = 101 + nb_segments_added * 3 / 6;
	     i < nb_segments_added * 5 / 6;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_vegline_06;

	seg_step = 100;
	for (int i = 1 + nb_segments_added * 5 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_01;
	for (int i = 21 + nb_segments_added * 5 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_02;
	for (int i = 41 + nb_segments_added * 5 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_03;
	for (int i = 61 + nb_segments_added * 5 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_04;
	for (int i = 81 + nb_segments_added * 5 / 6; i < nb_segments_added;
	     i += seg_step)
		ctx->track.segments[i].scene = scene_rockline_05;

	return 0;
}


static int track_build_speedway(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_SPEEDWAY; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_speedway[i][SECTOR_PARAM_ENTER_LG],
			sector_speedway[i][SECTOR_PARAM_HOLD_LG],
			sector_speedway[i][SECTOR_PARAM_EXIT_LG],
			sector_speedway[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_speedway[i][SECTOR_PARAM_EXIT_CURVE],
			sector_speedway[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_speedway[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_speedway[i][SECTOR_PARAM_ENTER_LG] +
				sector_speedway[i][SECTOR_PARAM_HOLD_LG] +
				sector_speedway[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);


	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_water_bright;
	ctx->track.cd_road_bright = &cd_road_asphaltdark_bright;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 4;
	ctx->track.cds[0].bright = &cd_water_bright;
	ctx->track.cds[0].dark = &cd_water_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_RIGHT;

	ctx->track.cds[1].bright = &cd_foam_bright;
	ctx->track.cds[1].dark = &cd_foam_dark;
	ctx->track.cds[1].num = 300;
	ctx->track.cds[1].den = 100;
	ctx->track.cds[1].side = CDS_RIGHT;

	ctx->track.cds[2].bright = &cd_sand_bright;
	ctx->track.cds[2].dark = &cd_sand_dark;
	ctx->track.cds[2].num = 250;
	ctx->track.cds[2].den = 100;
	ctx->track.cds[2].side = CDS_RIGHT;

	ctx->track.cds[3].bright = &cd_sand_bright;
	ctx->track.cds[3].dark = &cd_sand_dark;
	ctx->track.cds[3].num = 250;
	ctx->track.cds[3].den = 100;
	ctx->track.cds[3].side = CDS_FULL_LEFT;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];


	ctx->track.lane_type = LANE_TYPE_HALF;


	struct scene_seg_desc *scene_maois =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_maois->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_palms =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_palms->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_speedboat =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_speedboat->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_cabin =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_cabin->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;

	struct scene_seg_desc *scene_buoy =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_buoy->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;


	set_scene_sprite_desc(&scene_maois->sprite[0],
			      &ctx->gfx.scene_maoi,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);

	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)i * 1.5f;
		set_scene_sprite_desc(&scene_maois->sprite[i],
				      &ctx->gfx.scene_maoi,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}


	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(i + 1) * 1.5f;
		set_scene_sprite_desc(&scene_palms->sprite[i],
				      &ctx->gfx.scene_tree_palm,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	set_scene_sprite_desc(&scene_buoy->sprite[0],
			      &ctx->gfx.scene_buoy,
			      5.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);


	set_scene_sprite_desc(&scene_speedboat->sprite[0],
			      &ctx->gfx.scene_boat_speed,
			      7.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	set_scene_sprite_desc(&scene_speedboat->sprite[1],
			      &ctx->gfx.scene_beach_umbrella,
			      1.5f,
			      NULL,
			      1,
			      SDL_FLIP_HORIZONTAL);
	set_scene_sprite_desc(&scene_speedboat->sprite[2],
			      &ctx->gfx.scene_billboard_beach,
			      -1.5f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	for (int i = 3; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(i + 1) * 1.5f;
		set_scene_sprite_desc(&scene_speedboat->sprite[i],
				      &ctx->gfx.scene_tree_palm,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	set_scene_sprite_desc(&scene_cabin->sprite[0],
			      &ctx->gfx.scene_beach_cabin,
			      -2.f,
			      NULL,
			      1,
			      SDL_FLIP_NONE);
	for (int i = 1; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(i + 1) * 1.5f;
		set_scene_sprite_desc(&scene_cabin->sprite[i],
				      &ctx->gfx.scene_tree_palm,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
	}

	for (int i = 0; i < nb_segments_added * 3 / 16; i += 40)
		ctx->track.segments[i].scene = scene_speedboat;

	for (int i = nb_segments_added * 3 / 16; i < nb_segments_added * 7 / 16;
	     i += 20)
		ctx->track.segments[i].scene = scene_maois;

	for (int i = nb_segments_added * 7 / 16;
	     i < nb_segments_added * 11 / 16;
	     i += 12)
		ctx->track.segments[i].scene = scene_palms;
	for (int i = (nb_segments_added * 7 / 16) + 6;
	     i < nb_segments_added * 11 / 16;
	     i += 24)
		ctx->track.segments[i].scene = scene_buoy;

	for (int i = nb_segments_added * 11 / 16;
	     i < nb_segments_added * 15 / 16;
	     i += 20)
		ctx->track.segments[i].scene = scene_cabin;

	for (int i = nb_segments_added * 15 / 16; i < nb_segments_added;
	     i += 40)
		ctx->track.segments[i].scene = scene_speedboat;

	return 0;
}


static int track_build_dijon(struct game_context *ctx)
{
	int nb_segments_added = 0;

	// Build the track segments
	for (int i = 0; i < NB_SECTOR_DIJON; i++) {
		nb_segments_added += road_add_sector(
			ctx->track.segments,
			nb_segments_added,
			sector_dijon[i][SECTOR_PARAM_ENTER_LG],
			sector_dijon[i][SECTOR_PARAM_HOLD_LG],
			sector_dijon[i][SECTOR_PARAM_EXIT_LG],
			sector_dijon[i][SECTOR_PARAM_EXIT_Y],
			(float)sector_dijon[i][SECTOR_PARAM_EXIT_CURVE],
			sector_dijon[i][SECTOR_PARAM_NB_LANE_ENTER],
			sector_dijon[i][SECTOR_PARAM_NB_LANE_EXIT]);

		SDL_Log("[%s] segments: total = %d, sector[%d] = %d\n",
			__func__,
			nb_segments_added,
			i,
			sector_dijon[i][SECTOR_PARAM_ENTER_LG] +
				sector_dijon[i][SECTOR_PARAM_HOLD_LG] +
				sector_dijon[i][SECTOR_PARAM_EXIT_LG]);
	}

	ctx->track.track_length = ROAD_SEGMENT_LENGTH * ctx->track.nb_segments;

	SDL_Log("[%s] nb_segments_added = %d\n", __func__, nb_segments_added);

	/////////////////////////////////////////////////////////////////////

	/*
		struct scene_seg_desc *start_lane =
			calloc(1, sizeof(struct scene_seg_desc));
		start_lane->nb_sprites = 1;
		float position = -0.9000001f;
		set_scene_sprite_desc(&start_lane->sprite[0],
				      &ctx->gfx.scene_start_lane,
				      position,
				      NULL,
				      1);
	*/

	struct scene_seg_desc *barn_n_well =
		calloc(1, sizeof(struct scene_seg_desc));
	barn_n_well->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&barn_n_well->sprite[2 * i],
				      i == 0 ? &ctx->gfx.scene_barn
					     : &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&barn_n_well->sprite[2 * i + 1],
				      i == 0 ? &ctx->gfx.scene_well
					     : &ctx->gfx.scene_bush_flower,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *windmill_n_grass =
		calloc(1, sizeof(struct scene_seg_desc));
	windmill_n_grass->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&windmill_n_grass->sprite[2 * i],
				      i == 1 ? &ctx->gfx.scene_windmill
					     : &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&windmill_n_grass->sprite[2 * i + 1],
				      i == 1 ? &ctx->gfx.scene_windmill
					     : &ctx->gfx.scene_grass,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *fence_n_bush =
		calloc(1, sizeof(struct scene_seg_desc));
	fence_n_bush->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&fence_n_bush->sprite[2 * i],
				      i < 1 ? &ctx->gfx.scene_fence
					    : &ctx->gfx.scene_bush_flower,
				      position,
				      NULL,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&fence_n_bush->sprite[2 * i + 1],
				      i < 1 ? &ctx->gfx.scene_fence
					    : &ctx->gfx.scene_bush_flower,
				      -position,
				      NULL,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *grass = calloc(1, sizeof(struct scene_seg_desc));
	grass->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = 1.5f + 1.25f * (float)i;
		set_scene_sprite_desc(&grass->sprite[2 * i],
				      &ctx->gfx.scene_grass,
				      position,
				      NULL,
				      0,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&grass->sprite[2 * i + 1],
				      &ctx->gfx.scene_grass,
				      -position,
				      NULL,
				      0,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *oak_forest_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	oak_forest_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 + 2 * i);
		set_scene_sprite_desc(&oak_forest_1->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&oak_forest_1->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *oak_forest_2 =
		calloc(1, sizeof(struct scene_seg_desc));
	oak_forest_2->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(2 + 2 * i);
		set_scene_sprite_desc(&oak_forest_2->sprite[2 * i],
				      &ctx->gfx.scene_tree_oak,
				      position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_NONE);
		set_scene_sprite_desc(&oak_forest_2->sprite[2 * i + 1],
				      &ctx->gfx.scene_tree_oak,
				      -position,
				      &hitbox_oak,
				      1,
				      SDL_FLIP_HORIZONTAL);
	}

	// randomize different bushes set
	struct scene_seg_desc *bushes_rnd_1 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_1->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_1->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0,
			SDL_FLIP_NONE);
		set_scene_sprite_desc(
			&bushes_rnd_1->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0,
			SDL_FLIP_HORIZONTAL);
	}
	struct scene_seg_desc *bushes_rnd_2 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_2->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_2->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0,
			SDL_FLIP_NONE);
		set_scene_sprite_desc(
			&bushes_rnd_2->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0,
			SDL_FLIP_HORIZONTAL);
	}
	struct scene_seg_desc *bushes_rnd_3 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_3->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_3->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0,
			SDL_FLIP_NONE);
		set_scene_sprite_desc(
			&bushes_rnd_3->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0,
			SDL_FLIP_HORIZONTAL);
	}
	struct scene_seg_desc *bushes_rnd_4 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_4->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_4->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0,
			SDL_FLIP_NONE);
		set_scene_sprite_desc(
			&bushes_rnd_4->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0,
			SDL_FLIP_HORIZONTAL);
	}
	struct scene_seg_desc *bushes_rnd_5 =
		calloc(1, sizeof(struct scene_seg_desc));
	bushes_rnd_5->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	for (int i = 0; i < MAX_SCENE_SPRITE_PER_SEG / 2; i++) {
		float position = (float)(1 * i) + 1.5f;
		set_scene_sprite_desc(
			&bushes_rnd_5->sprite[2 * i],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			position,
			NULL,
			0,
			SDL_FLIP_NONE);
		set_scene_sprite_desc(
			&bushes_rnd_5->sprite[2 * i + 1],
			&ctx->gfx.scene_bushes[rand() % NB_SPRITE_BUSH],
			-position,
			NULL,
			0,
			SDL_FLIP_HORIZONTAL);
	}

	struct scene_seg_desc *bushes_rnd_tab[5] = {bushes_rnd_1,
						    bushes_rnd_2,
						    bushes_rnd_3,
						    bushes_rnd_4,
						    bushes_rnd_5};

	/////////////////////////////////////////////////////////////////////

	for (int i = 0; i < nb_segments_added / 10; i += 5)
		// ctx->track.segments[i].scene = grass;
		ctx->track.segments[i].scene = bushes_rnd_tab[rand() % 5];

	for (int i = nb_segments_added / 10; i < nb_segments_added * 3 / 10;
	     i += 8)
		ctx->track.segments[i].scene = oak_forest_1;
	for (int i = nb_segments_added / 10 + 4; i < nb_segments_added * 3 / 10;
	     i += 8)
		ctx->track.segments[i].scene = oak_forest_2;

	for (int i = nb_segments_added * 3 / 10; i < nb_segments_added * 5 / 10;
	     i += 32)
		ctx->track.segments[i].scene = barn_n_well;

	for (int i = nb_segments_added * 5 / 10; i < nb_segments_added * 7 / 10;
	     i += 5)
		ctx->track.segments[i].scene = fence_n_bush;

	for (int i = nb_segments_added * 7 / 10; i < nb_segments_added * 9 / 10;
	     i += 16)
		ctx->track.segments[i].scene = windmill_n_grass;

	for (int i = nb_segments_added * 9 / 10; i < nb_segments_added; i += 4)
		// ctx->track.segments[i].scene = bushes_rnd_1;
		ctx->track.segments[i].scene = bushes_rnd_tab[rand() % 5];
	// ctx->track.segments[i].scene = grass;


	// ctx->track.segments[0].scene = start_lane;


	/////////////////////////////////////////////
	// set color of segment outside of the road
	ctx->track.bg_color_sky = &cd_sky_blue;
	ctx->track.bg_color_ground = &cd_grass_bright;
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
	ctx->track.cd_rumble_bright = &cd_rumble_bright;
	ctx->track.cd_rumble_dark = &cd_rumble_dark;
	ctx->track.cd_lane = &cd_lane_yellow;
	ctx->track.cd_start_line = &cd_lane_white;
	ctx->track.nb_cds = 1;
	ctx->track.cds[0].bright = &cd_grass_bright;
	ctx->track.cds[0].dark = &cd_grass_dark;
	ctx->track.cds[0].num = 0;
	ctx->track.cds[0].den = 0;
	ctx->track.cds[0].side = CDS_FULL_BOTH;

	for (int i = 0; i < nb_segments_added; i++)
		ctx->track.segments[i].cds = &ctx->track.cds[0];

	ctx->track.lane_type = LANE_TYPE_HALF;

	return 0;
}

int track_build(struct game_context *ctx)
{

	int tid = ctx->track.track_selected;
	ctx->track.nb_segments = track_build_tab[tid].nb_segment;

	///////////////////////////////////
	// TODO: put this in a function elsewhere
	int player_lane = NB_AI_CARS % ctx->track.lanes;
	ctx->pcar.player_x = ai_lane_to_posx(player_lane, ctx->track.lanes);
	ctx->pcar.player_segment =
		ctx->track.nb_segments -
		(NB_AI_CARS / ctx->track.lanes) * AI_SEGMENTS_SPACING - 6;
	ctx->pcar.player_segment_prev = ctx->pcar.player_segment;
	ctx->pcar.position = ctx->pcar.player_segment * ROAD_SEGMENT_LENGTH;
	ctx->pcar.player_distance_ran =
		(ctx->pcar.player_segment - ctx->track.nb_segments) *
			ROAD_SEGMENT_LENGTH -
		1;

	SDL_Log("PLAYER player_distance_ran = %d\n",
		ctx->pcar.player_distance_ran);

	///////////////////////////////////

	ctx->track.segments = calloc((size_t)ctx->track.nb_segments,
				     sizeof(*ctx->track.segments));
	if (!ctx->track.segments) {
		SDL_Log("[%s] ERROR: calloc failed\n", __func__);
		return -ENOMEM;
	}

	switch (tid) {
	case TRACK_DIJON:
		track_build_dijon(ctx);
		break;
	case TRACK_SPEEDWAY:
		track_build_speedway(ctx);
		break;
	case TRACK_FORK:
		track_build_fork(ctx);
		break;
	case TRACK_FROST:
		track_build_frost(ctx);
		break;
	case TRACK_STONE:
		track_build_stone(ctx);
		break;
	case TRACK_HORNS:
		track_build_horns(ctx);
		break;
	case TRACK_CURVES:
		track_build_curves(ctx);
		break;
	case TRACK_SQUARES:
		track_build_squares(ctx);
		break;
	case TRACK_WHALE:
		track_build_whale(ctx);
		break;
	case TRACK_CARMONA:
		track_build_carmona(ctx);
		break;
	}

	return 0;
}

int track_unload(struct game_context *ctx)
{

	struct scene_seg_desc *scene_desc_freed[50] = {};
	int idx = 0;


	for (int i = 0; i < ctx->track.nb_segments; i++) {
		int desc_found = 0;
		for (int j = 0; j < 50; j++) {
			if (ctx->track.segments[i].scene ==
			    scene_desc_freed[j]) {
				desc_found = 1;
				break;
			}
		}

		if (!desc_found) {
			scene_desc_freed[idx] = ctx->track.segments[i].scene;
			idx++;
			free(ctx->track.segments[i].scene);
		}
	}

	free(ctx->track.segments);
	ctx->track.segments = NULL;

	return 0;
}
