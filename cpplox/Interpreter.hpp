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
	std::variant<bool, double, std::string, std::monostate> getRollingValue() const { return rollingValue; }

private:
	void eval(std::unique_ptr<Expr>&& expr);
	void isTruthy();
	void isEquey(std::variant<bool, double, std::string, std::monostate> const& right);
	void ensureNumeracy(Token const& op, std::variant<bool, double, std::string, std::monostate> const& operand) const;
	void ensureNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const;

	std::variant<bool, double, std::string, std::monostate> rollingValue = std::monostate{};
};