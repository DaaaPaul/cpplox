#include <iostream>
#include <string>
#include <memory>
#include "Lox.hpp"
#include "Token.hpp"
#include "AstPrinterVisitor.hpp"

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

	// TEST CASE FOR AST CLASSES
	//const Expr rightHandNumber(Literal(45.67));
	//const Expr rightHandNumberGrouping(Grouping(std::make_unique<Expr>(rightHandNumber)));

	//const Expr leftHandNumber(Literal(123));
	//const Expr unaryLeftHandNumber(Unary(Token(-1, {}, "-", TokenType::MINUS), std::make_unique<Expr>(leftHandNumber)));

	//const Expr binary(Binary(std::make_unique<Expr>(unaryLeftHandNumber), Token(-1, {}, "*", TokenType::STAR), std::make_unique<Expr>(rightHandNumberGrouping)));

	//std::cout << AstPrinterVisitor().print(binary);

	return 0;
}
