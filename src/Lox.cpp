#include "Lox.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

bool Lox::hadError = false;

void Lox::runFile(std::string path) {
	std::string contents;
	std::string line;
	std::ifstream fin(path);
	
	if(fin.good()) {
		while(std::getline(fin, line)) {
			contents.append(line + "\n");
		}
		contents.pop_back();
	} else {
		std::cerr << "Failed to run file at " << path << '\n';
	}

	run(contents);
	if(hadError) std::exit(1);
}

void Lox::runPrompt() {
	std::string line;

	do {
		std::cout << ':';
		if(std::getline(std::cin, line)) run(line);	
		else break;
		hadError = false;
	} while(true);
}

void Lox::run(std::string source) {
	std::cout << source << '\n';
}

void Lox::reportError(int line, std::string message) {
	std::cerr << "(ERROR at line " << line << "): " << message << '\n';
}
