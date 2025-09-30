#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Lox.hpp"
#include "Token.hpp"

int main() {
	std::string fullInput;
	std::getline(std::cin, fullInput);

	std::vector<std::string> inputArguements;
	std::istringstream inputStream(fullInput);
	std::string extracted;
	while(inputStream >> extracted) inputArguements.push_back(extracted);

	if (inputArguements.size() > 1) {
		std::cout << "Usage: <prompt/source code filepath>";
	} else if(inputArguements[0] == "prompt") {
		Lox::runPrompt();
	} else if(inputArguements[0] != "prompt") {
		Lox::runFile(inputArguements[0]);
	}

	return 0;
}
