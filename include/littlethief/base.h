#pragma once

#include <SDL2/SDL.h>
#include <filesystem>
#include <fstream>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

struct RendererLayers {
	SDL_Surface* ui;
	SDL_Surface* overlay;
	SDL_Surface* foreground;
	SDL_Surface* character;
	SDL_Surface* background;
};

struct Renderer {

	Renderer();

	void draw();
	void exit();

	SDL_Window* gWindow{ NULL };
	SDL_Surface* gWindowSurface{ NULL };

	RendererLayers layers{ NULL, NULL, NULL, NULL, NULL };
};

struct Game {

	static enum State {
		Paused,
		Typing,
		Waiting,
		Choosing,
		Quit
	} state;

	void ingest(bool& quit);
	void update();

};

class AssetFetcher {

public:

	AssetFetcher();

	void setDirectories(const char* name);

	std::ifstream* loadFile(const char* filename, const char* ext, const bool asset);
	std::ifstream* loadFile(const char* filename, const bool asset);

	SDL_Surface* loadImage(const char* path, Renderer& renderer);


private:
	std::filesystem::path gameDirectory;
	std::filesystem::path defaultDirectory;
	std::filesystem::path resolveAssetPath(const char* filename, const char* ext);
	std::filesystem::path resolveAssetPath(const char* filename);

	std::filesystem::path resolvePath(const char* filename, const char* ext);
	std::filesystem::path resolvePath(const char* filename);
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



