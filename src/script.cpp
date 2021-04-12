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

StepResult Script::step() {
	if (currentScript.good()) {

		if (dialogueBlock) return StepResult{ Game::State::Pass, RendererLayers{} };

		const std::regex valid_command{ "(bg|background|char|character|fg|foreground|nick|nickname|mus|music|speak|speaker)(?: ((?: ?\\S+)*))?" };
		const std::regex comment{ "\\/\\/.+" };

		std::smatch results{};
		std::string rawLine;
		std::getline(currentScript, rawLine);

		std::string line{ std::regex_replace(rawLine, comment, "") };

		if (!std::regex_match(line, results, valid_command))
			return step();
		const Script::Command command{ commStrToCommand(results[1]) };
		const std::string args{ results[2] };

		// split args into argument vector (split by space)
		std::vector<std::string> argv;
		std::istringstream iss{ args };
		for (std::string s; iss >> s; )
			argv.push_back(s);

		switch (command) {
		case Command::SetBackground:
			break;
		case Command::SetForeground:
			break;
		case Command::SetCharacter:
			break;
		case Command::SetNickname:
			break;
		case Command::SetMusic:
			break;
		case Command::SetSpeaker:
			break;
		}
	}
	else if(!currentScript.eof()) {
		throw std::runtime_error("Couldn't load script file");
	}
	else {
		return StepResult{ Game::State::Quit, RendererLayers{} };
	}
}

Script::Command Script::commStrToCommand(std::string commstr) {

	if (commstr == "bg" || commstr == "background")
		return Script::Command::SetBackground;
	if (commstr == "char" || commstr == "character")
		return Script::Command::SetCharacter;
	if (commstr == "fg" || commstr == "foreground")
		return Script::Command::SetForeground;
	if (commstr == "nick" || commstr == "nickname")
		return Script::Command::SetNickname;
	if (commstr == "mus" || commstr == "music")
		return Script::Command::SetMusic;
	if (commstr == "speak" || commstr == "speaker")
		return Script::Command::SetSpeaker;
	return Script::Command::NoCommand;
}