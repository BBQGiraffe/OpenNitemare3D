#include "engine.h"
#include "img.h"
#include <tinyfiledialogs\tinyfiledialogs.h>
#include <iostream>

void Engine::startGame() {
	//init window stuff
	Engine::startGraphics("OpenNitemare3D", 640, 480);
	bool quit = false;
	
	
	
}

void Engine::startGraphics(const char* Name, int displayWidth, int displayHeight) {
	IMG img;
	size_t numImages;
	//FileNames fileIndex;
	img.Init("GAME.PAL", "IMG.1");
	numImages = img.GetNumImages();
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(Name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer, img[3]);
	
	int index = 482;
	while (true)
	{
		SDL_RenderClear(renderer);
		texture = SDL_CreateTextureFromSurface(renderer, img[index]);
		int img_width = img[index]->h;
		int img_height = img[index]->w;
		index++;
		if (index > 527) {
			index = 482;
		}
		SDL_Delay(250);
		SDL_PollEvent(&event);
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
		//dstrect.x = (displayWidth - displayHeight) / 2 - 1;
		//dstrect.y = (displayHeight - displayWidth) / 2;
		dstrect.x = displayWidth / 2;
		dstrect.y = displayHeight / 2;
		dstrect.w = img_height * 3;
		dstrect.h = img_width * 3;


		SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, 90, nullptr, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);
	}
	
}