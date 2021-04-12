#pragma once

#include <SDL2/SDL.h>
#include <filesystem>
#include <fstream>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

#define DRAW_LAYER(layer) if (layers.layer.surface != NULL) SDL_BlitSurface(layers.layer.surface, NULL, gWindowSurface, NULL);

#define DRAW_STATIC_LAYER(layer) if (layers.layer.surface != NULL) SDL_BlitSurface(layers.layer.surface, NULL, gWindowSurface, NULL);

struct RendererLayer {

	SDL_Surface* surface{ NULL };
	int animLength{ 1 };
	struct Grid { int x{ 1 }, y{ 1 }; } grid;
};

struct RendererLayers {
	RendererLayer ui;
	RendererLayer overlay;
	RendererLayer foreground;
	RendererLayer character;
	RendererLayer background;
	bool anySet{ false };
};

struct Renderer {

	Renderer();

	void draw();
	void exit();

	SDL_Window* gWindow{ NULL };
	SDL_Surface* gWindowSurface{ NULL };

	RendererLayers layers;
};

struct Game {

	enum class State {
		Paused,
		Typing,
		Waiting,
		Choosing,
		Quit,
		Pass
	};

	State state;

	Game(State state = State::Typing) : state{ state } {}

	void ingest(bool& quit);
	void update();

};

class AssetFetcher {

public:

	AssetFetcher();

	void setDirectories(const char* name);

	std::ifstream loadFile(std::filesystem::path path, const bool asset);
	std::ifstream loadFile(const char* filename, const char* ext, const bool asset);
	std::ifstream loadFile(const char* filename, const bool asset);

	SDL_Surface* loadImage(const char* path, Renderer& renderer);


private:
	std::filesystem::path gameDirectory;
	std::filesystem::path defaultDirectory;
	std::filesystem::path resolveAssetPath(const char* filename, const char* ext);
	std::filesystem::path resolveAssetPath(const char* filename);

	std::filesystem::path resolvePath(const char* filename, const char* ext);
	std::filesystem::path resolvePath(const char* filename);
};


typedef std::tuple<Game::State, RendererLayers> StepResult;

class Script {

public:

	void registerFetcher(AssetFetcher& fp) {
		fetcher = &fp;
	}

	void loadScript(const char* scriptName);

	StepResult step();

	static void processTags(const char* line);

private:

	enum class Command {
		SetForeground,
		SetBackground,
		SetCharacter,
		SetNickname,
		SetSpeaker,
		SetMusic,
		NoCommand
	};

	bool dialogueBlock{ false };
	std::ifstream currentScript;
	std::string currentLine;
	AssetFetcher* fetcher;

	Command commStrToCommand(std::string commstr);
};



