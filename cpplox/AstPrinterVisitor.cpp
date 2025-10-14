#include "AstPrinterVisitor.hpp"
#include <any>
#include <iostream>
#include <memory>
#include <initializer_list>

std::string AstPrinterVisitor::print(Expr const& expr) const {
	return expr.accept(*this);
}

std::string AstPrinterVisitor::operator()(const Literal& literal) const {
	if (!literal.value.has_value()) {
		return "nil";
	}
	else {
		if (literal.value.type() == typeid(double)) {
			return std::to_string(std::any_cast<double>(literal.value));
		}
		else if (literal.value.type() == typeid(int)) {
			return std::to_string(static_cast<double>(std::any_cast<int>(literal.value)));
		}
		else if (literal.value.type() == typeid(std::string)) {
			return std::any_cast<std::string>(literal.value);
		} else {
			return std::string("Invalid literal type");
		}
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