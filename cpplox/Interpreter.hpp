#pragma once

#include "Visitor.hpp"
#include "Expr.hpp"
#include <variant>
#include <string>
#include <memory>

class Interpreter : public Visitor {
public:
	void visitLiteral(const Literal& literal) override;
	void visitGrouping(const Grouping& grouping) override;
	void visitUnary(const Unary& unary) override;
	void visitBinary(const Binary& binary) override;
	std::variant<bool, double, std::string, std::monostate> getInterpretedValue() const { return interpretedValue; }

private:
	std::variant<bool, double, std::string, std::monostate> eval(std::unique_ptr<Expr> expr);

	std::variant<bool, double, std::string, std::monostate> interpretedValue;
};