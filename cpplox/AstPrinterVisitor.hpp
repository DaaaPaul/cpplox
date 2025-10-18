#pragma once

#include "Visitor.hpp"
#include "Expr.hpp"
#include <string>
#include <memory>

class AstPrinterVisitor : public Visitor {
public:
	void print(Expr const& expr);
	void visitLiteral(const Literal& literal) override;
	void visitGrouping(const Grouping& grouping) override;
	void visitUnary(const Unary& unary) override;
	void visitBinary(const Binary& binary) override;

private:
	void parenthesize(std::string const& identity, std::initializer_list<std::reference_wrapper<const Expr>> const& exprs);
};