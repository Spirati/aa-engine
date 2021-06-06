#include <littlethief/base.h>
#include <littlethief/except.h>
#include <SDL_image.h>

Renderer::Renderer() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		const char* e{ SDL_GetError() };

		std::cout << e << std::endl;

		throw SDLResourceFailure(e);
	}
		

	gWindow = SDL_CreateWindow("Little Thief Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
	if (gWindow == NULL) {
		const char* e{ SDL_GetError() };

		std::cout << e << std::endl;

		throw SDLResourceFailure(e);
	}

	gWindowSurface = SDL_GetWindowSurface(gWindow);

	layers = RendererLayers();

}

void Renderer::draw() {
	SDL_FillRect(gWindowSurface, NULL, SDL_MapRGB(gWindowSurface->format, 0xFF, 0x00, 0x00));

	//RendererLayers newLayer = RendererLayers();
	//std::cout << static_cast<void*>(newLayer.ui.surface) << ", " << NULL << std::endl;

	DRAW_LAYER(background);
	DRAW_LAYER(character);
	DRAW_LAYER(foreground);
	DRAW_LAYER(overlay);
	DRAW_LAYER(ui);

	SDL_UpdateWindowSurface(gWindow);
}

void Renderer::updateLayers(RendererLayers& newLayers) {
	layers.ui = newLayers.ui.surface == NULL ? layers.ui : newLayers.ui;
	layers.overlay = newLayers.overlay.surface == NULL ? layers.overlay : newLayers.overlay;
	layers.foreground = newLayers.foreground.surface == NULL ? layers.foreground : newLayers.foreground;
	layers.character = newLayers.character.surface == NULL ? layers.character : newLayers.character;
	layers.background = newLayers.background.surface == NULL ? layers.background : newLayers.background;
}

void Renderer::exit() {

	SDL_FreeSurface(layers.overlay.surface);
	layers.overlay.surface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();


}