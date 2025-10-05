#pragma once

#include "Visitor.h"
#include "Expr.h"
#include <string>

class AstPrinterVisitor : public Visitor<std::string> {
public:
	std::string print(const Expr& expr) const;

	std::string visitLiteral(const Literal& literal) const override;

	std::string visitGrouping(const Grouping& grouping) const override;

	std::string visitUnary(const Unary& unary) const override;

	std::string visitBinary(const Binary& binary) const override;

private:
	template<typename... Exprs>
	std::string parenthesize(const std::string identity, const Exprs&... exprs) const;
};