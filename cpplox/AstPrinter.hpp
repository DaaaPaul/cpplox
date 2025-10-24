//#pragma once
//
//#include "Visitor.h"
//#include "Expr.h"
//#include <string>
//#include <memory>
//
//class AstPrinter : public Visitor {
//public:
//	void print(Expr& expr);
//	void visitLiteral(Literal& literal) override;
//	void visitGrouping(Grouping& grouping) override;
//	void visitUnary(Unary& unary) override;
//	void visitBinary(Binary& binary) override;
//
//private:
//	void parenthesize(std::string const& identity, std::initializer_list<std::reference_wrapper<Expr>> const& exprs);
//};