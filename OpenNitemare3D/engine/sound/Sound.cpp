#include "Sound.h"

void Sound::PlaySound(int i, Datreader snd)
{
    //since original channel only had one sfx channel
    //if (Mix_Playing(1)) return;

    Mix_Chunk sfx;
    sfx.allocated = 1;
    sfx.abuf = (Uint8*)snd[i + SND_OFFSET].data;
    sfx.alen = snd[i + SND_OFFSET].length;
    sfx.volume = 32;
    Mix_PlayChannel(1, &sfx, 0);
    // Mix_FreeChunk(&sfx);
}
