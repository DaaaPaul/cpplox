#pragma once

#include "Visitor.hpp"
#include "Expr.hpp"
#include <string>
#include <memory>

class AstPrinterVisitor : public Visitor {
public:
	void print(Expr const& expr) const;
	void visitLiteral(const Literal& literal) const override;
	void visitGrouping(const Grouping& grouping) const override;
	void visitUnary(const Unary& unary) const override;
	void visitBinary(const Binary& binary) const override;

private:
	void parenthesize(std::string const& identity, std::initializer_list<std::reference_wrapper<const Expr>> const& exprs) const;
};