#pragma once

#include <variant>
#include <memory>
#include <iostream>
#include "Visitor.h"
#include "Token.hpp"

struct Expr;

struct Grouping {
	std::unique_ptr<Expr> expression;
};

struct Binary {
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;
};

struct Unary {
	Token op;
	std::unique_ptr<Expr> right;
};

struct Literal {
	std::any value;
};

struct Expr {
	std::variant<Grouping, Binary, Unary, Literal> variant;

	template<class R>
	R accept(const Visitor<R>& visitor) const {
		return std::visit(visitor, variant);
	}
};