#include "track.h"
#include "main.h"


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
	{.nb_sector = NB_SECTOR_STONE, .nb_segment = NB_SEGMENT_STONE},
	{.nb_sector = NB_SECTOR_CURVES, .nb_segment = NB_SEGMENT_CURVES},
	{.nb_sector = NB_SECTOR_HORNS, .nb_segment = NB_SEGMENT_HORNS},
	{.nb_sector = NB_SECTOR_SQUARES, .nb_segment = NB_SEGMENT_SQUARES},
	{.nb_sector = NB_SECTOR_WHALE, .nb_segment = NB_SEGMENT_WHALE},
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
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_NONE, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_DOWN_MEDIUM, CURVE_L_EASY, 2, 2},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_UP_HIGH, CURVE_NONE, 2, 3},
	{LG_SHORT, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_horns[NB_SECTOR_HORNS][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_HARD, 4, 4},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_HARD, 4, 4},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 4, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_HARD, 4, 4},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_HARD, 4, 4},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 4, 3}};


static int sector_curves[NB_SECTOR_CURVES][NB_SECTOR_PARAM] = {
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_R_MEDIUM, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_squares[NB_SECTOR_SQUARES][NB_SECTOR_PARAM] = {

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},


	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_SHORT, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},


	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	//{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_whale[NB_SECTOR_WHALE][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 2, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_HARD, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_MEDIUM, 3, 2},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 2, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_MEDIUM, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 2, 2},

	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
};


static int sector_carmona[NB_SECTOR_CARMONA][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 4},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 4, 4},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 4, 4},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_HARD, 4, 4},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 4, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_MEDIUM, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_L_EASY, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 2},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 2, 2},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 2, 2},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_EASY, 2, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_LONG, LG_LONG, LG_LONG, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_EASY, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_SHORT, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},

	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},


};


static SDL_Rect hitbox_oak = {.x = 262, .y = 0, .w = 240, .h = 711};
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
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
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
	ctx->track.cd_road_bright = &cd_road_asphaltdark_bright;
	ctx->track.cd_road_dark = &cd_road_asphaltdark_dark;
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


	struct scene_seg_desc *scene_tunnel_bright =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_tunnel_bright->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	scene_tunnel_bright->type = SCENE_SPRITE_CENTERED;
	set_scene_sprite_desc(&scene_tunnel_bright->sprite[0],
			      &ctx->gfx.scene_tunnel_a_bright,
			      1.5f,
			      &hitbox_tunnel_a,
			      1,
			      SDL_FLIP_NONE);

	struct scene_seg_desc *scene_tunnel_dark =
		calloc(1, sizeof(struct scene_seg_desc));
	scene_tunnel_dark->nb_sprites = MAX_SCENE_SPRITE_PER_SEG;
	scene_tunnel_dark->type = SCENE_SPRITE_CENTERED;
	set_scene_sprite_desc(&scene_tunnel_dark->sprite[0],
			      &ctx->gfx.scene_tunnel_a_dark,
			      1.5f,
			      &hitbox_tunnel_a,
			      1,
			      SDL_FLIP_NONE);

	for (int i = nb_segments_added * 0 / 16 + 20;
	     i < nb_segments_added * 15 / 16;
	     i += 3) {
		ctx->track.segments[i].scene =
			i % 2 == 0 ? scene_tunnel_bright : scene_tunnel_dark;
	}


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
	ctx->track.cd_road_bright = &cd_road_asphalt_bright;
	ctx->track.cd_road_dark = &cd_road_asphalt_dark;
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
