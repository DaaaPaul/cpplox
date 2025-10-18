#include "AstPrinterVisitor.hpp"
#include <iostream>
#include <memory>
#include <initializer_list>

void AstPrinterVisitor::print(Expr& expr) {
	expr.accept(*this);
}

void AstPrinterVisitor::visitLiteral(Literal& literal) {
	if (std::holds_alternative<std::monostate>(literal.value)) {
		std::cout << "nil";
	} else if(std::holds_alternative<double>(literal.value)) {
		std::cout << std::to_string(std::get<double>(literal.value));
	} else if(std::holds_alternative<std::string>(literal.value)) {
		std::cout << std::get<std::string>(literal.value);
	} else {
		std::cout << "Literal isn't holding valid type";
	}
}

void AstPrinterVisitor::visitGrouping(Grouping& grouping) {
	parenthesize("grouping", { *(grouping.expr) });
}

void AstPrinterVisitor::visitUnary(Unary& unary) {
	parenthesize(unary.op.toLexeme(), { *unary.right });
}

void AstPrinterVisitor::visitBinary(Binary& binary) {
	parenthesize(binary.op.toLexeme(), { *binary.left, *binary.right });
}

void AstPrinterVisitor::parenthesize(std::string const& identity, std::initializer_list<std::reference_wrapper<Expr>> const& exprs) {
	std::cout << "(" << identity;

	for (Expr& e : exprs) {
		std::cout << " ";
		e.accept(*this);
	}

	std::cout << ")";
}