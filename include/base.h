#pragma once
#include <SDL2/SDL.h>
#include <filesystem>
#include <fstream>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

struct Game;


struct Renderer {
	SDL_Window* gWindow{ NULL };
	SDL_Surface* gWindowSurface{ NULL };
};

class AssetFetcher {

public:

	void setDirectories(Game* game);

	std::ifstream loadFile(char* filename, char* ext, bool asset);
	std::ifstream loadFile(char* filename, bool asset);
private:
	std::filesystem::path gameDirectory;
	std::filesystem::path defaultDirectory;
	std::filesystem::path resolveAssetPath(char* filename, char* ext);
	std::filesystem::path resolveAssetPath(char* filename);

	std::filesystem::path resolvePath(char* filename, char* ext);
	std::filesystem::path resolvePath(char* filename);
};

class Script {

public:

	void registerFetcher(AssetFetcher& fetcher) {
		fetcher = fetcher;
	}

	//void loadScript(char* scriptName);

	void step();

	static void processTags(char* line);

private:
	std::ifstream currentScript;
	AssetFetcher* fetcher;
};

struct Game {

	static enum State {
		Paused,
		Typing,
		Waiting,
		Choosing
	} state;

	Game(char* name);

	void update();
	void draw();

	AssetFetcher fetcher;
	Renderer renderer;
	Script script;

	char* name;
};








