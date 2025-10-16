#include "AstPrinterVisitor.hpp"
#include <iostream>
#include <memory>
#include <initializer_list>

void AstPrinterVisitor::print(Expr const& expr) const {
	expr.accept(*this);
}

void AstPrinterVisitor::visitLiteral(const Literal& literal) const {
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

void AstPrinterVisitor::visitGrouping(const Grouping& grouping) const {
	parenthesize("grouping", { *(grouping.expr) });
}

void AstPrinterVisitor::visitUnary(const Unary& unary) const {
	parenthesize(unary.op.toLexeme(), { *unary.right });
}

void AstPrinterVisitor::visitBinary(const Binary& binary) const {
	parenthesize(binary.op.toLexeme(), { *binary.left, *binary.right });
}

void AstPrinterVisitor::parenthesize(std::string const& identity, std::initializer_list<std::reference_wrapper<const Expr>> const& exprs) const {
	std::cout << "(" << identity;

	for (Expr const& e : exprs) {
		std::cout << " ";
		e.accept(*this);
	}

	std::cout << ")";
}