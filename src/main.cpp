#include <base.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "No case name provided! Exiting." << std::endl;
		return 0;
	}

	Game game = Game{ argv[1] };
}
