#include <littlethief/base.h>
#include <littlethief/except.h>
#include <SDL_image.h>

Renderer::Renderer() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		const char* e{ SDL_GetError() };

		std::cout << e << std::endl;

		throw SDLResourceFailure(e);
	}
		

	gWindow = SDL_CreateWindow("Little Thief Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		const char* e{ SDL_GetError() };

		std::cout << e << std::endl;

		throw SDLResourceFailure(e);
	}

	gWindowSurface = SDL_GetWindowSurface(gWindow);

}

void Renderer::draw() {
	SDL_FillRect(gWindowSurface, NULL, SDL_MapRGB(gWindowSurface->format, 0xFF, 0x00, 0x00));

	if (layers.overlay != NULL)
		SDL_BlitSurface(layers.overlay, NULL, gWindowSurface, NULL);

	SDL_UpdateWindowSurface(gWindow);
}

void Renderer::exit() {
	SDL_FreeSurface(layers.overlay);
	layers.overlay = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();


}