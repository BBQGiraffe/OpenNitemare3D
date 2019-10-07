#include <string>

#include <stdio.h>

#include "SDL.h"

#include "img.h"

#define MAX_STR_LEN 255

int main()
{
	IMG img;
	size_t numImages;
	std::string name;
	
	img.Init("GAME.PAL", "IMG.1");
	numImages = img.GetNumImages();
	
	for (int i = 0; i < numImages; i++)
	{
		name = std::to_string(i) + ".bmp";
		if (img[i] != NULL)
		{
			SDL_SaveBMP(img[i], name.c_str());
		}
	}
}
