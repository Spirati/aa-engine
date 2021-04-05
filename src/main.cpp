#include <init.h>
#include <cstdio>

Game game{};

int main() {
	
	if (!game.init()) {
		printf("Failed to initialize :(\n");
	}
	else {
		SDL_FillRect(game.gSurface, NULL, SDL_MapRGB(game.gSurface->format, 0xFF, 0x00, 0x00));

		SDL_UpdateWindowSurface(game.gWindow);

		SDL_Delay(2000);
	}

	game.close();
}