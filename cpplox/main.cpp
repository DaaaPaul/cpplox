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

	
	auto lit2 = std::make_unique<Expr>(Literal(3.0));
	Grouping g(std::move(lit2));
	auto g_ptr = std::make_unique<Expr>(std::move(g));

	auto lit1 = std::make_unique<Expr>(Literal(0.0));
	Token minus_token(1, std::any(), "-", TokenType::MINUS);
	Unary unary_expr(minus_token, std::move(lit1));
	auto unary_ptr = std::make_unique<Expr>(std::move(unary_expr));

	Token star_token(1, std::any(), "*", TokenType::STAR);
	Binary binary_expr(std::move(unary_ptr), star_token, std::move(g_ptr));

	Expr root_expr(std::move(binary_expr));

	std::cout << AstPrinterVisitor().print(root_expr) << std::endl;

	return 0;
}
