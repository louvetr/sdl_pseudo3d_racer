#ifndef TRACK_H
#define TRACK_H

//#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <SDL2/SDL_stdinc.h>

#define NB_SECTOR_PARAM 7
#define SECTOR_PARAM_ENTER_LG 0
#define SECTOR_PARAM_HOLD_LG 1
#define SECTOR_PARAM_EXIT_LG 2
#define SECTOR_PARAM_EXIT_Y 3
#define SECTOR_PARAM_EXIT_CURVE 4
#define SECTOR_PARAM_NB_LANE_ENTER 5
#define SECTOR_PARAM_NB_LANE_EXIT 6

#define NB_SECTOR_DIJON 16
#define NB_SEGMENT_DIJON 2570

#define NB_SECTOR_SPEEDWAY 9
#define NB_SEGMENT_SPEEDWAY 2400

#define NB_SECTOR_FORK 11
#define NB_SEGMENT_FORK 2700

#define NB_SECTOR_FROST 25
//#define NB_SEGMENT_FROST 3050
#define NB_SEGMENT_FROST 3200

#define NB_SECTOR_STONE 15
#define NB_SEGMENT_STONE 2525

#define NB_SECTOR_HORNS 17
#define NB_SEGMENT_HORNS 2850

#define NB_SECTOR_CURVES 14
#define NB_SEGMENT_CURVES 2850

#define NB_SECTOR_SQUARES 41
#define NB_SEGMENT_SQUARES 3450

#define NB_SECTOR_WHALE 20
#define NB_SEGMENT_WHALE 3080

#define NB_SECTOR_CARMONA 23
#define NB_SEGMENT_CARMONA 3300

#define NB_CDS 6

typedef uint8_t Uint8;

enum track_selection {
	TRACK_DIJON = 0,
	TRACK_SPEEDWAY,
	TRACK_FORK,
	TRACK_FROST,
	TRACK_STONE,
	TRACK_HORNS,
	TRACK_CURVES,
	TRACK_SQUARES,
	TRACK_WHALE,
	TRACK_CARMONA,
	TRACK_LAST
};

enum track_mask {
	TRACK_MASK_DIJON = (1u << 0),
	TRACK_MASK_SPEEDWAY = (1u << 1),
	TRACK_MASK_FORK = (1u << 2),
	TRACK_MASK_FROST = (1u << 3),
	TRACK_MASK_STONE = (1u << 4),
	TRACK_MASK_HORNS = (1u << 5),
	TRACK_MASK_CURVES = (1u << 6),
	TRACK_MASK_SQUARES = (1u << 7),
	TRACK_MASK_WHALE = (1u << 8),
	TRACK_MASK_CARMONA = (1u << 9),
};

struct track_build_info {
	int nb_sector;
	int nb_segment;
};

enum track_lane_type {
	LANE_TYPE_NONE = 0,
	LANE_TYPE_HALF,
	LANE_TYPE_FULL
};

struct color_desc {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};


// turn curve level and direction
enum road_curve {
	CURVE_L_HARD = -6,
	CURVE_L_MEDIUM = -4,
	CURVE_L_EASY = -2,
	CURVE_NONE = 0,
	CURVE_R_EASY = 2,
	CURVE_R_MEDIUM = 4,
	CURVE_R_HARD = 6
};

// 'altitude' of the road
enum road_hill {
	HILL_DOWN_HIGH = -60,
	HILL_DOWN_MEDIUM = -40,
	HILL_DOWN_LOW = -20,
	HILL_DOWN_SLIGHT = -10,
	HILL_NONE = 0,
	HILL_UP_SLIGHT = 10,
	HILL_UP_LOW = 20,
	HILL_UP_MEDIUM = 40,
	HILL_UP_HIGH = 60
};

// length in segment of a road sector
enum road_sector_length {
	LG_VSHORT = 10,
	LG_SHORT = 25,
	LG_MEDIUM = 50,
	LG_LONG = 100
};

enum color_desc_scene_side {
	CDS_LEFT = -1,
	CDS_BOTH = 0,
	CDS_RIGHT = 1,
	CDS_FULL_LEFT,
	CDS_FULL_RIGHT,
	CDS_FULL_BOTH,
};

struct color_desc_scene{
	struct color_desc *bright;
	struct color_desc *dark;
	int num;
	int den;
	enum color_desc_scene_side side;
};

struct track_info {

	enum track_selection track_selected;
	enum track_lane_type lane_type;
	struct color_desc lane_color;

    // number of road segments of the track
    int nb_segments;
	// array of road segments
	struct road_segment *segments; // array of road segments
	// number of segments per red/white rumble strip
	int rumble_length;
	// z length of entire track (computed)
	int track_length;
	// number of lanes
	int lanes;
	

	// color info
	struct color_desc *cd_road_bright;
	struct color_desc *cd_road_dark;
	struct color_desc *cd_rumble_bright;
	struct color_desc *cd_rumble_dark;
	struct color_desc *cd_lane;
	struct color_desc *cd_start_line;

	int nb_cds;
	struct color_desc_scene cds[NB_CDS];

};

#endif