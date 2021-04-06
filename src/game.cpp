#include <base.h>

Game::Game(char* name) : name{ name } {

	fetcher.setDirectories(this);
	script.registerFetcher(fetcher);

}