#include "Interpreter.hpp"

void Interpreter::visitLiteral(Literal& literal) {
	interpretedValue = literal.value;
}

void Interpreter::visitGrouping(Grouping& grouping) {
	eval(std::move(grouping.expr));
}

void Interpreter::visitUnary(Unary& unary) {
	eval(std::move(unary.right));
	
	switch(unary.op.getType()) {
		case TokenType::MINUS:

			break;
		case TokenType::NOT:
			isTruthy();
			interpretedValue = !std::get<bool>(interpretedValue);
			break;
	}
}

void Interpreter::visitBinary(Binary& binary) {
	eval(std::move(binary.left));
	std::variant<bool, double, std::string, std::monostate> left = interpretedValue;
	eval(std::move(binary.right));

	switch(binary.op.getType()) {
		case TokenType::MINUS:

			break;
		case TokenType::SLASH:

			break;
		case TokenType::STAR:

			break;
	}
}

void Interpreter::eval(std::unique_ptr<Expr>&& expr) {
	expr->accept(*this);
}

void Interpreter::isTruthy() {
	if (std::holds_alternative<std::monostate>(interpretedValue)) interpretedValue = false;
	else if (std::holds_alternative<bool>(interpretedValue)) interpretedValue = interpretedValue;
	else interpretedValue = true;
}