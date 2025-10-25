#include "Interpreter.hpp"
#include "LoxRuntimeError.h"
#include "Lox.hpp"
#include "Stmt.h"
#include <cmath>
#include <iostream>

void Interpreter::interperet(std::vector<std::unique_ptr<Stmt>>&& stmts) noexcept {
	try {
		for(std::unique_ptr<Stmt>& s : stmts) {
			execute(std::move(s));
		}
	} catch(const LoxRuntimeError& error) {
		Lox::reportRuntimeError(error);
	}
}

std::string Interpreter::stringify() const {
	if (std::holds_alternative<std::monostate>(rollingValue)) return "nil";
	else if (std::holds_alternative<bool>(rollingValue)) return ((std::get<bool>(rollingValue)) ? "true" : "false");
	else if (std::holds_alternative<std::string>(rollingValue)) return std::get<std::string>(rollingValue);
	else return doubleToCleanString(std::get<double>(rollingValue));
}

void Interpreter::visitLiteral(Literal& literal) {
	rollingValue = literal.value;
}

void Interpreter::visitGrouping(Grouping& grouping) {
	eval(std::move(grouping.expr));
}

void Interpreter::visitUnary(Unary& unary) {
	const Token op = unary.op;
	eval(std::move(unary.right));
	
	switch(unary.op.getType()) {
		case TokenType::MINUS:
			if (std::holds_alternative<double>(rollingValue)) {
				rollingValue = std::get<double>(rollingValue) * (-1.0);
			} else if (std::holds_alternative<bool>(rollingValue)) {
				rollingValue = !std::get<bool>(rollingValue);
			} else {
				throw LoxRuntimeError(op, "Negated operand must be a number or boolean");
			}
			break;
		case TokenType::NOT:
			rollingValue = !isTruthy(rollingValue);
			break;
	}
}

void Interpreter::visitBinary(Binary& binary) {
	const Token op = binary.op;
	eval(std::move(binary.left));
	std::variant<bool, double, std::string, std::monostate> left = rollingValue;
	eval(std::move(binary.right));

	switch(binary.op.getType()) {
		case TokenType::PLUS:
			if (std::holds_alternative<double>(left) && std::holds_alternative<double>(rollingValue)) {
				rollingValue = std::get<double>(left) + std::get<double>(rollingValue);
			} else if(std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(rollingValue)) {
				rollingValue = std::get<std::string>(left) + std::get<std::string>(rollingValue);
			} else if ((std::holds_alternative<std::string>(left) && std::holds_alternative<double>(rollingValue))) {
				rollingValue = std::get<std::string>(left) + doubleToCleanString(std::get<double>(rollingValue));
			} else if ((std::holds_alternative<double>(left) && std::holds_alternative<std::string>(rollingValue))) {
				rollingValue = doubleToCleanString(std::get<double>(left)) + std::get<std::string>(rollingValue);
			} else {
				throw LoxRuntimeError(op, "Added operands must be numbers or strings");
			}
			break;
		case TokenType::MINUS:
			ensureNumeracies(op, left, rollingValue);
			rollingValue = std::get<double>(left) - std::get<double>(rollingValue);
			break;
		case TokenType::STAR:
			ensureNumeracies(op, left, rollingValue);
			rollingValue = std::get<double>(left) * std::get<double>(rollingValue);
			break;
		case TokenType::SLASH:
			ensureNumeracies(op, left, rollingValue);
			if(!(std::get<double>(rollingValue) == 0.0)) rollingValue = std::get<double>(left) / std::get<double>(rollingValue);
			else throw LoxRuntimeError(op, "Divison by zero is undefined");
			break;
		case TokenType::GREATER_EQUAL:
			ensureStringsOrNumeracies(op, left, rollingValue);
			rollingValue = left >= rollingValue;
			break;
		case TokenType::GREATER:
			ensureStringsOrNumeracies(op, left, rollingValue);
			rollingValue = left > rollingValue;
			break;
		case TokenType::LESSER:
			ensureStringsOrNumeracies(op, left, rollingValue);
			rollingValue = left < rollingValue;
			break;
		case TokenType::LESSER_EQUAL:
			ensureStringsOrNumeracies(op, left, rollingValue);
			rollingValue = left <= rollingValue;
			break;
		case TokenType::EQUAL_EQUAL:
			rollingValue = isEquey(left, rollingValue);
			break;
		case TokenType::NOT_EQUAL:
			rollingValue = !isEquey(left, rollingValue);
			break;
	}
}

void Interpreter::visitExprStmt(ExprStmt& exprStmt) {
	eval(std::move(exprStmt.expr));
}

void Interpreter::visitPrint(Print& print) {
	eval(std::move(print.expr));
	std::cout << stringify() << '\n';
}

void Interpreter::visitVar(Var& v) {
	std::variant<bool, double, std::string, std::monostate> value = std::monostate{};

	if(v.initializer) {
		eval(std::move(v.initializer));
		value = rollingValue;
	}

	environment.define(v.name.toLexeme(), value);
}

void Interpreter::visitVariable(Variable& v) {
	rollingValue = environment.get(v.identifier);
}

void Interpreter::visitAssign(Assign& a) {
	eval(std::move(a.initializer));
	environment.assign(a.identifier, rollingValue);
}

void Interpreter::visitBlock(Block& b) {
	executeBlock(std::move(b.innerStatements), environment);
}

void Interpreter::eval(std::unique_ptr<Expr>&& expr) {
	expr->accept(*this);
}

void Interpreter::execute(std::unique_ptr<Stmt>&& stmt) {
	stmt->accept(*this);
}

void Interpreter::executeBlock(std::vector<std::unique_ptr<Stmt>>&& block, Environment inner) {
	Environment previous = environment;

	try {
		environment = inner;
		environment.setEnclosing(previous);

		for(std::unique_ptr<Stmt>& stmt : block) {
			execute(std::move(stmt));
		}
	} catch(LoxRuntimeError const& e) {
		environment = previous;
		throw;
	}
}

bool Interpreter::isTruthy(std::variant<bool, double, std::string, std::monostate> const& value) const {
	if (std::holds_alternative<std::monostate>(value)) return false;
	else if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
	else return true;
}

bool Interpreter::isEquey(std::variant<bool, double, std::string, std::monostate> const& left, std::variant<bool, double, std::string, std::monostate> const& right) const {
	if (std::holds_alternative<std::monostate>(left) && std::holds_alternative<std::monostate>(right)) return true;
	else if (std::holds_alternative<std::monostate>(left) || std::holds_alternative<std::monostate>(right)) return false;
	else return left == right;
}

void Interpreter::ensureNumeracy(Token const& op, std::variant<bool, double, std::string, std::monostate> const& operand) const {
	if (std::holds_alternative<double>(operand)) return;
	else throw LoxRuntimeError(op, "Operand must be a number");
}

void Interpreter::ensureNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const {
	if (std::holds_alternative<double>(leftOperand) && std::holds_alternative<double>(rightOperand)) return;
	else throw LoxRuntimeError(op, "Both operands must be numbers");
}

void Interpreter::ensureStringsOrNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const {
	if (std::holds_alternative<double>(leftOperand) && std::holds_alternative<double>(rightOperand)) return;
	else if (std::holds_alternative<std::string>(leftOperand) && std::holds_alternative<std::string>(rightOperand)) return;
	else throw LoxRuntimeError(op, "Both operands must be either numbers or strings");
}

std::string Interpreter::doubleToCleanString(double const& d) const {
	std::string number = std::to_string(d);

	double integralPart = -1.0;
	double decimalPart = -1.0;
	decimalPart = std::modf(d, &integralPart);

	if (decimalPart == 0.0) {
		number = std::to_string(static_cast<int>(integralPart));
	}

	return number;
}