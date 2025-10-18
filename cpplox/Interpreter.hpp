#pragma once

#include "Visitor.hpp"
#include "Expr.hpp"
#include <variant>
#include <string>
#include <memory>

class Interpreter : public Visitor {
public:
	void visitLiteral(Literal& literal) override;
	void visitGrouping(Grouping& grouping) override;
	void visitUnary(Unary& unary) override;
	void visitBinary(Binary& binary) override;
	std::variant<bool, double, std::string, std::monostate> getInterpretedValue() const { return interpretedValue; }

private:
	void eval(std::unique_ptr<Expr>&& expr);

	std::variant<bool, double, std::string, std::monostate> interpretedValue = std::monostate{};
};