#ifndef SOUND_H
#define SOUND_H

#include "Console.h"

const LPCTSTR SFX_LOADING = TEXT("sfx\\Loading.wav");
const LPCTSTR SFX_MENU_NAVIGATE = TEXT("sfx\\270324__littlerobotsoundfactory__menu-navigate-00.wav");
const LPCTSTR SFX_MENU_SELECT = TEXT("sfx\\150222__pumodi__menu-select.wav");
const LPCTSTR SFX_BOMB = TEXT("sfx\\270306__littlerobotsoundfactory__explosion-02.wav");
const LPCTSTR SFX_LOSE = TEXT("sfx\\270329__littlerobotsoundfactory__jingle-lose-00.wav");
const LPCTSTR SFX_WIN = TEXT("sfx\\270331__littlerobotsoundfactory__jingle-achievement-00.wav");
const LPCTSTR MUSIC_GAME = TEXT("music\\251461__joshuaempyre__arcade-music-loop.wav");

enum SoundType {
	TYPE_SFX,
	TYPE_MUSIC
};

extern bool sfxOn;
extern bool musicOn;

void play(LPCTSTR sound, bool stop, SoundType type);

#endif // SOUND_H