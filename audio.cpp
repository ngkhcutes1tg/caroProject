#define MINIAUDIO_IMPLEMENTATION
#define SETTINGS_PATH "settings.cfg"
#include "miniaudio.h"
#include "audio.h"
#include <stdio.h>

static ma_engine engine;
static ma_sound_group musicGroup;
static ma_sound_group sfxGroup;
static ma_sound music;

static int ready = 0;
static int musicLoaded = 0;

static int musicVolume = 70;
static int sfxVolume = 70;
static int musicMuted = 0;
static int sfxMuted = 0;

static const char* sfxPaths[sfxCount] = {
	[sfxPlace] = "assets/audio/chessSound.wav",
	[sfxWin] = "assets/audio/winSound.wav",
	[sfxDraw] = "assets/audio/drawSound.wav",
	[sfxMove] = "assets/audio/moveSound.wav"
};

static int clamp100(int v) {
	if(v < 0) return 0;
	if(v > 100) return 100;
	return v;
}

static void applyAudio() {
	float m = musicMuted ? 0.0f : musicVolume / 100.0f;
	float f = sfxMuted ? 0.0f : sfxVolume / 100.0f;
	ma_sound_group_set_volume(&musicGroup, m);
	ma_sound_group_set_volume(&sfxGroup, f);
}

int audioInit() {
	if(ma_engine_init(NULL, &engine) != MA_SUCCESS) {
		printf("Khong khoi dong duoc am thanh!\n");
		return 0;
	}
	ma_sound_group_init(&engine, 0, NULL, &musicGroup);
	ma_sound_group_init(&engine, 0, NULL, &sfxGroup);
	ready = 1;

	if(ma_sound_init_from_file(&engine, "assets/audio/backgroundMusic.mp3",
								MA_SOUND_FLAG_STREAM, &musicGroup, NULL, &music) == MA_SUCCESS) {
		musicLoaded = 1;	
		ma_sound_set_looping(&music, MA_TRUE);
		ma_sound_start(&music);
	}
	else { 
		printf("Khong tim thay file nhac nen!\n");
	}
	applyAudio();
	return 1;
}

void audioShutdown() {
	if(!ready) return;
	if(musicLoaded) ma_sound_uninit(&music);
	ma_sound_group_uninit(&musicGroup);
	ma_sound_group_uninit(&sfxGroup);
	ma_engine_uninit(&engine);
	ready = 0;
}

void audioPlaySfx(sfxId id) {
	if(!ready || id < 0 || id >= sfxCount) return;
	ma_engine_play_sound(&engine, sfxPaths[id], &sfxGroup);
}

void audioSetMusicVolume(int v) {musicVolume = clamp100(v); applyAudio(); }
void audioSetSfxVolume(int v) {sfxVolume = clamp100(v); applyAudio(); }
void audioSetMusicMuted(int m) {musicMuted = m; applyAudio(); }
void audioSetSfxMuted(int m) {sfxMuted = m; applyAudio(); }

int audioGetMusicVolume() { return musicVolume; }
int audioGetSfxVolume() { return sfxVolume; }
int audioIsMusicMuted() { return musicMuted; }
int audioIsSfxMuted() { return sfxMuted; }

void audioLoad() {
	FILE* f = fopen(SETTINGS_PATH, "rt");
	if(!f) return;

	int mv, sv, mm, sm;
	if(fscanf(f, "%d %d %d %d", &mv, &sv, &mm, &sm) == 4) {
		musicVolume = clamp100(mv);
		sfxVolume = clamp100(sv);
		musicMuted = mm;
		sfxMuted = sm;
		if(ready) applyAudio();
	}
	fclose(f);
}

void audioSave() {
	FILE* f = fopen(SETTINGS_PATH, "wt");
	if(!f) {
		printf("Khong luu duoc cai dat!\n");
		return;
	}
	fprintf(f, "%d %d %d %d", musicVolume, sfxVolume, musicMuted, sfxMuted);
	fclose(f);
}
