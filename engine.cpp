#include "engine.h"
#include "img.h"
#include <tinyfiledialogs\tinyfiledialogs.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>

void Engine::startGame() {
	//init window stuff
	bool quit = false;
	Engine::startGraphics("OpenNitemare3D", 640, 480);
	while (quit = false) {
		Engine::gameLoop();
		SDL_Delay(60);
	}
	
	
	
	
}


//main Lööp
void Engine::gameLoop() { //this is where you actually put your game code, updates 60 times per second
	
	/*
	if (Mix_PlayMusic(music, -1) == -1) {
		//const char* const error = "Mix_PlayMusic: %s\n", Mix_GetError();
		//tinyfd_messageBox("SDL_Mixer error!", "Error with SDL_mixr, "ok", "error", 1);
		
	}
	*/
}

void Engine::startGraphics(const char* Name, int displayWidth, int displayHeight) {

	//load sprites from IMG.1
	IMG img;
	size_t numImages;
	img.Init("GAME.PAL", "IMG.1");
	numImages = img.GetNumImages();


	///int dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	//if (dev == 0) {
	//	SDL_Log("Failed to open audio: %s", SDL_GetError());
	//}


	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		//printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

	}


	Mix_Music* song = Mix_LoadMUS("music.mid");
	Mix_PlayMusic(song, -1);

	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	
	window = SDL_CreateWindow(Name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer, img[3]);
	Engine::gameLoop();
	int index = 352;
	while (true)
	{

		//note, kinda unorganized as this is a test program
		
		//this chunk of code replaces the color white in sprites with transparency 
		SDL_RenderClear(renderer);
		uint32_t keyColor;
		keyColor = SDL_MapRGB(img[index]->format, 255, 255, 255);
		SDL_SetColorKey(img[index], SDL_TRUE, keyColor);


		texture = SDL_CreateTextureFromSurface(renderer, img[index]);
		int img_width = img[index]->h;
		int img_height = img[index]->w;
		index++;
		if (index > 357) {
			index = 352;
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
		dstrect.x = displayWidth / 2 - img_height;
		dstrect.y = displayHeight / 2 - img_width;
		dstrect.w = img_height * 3;
		dstrect.h = img_width * 3;


		SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, 90, nullptr, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);
	}
	
}