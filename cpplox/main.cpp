#include <iostream>
#include <string>
#include <memory>
#include "Lox.hpp"
#include "Token.hpp"
#include "AstPrinterVisitor.hpp"

int main() {
	//std::string mode;
	//bool faultyInput = false;

	//do {
	//	faultyInput = false;
	//	std::cout << "Select Mode [p/i]:";
	//	std::getline(std::cin, mode);

	//	if (!(mode == "p" || mode == "i")) {
	//		std::cout << "Please select a mode out of: [p for prompt] [i for interpret]\n";
	//		faultyInput = true;
	//	}
	//} while (faultyInput);

	//if (mode == "p") Lox::runPrompt();
	//else if(mode == "i") {
	//	std::string filepath;
	//	std::cout << "Enter filepath relative to project root directory:";
	//	std::getline(std::cin, filepath);
	//	Lox::runFile(filepath);
	//}

	Expr rightHandNumberGrouping{ Grouping{Expr(Literal{45.67})} };
	Expr unaryLeftHandNumber{ Unary{Token(-1, {}, "-", TokenType::MINUS), Expr(Literal{123})} };
	Expr binary{ Binary{Expr(unaryLeftHandNumber), Token(-1, {}, "*", TokenType::STAR), Expr(rightHandNumberGrouping)} };
	std::cout << AstPrinterVisitor().print(binary);

	return 0;
}
