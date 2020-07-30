#ifndef _MUSIC_H
#define _MUSIC_H
#include "../dat/Datreader.h"
#include <SDL.h>
#undef main
#include <SDL_mixer.h>
class Music {
public:
	static void PlaySong(int i, Datreader snd, int loop);
};

#endif