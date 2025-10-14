#pragma once

#include <variant>
#include <memory>
#include <iostream>
#include "Visitor.h"
#include "Token.hpp"

struct Expr;

struct Grouping {
	Expr const& expression;
};

struct Binary {
	Expr const& left;
	Token op;
	Expr const& right;
};

struct Unary {
	Token op;
	Expr const& right;
};

struct Literal {
	const std::variant<bool, double, std::string, std::monostate> value;
};

struct Expr {
	const std::variant<Grouping, Binary, Unary, Literal> variant;

	template<class R>
	R accept(const Visitor<R>& visitor) const {
		return std::visit(visitor, variant);
	}
};