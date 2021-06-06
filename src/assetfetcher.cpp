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

	if (!filesystem::exists(gameDirectory))
		throw filesystem::filesystem_error(FILE_NOT_FOUND, gameDirectory, error_code());
}

filesystem::path AssetFetcher::resolveAssetPath(filesystem::path filepath) {
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

filesystem::path AssetFetcher::resolveAssetPath(const char* filename, const char* ext) {

	auto filepath = filesystem::path{ filename }.replace_extension(ext);

	return resolveAssetPath(filepath);
}
filesystem::path AssetFetcher::resolveAssetPath(const char* filename) {
	auto filepath = filesystem::path{ filename };

	return resolveAssetPath(filepath);
}

filesystem::path AssetFetcher::resolveAssetPath(const char* filename, const char* folder, const char* ext) {
	auto filepath_a = filesystem::path{ folder };
	auto filepath_b = filesystem::path{ filename }.replace_extension(ext);
	auto filepath = filepath_a / filepath_b;

	return resolveAssetPath(filepath);
}

filesystem::path AssetFetcher::resolvePath(const char* filename, const char* ext) {
	auto filepath = filesystem::path{ filename }.replace_extension(ext);

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
	auto filepath = filesystem::path{ filename };

	auto gamePath = gameDirectory / filepath.make_preferred();
	auto rootPath = defaultDirectory / filepath.make_preferred();

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

ifstream AssetFetcher::loadFile(const char* filename, const char* ext, const bool asset = true) {
	
	ifstream file;
	filesystem::path filepath;
	
	if (asset) {
		try {
			filepath = resolveAssetPath(filename, ext);
		}
		catch (filesystem::filesystem_error e) {
			throw e;
		}
	}
	else {
		try {
			filepath = resolvePath(filename, ext);
		}
		catch (filesystem::filesystem_error e) {
			throw e;
		}
	}
	file.open(filepath);
	return file;
}
ifstream AssetFetcher::loadFile(const char* filename, const bool asset = true) {
	ifstream file;
	filesystem::path filepath;

	if (asset) {
		try {
			filepath = resolveAssetPath(filename);
		}
		catch (filesystem::filesystem_error e) {

			throw e;
		}
	}
	else {
		try {
			filepath = resolvePath(filename);
		}
		catch (filesystem::filesystem_error e) {
			throw e;
		}
	}
	file.open(filepath);
	return file;
}

SDL_Surface* AssetFetcher::loadImage(const char* path, const char* folder) {

	std::string filepath = resolveAssetPath(path, folder, "png").generic_string();

	const char* fpstr = filepath.c_str();

	SDL_Surface* optimized{ NULL };
	SDL_Surface* loaded{ IMG_Load(fpstr) };
	
	if (loaded == NULL)
		throw SDLResourceFailure(SDL_GetError());

	optimized = SDL_ConvertSurface(loaded, ref_renderer.gWindowSurface->format, 0);

	SDL_FreeSurface(loaded);

	return optimized;

}
