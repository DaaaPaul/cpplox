#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lox.hpp"
#include "Token.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "CheckType.hpp"

bool Lox::hadError = false;
bool Lox::hadRuntimeError = false;
Interpreter Lox::interpreter;

void Lox::runFile(std::string path) {
	std::string contents;
	std::string line;
	std::ifstream fin(path);
	
	if(fin.good()) {
		while(std::getline(fin, line)) {
			contents.append(line + "\n");
		}
		contents.pop_back();

		run(contents);
	} else {
		std::cerr << "Failed to run file at " << path << '\n';
	}

	if (hadError) std::exit(65);
	else if (hadRuntimeError) std::exit(70);
}

void Lox::runPrompt() {
	std::string input;
	bool quit = false;

	while(!quit) {
		std::cout << R"(<Lox> )";

		if(std::getline(std::cin, input)) {
			if(input != "QQQ") {
				run(input);
				if(!hadError && !hadRuntimeError) std::cout << '\n';
			} else {
				quit = true;
			}
		} else {
			quit = true;
		}

		hadError = false;
		hadRuntimeError = false;
	}
}

void Lox::run(std::string source) {
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();
	Parser parser(std::move(tokens));
	std::vector<std::unique_ptr<Stmt>> statements(parser.parse());

	if (hadError) return;

	if (statements.size() == 1) {
		CheckType checkType{};
		statements[0]->accept(checkType);
		if(checkType.whichType["EXPRSTMT"]) {
			interpreter.interperet(std::move(statements));
			std::cout << interpreter.stringify();
		} else {
			interpreter.interperet(std::move(statements));
		}
	} else {
		interpreter.interperet(std::move(statements));
	}
}

void Lox::reportError(Token const& token, std::string const& message) {
	std::cerr << "ERROR at line " << token.getLine() << ": " << message << " at \"" << token.toLexeme() << "\"\n";

	hadError = true;
}

void Lox::reportRuntimeError(LoxRuntimeError const& error) {
	std::cerr << "RUNTIME ERROR at line " << error.erroneousToken.getLine() << ": " << error.what() << 
		" at \"" << error.erroneousToken.toLexeme() << "\"\n";
	hadRuntimeError = true;
}