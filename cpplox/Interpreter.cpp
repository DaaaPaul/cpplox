#include "Interpreter.hpp"
#include "LoxRuntimeError.h"

void Interpreter::visitLiteral(Literal& literal) {
	rollingValue = literal.value;
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
			rollingValue = !std::get<bool>(rollingValue); // rollingValue should certainly be bool here
			break;
	}
}

void Interpreter::visitBinary(Binary& binary) {
	eval(std::move(binary.left));
	std::variant<bool, double, std::string, std::monostate> left = rollingValue;
	eval(std::move(binary.right));

	switch(binary.op.getType()) {
		case TokenType::MINUS:

			break;
		case TokenType::SLASH:

			break;
		case TokenType::STAR:

			break;
		case TokenType::PLUS:

			break;
		case TokenType::GREATER_EQUAL:

			break;
		case TokenType::GREATER:

			break;
		case TokenType::LESSER:

			break;
		case TokenType::LESSER_EQUAL:

			break;
		case TokenType::EQUAL_EQUAL:

			break;
		case TokenType::NOT_EQUAL:

			break;
	}
}

void Interpreter::eval(std::unique_ptr<Expr>&& expr) {
	expr->accept(*this);
}

void Interpreter::isTruthy() {
	if (std::holds_alternative<std::monostate>(rollingValue)) rollingValue = false;
	else if (std::holds_alternative<bool>(rollingValue)) rollingValue = rollingValue;
	else rollingValue = true;
}

void Interpreter::isEquey(std::variant<bool, double, std::string, std::monostate> const& right) {
	if (std::holds_alternative<std::monostate>(rollingValue) && std::holds_alternative<std::monostate>(right)) rollingValue = true;
	else if (std::holds_alternative<std::monostate>(rollingValue) || std::holds_alternative<std::monostate>(right)) rollingValue = false;
	rollingValue = (rollingValue == right);
}

void Interpreter::ensureNumeracy(Token const& op, std::variant<bool, double, std::string, std::monostate> const& operand) const {
	if (std::holds_alternative<double>(operand)) return;
	throw LoxRuntimeError(op, "Operand must be a number");
}

void Interpreter::ensureNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const {
	if (std::holds_alternative<double>(leftOperand) && std::holds_alternative<double>(rightOperand)) return;
	throw LoxRuntimeError(op, "Both operands must be numbers");
}