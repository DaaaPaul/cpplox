#include <iostream>
#include "Lox.hpp"
#include "Token.hpp"

int main(int argc, char** argv) {
	if(argc == 1) {
		Lox::runPrompt();
	} else if(argc == 2) {
		Lox::runFile(argv[1]);
	} else {
		std::cerr << "Usage: ./main [filepath]\n";
	}

	return 0;
}
