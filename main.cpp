









#include <string>
#include <tinyfiledialogs\tinyfiledialogs.h>
#include <stdio.h>
#include "engine.h"
#include <SDL2/SDL.h>
#undef main





int main()
{

	Engine engine;
	engine.startGame();
	return 0;
}




/*
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
	return 0;
}
*/
