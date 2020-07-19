#ifndef COMMON_H
#define COMMON_H


#define MAX_VOLUME 128

#define SFX_CHANNEL_MENU 3

enum car_sprite_idx {
 	CAR_SPRITE_REAR,
 	CAR_SPRITE_RIGHT1,
 	CAR_SPRITE_RIGHT2,
 	CAR_SPRITE_LAST
};

enum car_model_type {
 	CAR_MODEL_TRUENO = 0,
 	CAR_MODEL_DELTA,
 	CAR_MODEL_FALCON,
 	CAR_MODEL_HART,
 	CAR_MODEL_IMPREZIA,
 	CAR_MODEL_LANCER,
 	CAR_MODEL_TT,
 	CAR_MODEL_NSX,
 	CAR_MODEL_LOTUS,
 	CAR_MODEL_VIPER,
 	CAR_MODEL_LAST
};

enum car_model_mask {
 	CAR_MASK_TRUENO = (1u << 0),
 	CAR_MASK_DELTA = (1u << 1),
 	CAR_MASK_FALCON = (1u << 2),
 	CAR_MASK_HART = (1u << 3),
 	CAR_MASK_IMPREZIA = (1u << 4),
 	CAR_MASK_LANCER = (1u << 5),
 	CAR_MASK_TT = (1u << 6),
 	CAR_MASK_NSX = (1u << 7),
 	CAR_MASK_LOTUS = (1u << 8),
 	CAR_MASK_VIPER = (1u << 9),
};


enum car_stat_type {
 	CAR_STAT_SPEED = 0,
 	CAR_STAT_ACCEL,
 	CAR_STAT_CENTRIFUGAL,
 	CAR_STAT_NITRO,
 	CAR_STAT_LAST
};

/* identifies the different layers. Their value is the coefficient to which
 * they scroll */
enum background_layer {
	BG_LAYER_SKY_FAR = 2,
	BG_LAYER_LANDSCAPE_FAR = 4,
	BG_LAYER_LANDSCAPE_NEAR = 5,
	BG_LAYER_SKY_NEAR = 6
};

#endif