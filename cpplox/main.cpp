#include <iostream>
#include <string>
#include "Lox.hpp"
#include "Token.hpp"

int main() {
	std::string mode;
	bool faultyInput = false;

	do {
		faultyInput = false;
		std::cout << "Select Mode [p/i]:";
		std::getline(std::cin, mode);

		if (!(mode == "p" || mode == "i")) {
			std::cout << "Please select a mode out of: [p for prompt] [i for interpret]\n";
			faultyInput = true;
		}
	} while (faultyInput);

	if (mode == "p") Lox::runPrompt();
	else if(mode == "i") {
		std::string filepath;
		std::cout << "Enter filepath relative to project root directory:";
		std::getline(std::cin, filepath);
		Lox::runFile(filepath);
	}

	return 0;
}
