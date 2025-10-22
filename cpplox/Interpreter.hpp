#pragma once

#include "Visitor.hpp"
#include "Expr.hpp"
#include <variant>
#include <string>
#include <memory>

class Interpreter : public Visitor {
public:
	void interperet(std::unique_ptr<Expr>&& expr);
	void visitLiteral(Literal& literal) override;
	void visitGrouping(Grouping& grouping) override;
	void visitUnary(Unary& unary) override;
	void visitBinary(Binary& binary) override;
	std::variant<bool, double, std::string, std::monostate> getRollingValue() const { return rollingValue; }
	std::string stringify() const;

private:
	void eval(std::unique_ptr<Expr>&& expr);
	bool isTruthy(std::variant<bool, double, std::string, std::monostate> const& value) const;
	bool isEquey(std::variant<bool, double, std::string, std::monostate> const& left, std::variant<bool, double, std::string, std::monostate> const& right) const;
	void ensureNumeracy(Token const& op, std::variant<bool, double, std::string, std::monostate> const& operand) const;
	void ensureNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const;
	void ensureStringsOrNumeracies(Token const& op, std::variant<bool, double, std::string, std::monostate> const& leftOperand, std::variant<bool, double, std::string, std::monostate> const& rightOperand) const;
	std::string doubleToCleanString(double const& d) const;

	std::variant<bool, double, std::string, std::monostate> rollingValue = std::monostate{};
};