#pragma once
#include <SDL2/SDL.h>


#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

extern struct Game {
	bool init();
	bool loadMedia();
	void close();
	SDL_Window* gWindow{ NULL };
	SDL_Surface* gSurface{ NULL };
	SDL_Surface* gImage{ NULL };
};

