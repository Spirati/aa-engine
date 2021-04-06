#include <base.h>
#include <gameexcept.h>
#include <iostream>


using namespace std;

/*
void Script::loadScript(char* scriptName) {
	currentScript = fetcher->loadFile(scriptName, ".txt");
}
*/

void AssetFetcher::setDirectories(Game* game) {

	auto d = filesystem::current_path();

	defaultDirectory = d;
	gameDirectory = d / "games" / game->name;
}

filesystem::path AssetFetcher::resolveAssetPath(char* filename, char* ext) {
	auto filepath = filesystem::path{ filename }.replace_extension(ext);

	auto gamePath = gameDirectory / "assets" / filepath;
	auto rootPath = defaultDirectory / "assets" / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return gamePath;
	}
	else {
		throw AssetNotFound("assets" / filepath);
	}
}
filesystem::path AssetFetcher::resolveAssetPath(char* filename) {
	auto filepath = filesystem::path{ filename };

	auto gamePath = gameDirectory / "assets" / filepath;
	auto rootPath = defaultDirectory / "assets" / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return gamePath;
	}
	else {
		throw AssetNotFound("assets" / filepath);
	}
}

filesystem::path AssetFetcher::resolvePath(char* filename, char* ext) {
	auto filepath = filesystem::path{ filename }.replace_extension(ext);

	auto gamePath = gameDirectory / filepath;
	auto rootPath = defaultDirectory / filepath;


	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return gamePath;
	}
	else {
		throw AssetNotFound(filepath);
	}
}
filesystem::path AssetFetcher::resolvePath(char* filename) {
	auto filepath = filesystem::path{ filename };

	auto gamePath = gameDirectory / filepath;
	auto rootPath = defaultDirectory / filepath;

	if (filesystem::exists(gamePath)) {
		return gamePath;
	}
	else if (filesystem::exists(rootPath)) {
		return gamePath;
	}
	else {
		throw AssetNotFound(filepath);
	}
}


ifstream AssetFetcher::loadFile(char* filename, char* ext, bool asset = true) {
	
	ifstream file;
	filesystem::path filepath;
	
	if (asset) {
		try {
			filepath = resolveAssetPath(filename, ext);
		}
		catch (AssetNotFound e) {
			throw e;
		}
	}
	else {
		try {
			filepath = resolvePath(filename, ext);
		}
		catch (AssetNotFound e) {
			throw e;
		}
	}
}
ifstream AssetFetcher::loadFile(char* filename, bool asset = true) {
	ifstream file;
	filesystem::path filepath;

	if (asset) {
		try {
			filepath = resolveAssetPath(filename);
		}
		catch (AssetNotFound e) {
			throw e;
		}
	}
	else {
		try {
			filepath = resolvePath(filename);
		}
		catch (AssetNotFound e) {
			throw e;
		}
	}
}
