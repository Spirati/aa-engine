#include <littlethief/base.h>
#include <littlethief/except.h>
#include <iostream>
#include <vector>

Game game;
Renderer renderer{};
AssetFetcher fetcher{};
Script script;

int main(int argc, char* argv[]) {

	char casename[255];

	if (argc == 1) {
		std::cout << "Enter the case name (inside games) to be loaded: ";
		std::cin.getline(casename, 255);
		std::cout << std::endl;
	} else {
		strcpy(casename, argv[1]);
	}
	try {
		fetcher.setDirectories(casename);
	}
	catch (std::filesystem::filesystem_error e) {
		std::cout << "Couldn't find that case; make sure you typed it correctly and try again." << std::endl;
		return 1;
	}
	
	script.registerFetcher(fetcher);

	try {
		//TODO: Fix access violation error(?????)
		script.loadScript("main");
	}
	catch (std::filesystem::filesystem_error e) {
		std::cout << "Couldn't find the entry script; make sure script/main.txt exists!";
		return 1;
	}

	SDL_ShowWindow(renderer.gWindow);

	bool quit = false;
	Game::State state{ game.state };
	RendererLayers newLayers;

	while (!quit) {
		game.ingest(quit);

		try {
			StepResult step{ script.step() };

			state = std::get<Game::State>(step);
			newLayers = std::get<RendererLayers>(step);
			if (newLayers.anySet)
				renderer.updateLayers(newLayers);
		}
		catch (std::runtime_error e) {
			if (!strncmp(e.what(), "Couldn't load script file", 26)) {
				std::cout << e.what() << std::endl;
				break;
			} else {
				std::cout << "An unhandled exception occurred! We're not sure what happened." << std::endl;
				break;
			}
		}

		if (state == Game::State::Quit) break;

		renderer.draw();
	}

	while (true) {};

	renderer.exit();

	return 0;
}
