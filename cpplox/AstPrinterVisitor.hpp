#pragma once

#include "Visitor.h"
#include "Expr.h"
#include <string>
#include <memory>

class AstPrinterVisitor : public Visitor<std::string> {
public:
	std::string print(Expr const& expr) const;
	std::string operator()(const Literal& literal) const override;
	std::string operator()(const Grouping& grouping) const override;
	std::string operator()(const Unary& unary) const override;
	std::string operator()(const Binary& binary) const override;

private:
	template<class... Exprs>
	std::string parenthesize(const std::string identity, const Exprs&... exprs) const;
};