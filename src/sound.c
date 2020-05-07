#include "common.h"


#define SFX_ENGINE_ACCEL "./media/sfx/engine_accel.wav"
#define SFX_ENGINE_NORMAL "./media/sfx/engine_normal.wav"
#define SFX_ENGINE_IDLE "./media/sfx/engine_idle.wav"
#define SFX_ENGINE_NITRO "./media/sfx/engine_nitro.wav"
#define SFX_IMPACT "./media/sfx/impact.wav"
#define SFX_DRIFT "./media/sfx/drift.wav"

#define SFX_CHANNEL_MOTOR 0
#define SFX_CHANNEL_COLLISION 1
#define SFX_CHANNEL_DRIFT 1

int sound_load_resources(struct game_context *ctx)
{
	// init Music and SFX management
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_ttf could not initialize! SDL_Mixer Error: %s\n",
		       TTF_GetError());
		return -EINVAL;
	}

	ctx->sfx.engine_accel = Mix_LoadWAV(SFX_ENGINE_ACCEL);
	if (!ctx->sfx.engine_accel) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_ENGINE_ACCEL,
			Mix_GetError());
		return -EINVAL;
	}

	ctx->sfx.engine_normal = Mix_LoadWAV(SFX_ENGINE_NORMAL);
	if (!ctx->sfx.engine_normal) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_ENGINE_NORMAL,
			Mix_GetError());
		return -EINVAL;
	}

	ctx->sfx.engine_nitro = Mix_LoadWAV(SFX_ENGINE_NITRO);
	if (!ctx->sfx.engine_nitro) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_ENGINE_NITRO,
			Mix_GetError());
		return -EINVAL;
	}

	ctx->sfx.engine_idle = Mix_LoadWAV(SFX_ENGINE_IDLE);
	if (!ctx->sfx.engine_idle) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_ENGINE_IDLE,
			Mix_GetError());
		return -EINVAL;
	}

	ctx->sfx.impact = Mix_LoadWAV(SFX_IMPACT);
	if (!ctx->sfx.impact) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_IMPACT,
			Mix_GetError());
		return -EINVAL;
	}

	ctx->sfx.drift = Mix_LoadWAV(SFX_DRIFT);
	if (!ctx->sfx.drift) {
		SDL_Log("[%s] failed to load '%s'. Err = %s\n",
			__func__,
			SFX_DRIFT,
			Mix_GetError());
		return -EINVAL;
	}

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
	}

	if (ctx->status_cur == GAME_STATE_RACE_ANIM_START &&
	    ctx->status_prev != GAME_STATE_RACE_ANIM_START) {
		Mix_PlayChannel(SFX_CHANNEL_MOTOR, ctx->sfx.engine_idle, -1);
	}

	if (ctx->collision_detected)
		Mix_PlayChannel(SFX_CHANNEL_COLLISION, ctx->sfx.impact, 0);

	if ((ctx->drift >= 0.025f && ctx->drift_prev < 0.025f) ||
	    (ctx->drift <= -0.025f && ctx->drift_prev > -0.025f))
		Mix_PlayChannel(SFX_CHANNEL_DRIFT, ctx->sfx.drift, -1);

	if ((ctx->drift < 0.025f && ctx->drift_prev >= 0.025f) ||
	    (ctx->drift > -0.025f && ctx->drift_prev <= -0.025f))
		Mix_HaltChannel(SFX_CHANNEL_DRIFT);

	return 0;
}