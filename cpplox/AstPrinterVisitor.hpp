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
	std::string parenthesize(std::string const& identity, std::initializer_list<Expr> const& exprs) const;
};