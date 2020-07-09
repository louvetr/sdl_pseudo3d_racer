   
#define NB_BGM 4

enum sound_volume {
	VOLUME_0  = 0,
	VOLUME_20 = 26,
	VOLUME_40 = 51,
	VOLUME_60 = 77,
	VOLUME_80 = 102,
	VOLUME_100 = 128,
};

enum sfx_state {
	SFX_NONE = 0,
	SFX_IDLE = 1,
	SFX_NORMAL = 2,
	SFX_ACCEL = 4,
	SFX_NITRO = 8,
	SFX_DRIFT = 16,
	SFX_SHOCK = 32
};

struct sfxs {
	enum sfx_state state;
	Mix_Chunk *engine_accel;
	Mix_Chunk *engine_normal;
	Mix_Chunk *engine_nitro;
	Mix_Chunk *engine_idle;
	Mix_Chunk *impact;
	Mix_Chunk *drift;
	Mix_Chunk *lap;
	Mix_Chunk *one;
	Mix_Chunk *two;
	Mix_Chunk *three;
	Mix_Chunk *go;
	Mix_Chunk *congratulations;

	Mix_Chunk *menu_a;
	Mix_Chunk *menu_b;
};

struct musics {
	Mix_Music *title;
	Mix_Music *menu;
	Mix_Music *end_race;
	Mix_Music *bgm[NB_BGM];
	char *bgm_name[NB_BGM];
};

struct sound_info {
	struct sfxs sfx;
	struct musics music;
	int bgm_idx;
	enum sound_volume volume_music;
	enum sound_volume volume_sfx;

	// flags for SFX notifications
	int collision_detected;
	float drift;
	float drift_prev;
	int lap_sfx;

};