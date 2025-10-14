#include "AstPrinterVisitor.hpp"
#include <iostream>
#include <memory>
#include <initializer_list>

std::string AstPrinterVisitor::print(Expr const& expr) const {
	return expr.accept(*this);
}

std::string AstPrinterVisitor::operator()(const Literal& literal) const {
	if (std::holds_alternative<std::monostate>(literal.value)) {
		return "nil";
	} else if(std::holds_alternative<double>(literal.value)) {
		return std::to_string(std::get<double>(literal.value));
	} else if(std::holds_alternative<std::string>(literal.value)) {
		return std::get<std::string>(literal.value);
	} else {
		return "Literal isn't holding valid type";
	}
}

std::string AstPrinterVisitor::operator()(const Grouping& grouping) const {
	return parenthesize("grouping", { grouping.expression });
}

std::string AstPrinterVisitor::operator()(const Unary& unary) const {
	return parenthesize(unary.op.toLexeme(), { unary.right });
}

std::string AstPrinterVisitor::operator()(const Binary& binary) const {
	return parenthesize(binary.op.toLexeme(), { binary.left, binary.right });
}

std::string AstPrinterVisitor::parenthesize(std::string const& identity, std::initializer_list<Expr> const& exprs) const {
	std::string result = "(" + identity;
	
	for(Expr const& e : exprs) {
		result.append(" " + e.accept(*this));
	}
	
	result.append(")");
	return result;
}