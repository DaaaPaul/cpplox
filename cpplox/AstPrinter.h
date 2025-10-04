#pragma once

#include "Visitor.h"
#include "Expr.h"
#include "Token.hpp"
#include <string>

class AstPrinter : public Visitor<std::string> {
public:
	std::string print(Expr expr) {
		return expr.accept(*this);
	}

	std::string visitLiteral(const Literal& literal) const override {
	
	}

	std::string visitGrouping(const Grouping& grouping) const override {
	
	}

	std::string visitUnary(const Unary& unary) const override {
	
	}

	std::string visitBinary(const Binary& binary) const override {

	}
private:
	template<class... Expr>
	std::string parenthesize(std::string name, Expr... exprs) {

	}
};