#include "Sound.h"

bool sfxOn = true;
bool musicOn = true;

void play(LPCTSTR sound, bool stop, SoundType type) {
	stop = true;
	if (type == TYPE_SFX && !sfxOn)
		return;
	if (type == TYPE_MUSIC && !musicOn)
		return;

	DWORD flag = SND_ASYNC;
	if (!stop)
		flag |= SND_NOSTOP;
	if (type == TYPE_MUSIC)
		flag |= SND_LOOP;
	PlaySound(sound, NULL, flag);
}
