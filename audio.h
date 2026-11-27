#pragma once

typedef enum {
	sfxPlace,
	sfxWin,
	sfxDraw,
	sfxMove,
	sfxCount
} sfxId;

int audioInit();
void audioShutdown();

void audioPlaySfx(sfxId id);

void audioSetMusicVolume(int v);
void audioSetSfxVolume(int v);
void audioSetMusicMuted(int muted);
void audioSetSfxMuted(int muted);

int audioGetMusicVolume();
int audioGetSfxVolume();
int audioIsMusicMuted(); 
int audioIsSfxMuted(); 

void audioLoad();
void audioSave();