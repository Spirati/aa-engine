#include <littlethief/base.h>
#include <littlethief/except.h>
#include <SDL_image.h>
#include <iostream>


using namespace std;

AssetFetcher::AssetFetcher() {
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw SDLResourceFailure(IMG_GetError());

}

void AssetFetcher::setDirectories(const char* name) {

	auto d = filesystem::current_path();

	defaultDirectory = d;
	gameDirectory = d / "games" / name;
}

filesystem::path AssetFetcher::resolveAssetPath(const char* filename, const char* ext) {

	auto filepath = filesystem::path{ filename }.replace_extension(ext).make_preferred();

	auto gamePath = gameDirectory / "assets" / filepath;
	auto rootPath = defaultDirectory / "assets" / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return rootPath;
	}
	else {
		throw filesystem::filesystem_error(FILE_NOT_FOUND, "assets" / filepath, error_code());
	}
}
filesystem::path AssetFetcher::resolveAssetPath(const char* filename) {
	auto filepath = filesystem::path{ filename }.make_preferred();

	auto gamePath = gameDirectory / "assets" / filepath;
	auto rootPath = defaultDirectory / "assets" / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return rootPath;
	}
	else {
		throw filesystem::filesystem_error(FILE_NOT_FOUND, "assets" / filepath, error_code());
	}
}

filesystem::path AssetFetcher::resolvePath(const char* filename, const char* ext) {
	auto filepath = filesystem::path{ filename }.replace_extension(ext).make_preferred();

	auto gamePath = gameDirectory / filepath;
	auto rootPath = defaultDirectory / filepath;


	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return rootPath;
	}
	else {
		throw filesystem::filesystem_error(FILE_NOT_FOUND, filepath, error_code());
	}
}
filesystem::path AssetFetcher::resolvePath(const char* filename) {
	const filesystem::path filepath = filesystem::path{ filename }.make_preferred();

	auto gamePath = gameDirectory / filepath;
	auto rootPath = defaultDirectory / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return rootPath;
	}
	else {
		throw filesystem::filesystem_error(FILE_NOT_FOUND, filepath, error_code());
	}
}


ifstream* AssetFetcher::loadFile(const char* filename, const char* ext, const bool asset = true) {
	
	ifstream file;
	filesystem::path filepath;
	
	if (asset) {
		try {
			filepath = resolveAssetPath(filename, ext);
		}
		catch (filesystem::filesystem_error e) {
			return nullptr;
		}
	}
	else {
		try {
			filepath = resolvePath(filename, ext);
		}
		catch (filesystem::filesystem_error e) {
			return nullptr;
		}
	}
}
ifstream* AssetFetcher::loadFile(const char* filename, const bool asset = true) {
	ifstream file;
	filesystem::path filepath;

	if (asset) {
		try {
			filepath = resolveAssetPath(filename);
		}
		catch (filesystem::filesystem_error e) {

			return nullptr;
		}
	}
	else {
		try {
			filepath = resolvePath(filename);
		}
		catch (filesystem::filesystem_error e) {
			return nullptr;
		}
	}
}

SDL_Surface* AssetFetcher::loadImage(const char* path, Renderer& renderer) {

	std::string filepath = resolveAssetPath(path, "png").generic_string();

	const char* fpstr = filepath.c_str();

	SDL_Surface* optimized{ NULL };
	SDL_Surface* loaded{ IMG_Load(fpstr) };
	
	if (loaded == NULL)
		throw SDLResourceFailure(SDL_GetError());

	optimized = SDL_ConvertSurface(loaded, renderer.gWindowSurface->format, 0);

	SDL_FreeSurface(loaded);

	return optimized;

}
