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
	} else if (argc != 2) {
		std::cerr << "No case name provided! Exiting." << std::endl;
		return 1;
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

	while (!quit) {
		game.ingest(quit);

		try {
			script.step();
		}
		catch (std::runtime_error e) {
			if (!strncmp(e.what(), "Couldn't load script file", 26)) {
				std::cout << e.what() << std::endl;
				return 1;
			}
			else if (!strncmp(e.what(), "Reached end of script with no successor", 40)) {
				return 0;
			}
			else {
				std::cout << "An unhandled exception occurred! We're not sure what happened." << std::endl;
				return 1;
			}
		}

		renderer.draw();
	}

	renderer.exit();

	return 0;
}
