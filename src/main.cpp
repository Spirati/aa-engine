#include <littlethief/base.h>
#include <littlethief/except.h>
#include <iostream>
#include <vector>

Game game;
Renderer renderer{};
AssetFetcher fetcher;
Script script;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "No case name provided! Exiting." << std::endl;
		return 0;
	}

	fetcher.setDirectories(argv[1]);
	script.registerFetcher(fetcher);

	renderer.layers.overlay.surface = fetcher.loadImage("bg/witness", renderer);
	renderer.layers.foreground.surface = fetcher.loadImage("fg/witness", renderer);

	bool quit = false;

	while (!quit) {
		game.ingest(quit);

		renderer.draw();
	}

	renderer.exit();

}
