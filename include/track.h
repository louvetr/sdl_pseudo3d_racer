
//#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#define NB_SECTOR_PARAM 7
#define SECTOR_PARAM_ENTER_LG 0
#define SECTOR_PARAM_HOLD_LG 1
#define SECTOR_PARAM_EXIT_LG 2
#define SECTOR_PARAM_EXIT_Y 3
#define SECTOR_PARAM_EXIT_CURVE 4
#define SECTOR_PARAM_NB_LANE_ENTER 5
#define SECTOR_PARAM_NB_LANE_EXIT 6

#define NB_SECTOR_DIJON 14


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

int sector_dijon[NB_SECTOR_DIJON][NB_SECTOR_PARAM] = {
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 3, 2},
	{LG_SHORT, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 2, 2},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_UP_LOW, CURVE_L_EASY, 2, 2},
	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 2, 2},
	{LG_VSHORT, LG_VSHORT, LG_VSHORT, HILL_NONE, CURVE_NONE, 2, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_UP_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_LONG, LG_MEDIUM, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},
	{LG_SHORT, LG_MEDIUM, LG_LONG, HILL_NONE, CURVE_L_HARD, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_UP_MEDIUM, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_MEDIUM, LG_SHORT, HILL_NONE, CURVE_R_MEDIUM, 3, 3},
	{LG_LONG, LG_LONG, LG_LONG, HILL_DOWN_HIGH, CURVE_NONE, 3, 3},
	{LG_MEDIUM, LG_MEDIUM, LG_MEDIUM, HILL_NONE, CURVE_NONE, 3, 3}};