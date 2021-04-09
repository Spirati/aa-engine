#include <littlethief/base.h>
#include <regex>
#include <iostream>

void Script::loadScript(const char* scriptName) {
	
	auto path = "script" / std::filesystem::path{ scriptName }.replace_extension(".txt");
	
	std::string paths = path.generic_string();

	try {
		currentScript = fetcher->loadFile(paths.c_str(), false);
	}
	catch (std::filesystem::filesystem_error e) {
		throw e;
	}

}

Game::State Script::step() {
	if (currentScript.good()) {
		std::string line;
		std::getline(currentScript, line);

		std::cout << line << "\n";
	}
	else if(!currentScript.eof()) {
		throw std::runtime_error("Couldn't load script file");
	}
	else {
		throw std::runtime_error("Reached end of script with no successor");
	}
}