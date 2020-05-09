#include "common.h"


#define SFX_ENGINE_ACCEL "./media/sfx/engine_accel.wav"
#define SFX_ENGINE_NORMAL "./media/sfx/engine_normal.wav"
#define SFX_ENGINE_IDLE "./media/sfx/engine_idle.wav"
#define SFX_ENGINE_NITRO "./media/sfx/engine_nitro.wav"
#define SFX_IMPACT "./media/sfx/impact.wav"
#define SFX_DRIFT "./media/sfx/drift.wav"
#define SFX_1 "./media/sfx/1.wav"
#define SFX_2 "./media/sfx/2.wav"
#define SFX_3 "./media/sfx/3.wav"
#define SFX_GO "./media/sfx/go.wav"
#define SFX_CONGRATULATIONS "./media/sfx/congratulations.wav"
#define SFX_LAP "./media/sfx/lap_01.wav"

#define MUSIC_END_RACE "./media/music/end_race.ogg"
#define MUSIC_BGM_1 "./media/music/aries_beats---infinity---128kbps.mp3"
#define MUSIC_BGM_2                                                            \
	"./media/music/simon_bichbihler---in_the_1980s---128kbps.mp3"
#define MUSIC_BGM_3 "./media/music/aries_beats---turbo_rush---128kbps.mp3"
#define MUSIC_BGM_4                                                            \
	"./media/music/teknoaxe---sunrise_over_losangeles---128kbps.mp3"
#define MUSIC_BGM_1_NAME "\"Infinity\" by Aries Beats"
#define MUSIC_BGM_2_NAME "\"In the 1980s\" by Simon Bichbihler"
#define MUSIC_BGM_3_NAME "\"Turbo Rush\" by Aries Beats"
#define MUSIC_BGM_4_NAME "\"Sunrise Over Los Angeles\" by TeknoAXE"                                                           \

#define MAX_VOLUME 128

#define SFX_CHANNEL_MOTOR 0
#define SFX_CHANNEL_COLLISION 1
#define SFX_CHANNEL_DRIFT 1


static int sound_load_music(Mix_Music **music, const char *path)
{
	*music = Mix_LoadMUS(path);
	if (!*music) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			path,
			Mix_GetError());
		return -EINVAL;
	}
	return 0;
}


static int sound_load_wav(Mix_Chunk **sfx, const char *path)
{
	*sfx = Mix_LoadWAV(path);
	if (!*sfx) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			path,
			Mix_GetError());
		return -EINVAL;
	}
	return 0;
}

int sound_load_resources(struct game_context *ctx)
{
	// init Music and SFX management
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("SDL_ttf could not initialize! SDL_Mixer Error: %s\n",
			TTF_GetError());
		return -EINVAL;
	}

	Mix_VolumeMusic(MAX_VOLUME);

	sound_load_music(&ctx->music.end_race, MUSIC_END_RACE);
	sound_load_music(&ctx->music.bgm[0], MUSIC_BGM_1);
	sound_load_music(&ctx->music.bgm[1], MUSIC_BGM_2);
	sound_load_music(&ctx->music.bgm[2], MUSIC_BGM_3);
	sound_load_music(&ctx->music.bgm[3], MUSIC_BGM_4);

	ctx->music.bgm_name[0] = MUSIC_BGM_1_NAME;	
	ctx->music.bgm_name[1] = MUSIC_BGM_2_NAME;	
	ctx->music.bgm_name[2] = MUSIC_BGM_3_NAME;	
	ctx->music.bgm_name[3] = MUSIC_BGM_4_NAME;	

	sound_load_wav(&ctx->sfx.engine_accel, SFX_ENGINE_ACCEL);
	sound_load_wav(&ctx->sfx.engine_nitro, SFX_ENGINE_NITRO);
	sound_load_wav(&ctx->sfx.engine_normal, SFX_ENGINE_NORMAL);
	sound_load_wav(&ctx->sfx.engine_idle, SFX_ENGINE_IDLE);
	sound_load_wav(&ctx->sfx.impact, SFX_IMPACT);
	sound_load_wav(&ctx->sfx.drift, SFX_DRIFT);
	sound_load_wav(&ctx->sfx.lap, SFX_LAP);

	sound_load_wav(&ctx->sfx.one, SFX_1);
	sound_load_wav(&ctx->sfx.two, SFX_2);
	sound_load_wav(&ctx->sfx.three, SFX_3);
	sound_load_wav(&ctx->sfx.go, SFX_GO);
	sound_load_wav(&ctx->sfx.congratulations, SFX_CONGRATULATIONS);


	return 0;
}

int main_sound(struct game_context *ctx)
{


	if (ctx->status_cur == GAME_STATE_RACE ||
	    ctx->status_cur == GAME_STATE_RACE_COLLISION_SCENE ||
	    ctx->status_cur == GAME_STATE_RACE_NITRO

	) {

		// check accel update for SFX
		if (ctx->keys.nitro &&
		    ctx->keys.nitro != ctx->keys.nitro_prev) {
			Mix_HaltChannel(SFX_CHANNEL_MOTOR);
			Mix_PlayChannel(
				SFX_CHANNEL_MOTOR, ctx->sfx.engine_nitro, -1);

			SDL_Log("[%s] NITRO 1\n", __func__);

		} else if (ctx->keys.accel != ctx->keys.accel_prev) {
			Mix_HaltChannel(SFX_CHANNEL_MOTOR);
			/*SDL_Log("[%s] ?????, accel=%d, accel_prev=%d\n",
				__func__,
				ctx->keys.accel,
				ctx->keys.accel_prev);*/
			if (ctx->keys.accel) {
				if (ctx->nitro_nb_frame) {
					Mix_PlayChannel(SFX_CHANNEL_MOTOR,
							ctx->sfx.engine_nitro,
							-1);
					SDL_Log("[%s] NITRO 2\n", __func__);
				} else {
					Mix_PlayChannel(SFX_CHANNEL_MOTOR,
							ctx->sfx.engine_accel,
							-1);
					SDL_Log("[%s] ACCEL, accel=%d, accel_prev=%d\n",
						__func__,
						ctx->keys.accel,
						ctx->keys.accel_prev);
				}
			} else {
				Mix_PlayChannel(SFX_CHANNEL_MOTOR,
						ctx->sfx.engine_normal,
						-1);
				SDL_Log("[%s] NORMAL, accel=%d, accel_prev=%d\n",
					__func__,
					ctx->keys.accel,
					ctx->keys.accel_prev);
			}
		} else {

			/*SDL_Log("[%s] 3rd IF, accel=%d, accel_prev=%d,
			   nitro_frame=%d\n",
				__func__,
				ctx->keys.accel,
				ctx->keys.accel_prev,
				ctx->nitro_nb_frame
				);*/

			if (ctx->keys.accel &&
			    ctx->nitro_nb_frame == 1 /*50*/) {
				Mix_PlayChannel(SFX_CHANNEL_MOTOR,
						ctx->sfx.engine_accel,
						-1);
				SDL_Log("[%s] NITRO -> ACCEL\n", __func__);
			}
		}


		if (ctx->collision_detected)
			Mix_PlayChannel(
				SFX_CHANNEL_COLLISION, ctx->sfx.impact, 0);

		if ((ctx->drift >= 0.025f && ctx->drift_prev < 0.025f) ||
		    (ctx->drift <= -0.025f && ctx->drift_prev > -0.025f))
			Mix_PlayChannel(SFX_CHANNEL_DRIFT, ctx->sfx.drift, -1);


		if (ctx->lap_sfx)
			Mix_PlayChannel(-1, ctx->sfx.lap, 0);
	}

	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START &&
	    ctx->status_prev != GAME_STATE_RACE_ANIM_START) {
		Mix_PlayChannel(SFX_CHANNEL_MOTOR, ctx->sfx.engine_idle, -1);
		SDL_Log("[%s] engine IDLE\n", __func__);
	}

	if ((ctx->drift < 0.025f && ctx->drift_prev >= 0.025f) ||
	    (ctx->drift > -0.025f && ctx->drift_prev <= -0.025f))
		Mix_HaltChannel(SFX_CHANNEL_DRIFT);


	// End race animation SFX
	if (ctx->status_cur == GAME_STATE_RACE_ANIM_END &&
	    ctx->status_prev != GAME_STATE_RACE_ANIM_END) {
		Mix_HaltMusic();
		Mix_HaltChannel(SFX_CHANNEL_MOTOR);
		Mix_PlayMusic(ctx->music.end_race, 0);
		Mix_PlayChannel(-1, ctx->sfx.congratulations, 0);
	}

	// Countdown of start animation
	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START) {
		if (ctx->nb_frame_anim == FPS * (START_ANIM_DURATION - 1))
			Mix_PlayChannel(-1, ctx->sfx.go, 0);
		if (ctx->nb_frame_anim == FPS * (START_ANIM_DURATION - 2))
			Mix_PlayChannel(-1, ctx->sfx.one, 0);
		if (ctx->nb_frame_anim == FPS * (START_ANIM_DURATION - 3))
			Mix_PlayChannel(-1, ctx->sfx.two, 0);
		if (ctx->nb_frame_anim == FPS * (START_ANIM_DURATION - 4))
			Mix_PlayChannel(-1, ctx->sfx.three, 0);
	}

	if (ctx->status_cur == GAME_STATE_RACE &&
	    ctx->status_prev == GAME_STATE_RACE_ANIM_START) {
		Mix_PlayMusic(ctx->music.bgm[ctx->bgm_idx], -1);
	}


	return 0;
}