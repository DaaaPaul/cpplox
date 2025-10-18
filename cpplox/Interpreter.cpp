#include "Interpreter.hpp"

void Interpreter::visitLiteral(Literal& literal) {
	interpretedValue = literal.value;
}

void Interpreter::visitGrouping(Grouping& grouping) {
	eval(std::move(grouping.expr));
}

void Interpreter::visitUnary(Unary& unary) {

}

void Interpreter::visitBinary(Binary& binary) {

}

void Interpreter::eval(std::unique_ptr<Expr>&& expr) {
	expr->accept(*this);
}