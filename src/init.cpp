#include <cstdio>
#include <init.h>

bool Game::init() {
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initialized; %s\n", SDL_GetError());
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("Making an image!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window couldn't be created; %s\n", SDL_GetError());
			success = false;
		}
		else {
			gSurface = SDL_GetWindowSurface(gWindow);
		}

	}


	return success;
}

bool Game::loadMedia() {
	bool success = true;

	return success;
}

void Game::close() {
	SDL_FreeSurface(gImage);
	gImage = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}