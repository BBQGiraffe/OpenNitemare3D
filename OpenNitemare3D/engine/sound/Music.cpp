#include "Music.h"

void Music::PlaySong(int i, Datreader snd, int loop)
{
	SDL_RWops* test = SDL_RWFromMem(snd[i].data, snd[i].length);
	Mix_PlayMusic(Mix_LoadMUS_RW(test, 1), loop);
	Mix_VolumeMusic(32);
}
