#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lox.hpp"
#include "Token.hpp"
#include "Scanner.hpp"

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
	std::string input;
	bool quit = false;

	while(!quit) {
		std::cout << '>';
		if(std::getline(std::cin, input)) {
			run(input);
		} else {
			quit = true;
		}
		hadError = false;
	}
}

void Lox::run(std::string source) {
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();
	for(Token t: tokens) std::cout << t.toString() << '\n';	
}

void Lox::reportError(int line, std::string message) {
	std::cerr << "(ERROR at line " << line << "): " << message << '\n';
	hadError = true;
}
