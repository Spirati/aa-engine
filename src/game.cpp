#include <littlethief/base.h>

void Game::ingest(bool& quit) {
	quit = false;
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			quit = true;
	}
}