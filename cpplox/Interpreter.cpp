#include "Interpreter.hpp"

void Interpreter::visitLiteral(const Literal& literal) {
	interpretedValue = literal.value;
}

void Interpreter::visitGrouping(const Grouping& grouping) {
	interpretedValue = eval(std::make_unique<Expr>(*grouping.expr));
}

void Interpreter::visitUnary(const Unary& unary) {

}

void Interpreter::visitBinary(const Binary& binary) {

}

std::variant<bool, double, std::string, std::monostate> Interpreter::eval(std::unique_ptr<Expr> expr) {
	expr->accept(*this);
}