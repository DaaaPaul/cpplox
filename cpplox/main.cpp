/* cpplox - A C++ interpreter of the Lox programming language
source code -> SCANNER -> tokens -> PARSER -> ast -> INTERPRETER */

#include <iostream>
#include <string>
#include <memory>
#include "Lox.hpp"
#include "Token.hpp"

int main() {
	std::string mode;
	bool faultyInput = false;

	// enter by prompting user, REPL or interpret
	do {
		faultyInput = false;
		std::cout << "Select mode [REPL/interpret]:";
		std::getline(std::cin, mode);

		if (!(mode == "REPL" || mode == "interpret")) {
			std::cout << "Please select a valid mode\n";
			faultyInput = true;
		}
	} while (faultyInput);

	if (mode == "REPL") Lox::runPrompt();
	else if(mode == "interpret") {
		std::string filepath;
		std::cout << "Enter filepath relative to project root directory:";
		std::getline(std::cin, filepath);
		Lox::runFile(filepath);
	}

	return 0;
}
