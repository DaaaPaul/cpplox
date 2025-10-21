#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lox.hpp"
#include "Token.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "AstPrinterVisitor.hpp"

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
	} else {
		std::cerr << "Failed to run file at " << path << '\n';
	}

	run(contents);
	if (hadError) std::exit(65);
	else if (hadRuntimeError) std::exit(70);
}

void Lox::runPrompt() {
	std::string input;
	bool quit = false;

	while(!quit) {
		std::cout << "|>|";
		if(std::getline(std::cin, input)) {
			if(input != "QQQ") {
				run(input);
				std::cout << '\n';
			} else {
				quit = true;
			}
		} else {
			quit = true;
		}
		hadError = false;
	}
}

void Lox::run(std::string source) {
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();
	Parser parser(std::move(tokens));
	std::unique_ptr<Expr> expression = parser.parse();

	if (hadError || !expression) return;

	interpreter.interperet(std::move(expression));
	std::cout << interpreter.stringify();
}

void Lox::reportError(Token const& token, std::string const& message) {
	if(token.getType() == TokenType::END_OF_FILE) {
		std::cerr << "-----------------------------------------------------------------------\n";
		std::cerr << "ERROR at end of file: " << message << " at \"" << token.toLexeme() << "\"" << '\n';
		std::cerr << "-----------------------------------------------------------------------\n";
	} else {
		std::cerr << "-----------------------------------------------------------------------\n";
		std::cerr << "ERROR at line " << token.getLine() << ": " << message << " at \"" << token.toLexeme() << "\"" << '\n';
		std::cerr << "-----------------------------------------------------------------------\n";
	}

	hadError = true;
}

void Lox::reportRuntimeError(LoxRuntimeError const& error) {
	std::cerr << "RUNTIME ERROR at line " << error.erroneousToken.getLine() << ": " << error.what() << 
		" at\"" << error.erroneousToken.toLexeme() << "\"" << '\n';
	hadRuntimeError = true;
}