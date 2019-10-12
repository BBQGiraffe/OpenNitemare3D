#include "engine.h"
#include "img.h"
#include "fileNames.h"
#include <tinyfiledialogs\tinyfiledialogs.h>

void Engine::startGame() {
	//init window stuff
	Engine::startGraphics("OpenNitemare3D", 640, 640);
	bool quit = false;
	
	
	
}

void Engine::startGraphics(const char* Name, int displayWidth, int displayHeight) {
	IMG img;
	size_t numImages;
	FileNames fileIndex;
	img.Init("GAME.PAL", "IMG.1");
	numImages = img.GetNumImages();
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(Name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer, img[fileIndex.getSprite("RED_WALL_SINGLE_PAINTING")]);
	while (true)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			SDL_DestroyTexture(texture);
			//SDL_FreeSurface(image);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);

			SDL_Quit();
			return;
			break;
		}

		SDL_Rect dstrect;
		dstrect.x = (displayWidth - displayHeight) / 2 - 1;
		dstrect.y = (displayHeight - displayWidth) / 2;
		dstrect.w = displayHeight;
		dstrect.h = displayWidth; //; //		SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, 90, nullptr, SDL_FLIP_NONE);


		SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, 90, nullptr, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);
	}
	
}