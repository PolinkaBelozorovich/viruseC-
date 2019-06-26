#include "SDL.h"
#include <stdio.h>
#include <iostream>


bool running;
SDL_Event events;


void inputManager(SDL_Window* win) {
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_QUIT) {
			SDL_HideWindow(win);
			// пропишешь слип
			//SDL_ShowWindow() и вставишь сюда свое окно
		}
	}
}



int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_Window* window = SDL_CreateWindow("An SDL2 window", 10, 25, 1500, 785, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* bmp = SDL_LoadBMP("virus3.bmp");
	if (bmp == nullptr) {
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	running = true;


	while (running) {
		inputManager(window);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}