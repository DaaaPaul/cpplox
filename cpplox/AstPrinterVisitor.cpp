#include "AstPrinterVisitor.hpp"

std::string AstPrinterVisitor::print(const Expr& expr) const {
	return expr.accept(*this);
}

std::string AstPrinterVisitor::visitLiteral(const Literal& literal) const {
	if (!literal.value.has_value()) {
		return "nil";
	}
	else {
		if (literal.value.type() == typeid(double)) {
			return std::to_string(std::any_cast<double>(literal.value));
		}
		else if (literal.value.type() == typeid(std::string)) {
			return std::any_cast<std::string>(literal.value);
		}
	}
}

std::string AstPrinterVisitor::visitGrouping(const Grouping& grouping) const {
	return parenthesize("grouping", *grouping.expression);
}

std::string AstPrinterVisitor::visitUnary(const Unary& unary) const {
	return parenthesize(unary.op.toLexeme(), *unary.right);
}

std::string AstPrinterVisitor::visitBinary(const Binary& binary) const {
	return parenthesize(binary.op.toLexeme(), *binary.left, *binary.right);
}

template<typename... Exprs>
std::string AstPrinterVisitor::parenthesize(const std::string identity, const Exprs&... exprs) const {
	std::string result = "(" + identity;
	(result.append(" " + std::string(exprs.accept(*this))), ...);
	result.append(")");
	return result;
}