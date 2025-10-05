#pragma once

#include "Token.hpp"
#include <memory>

struct Expr;

struct Unary {
	Token op;
	std::unique_ptr<Expr> right;

	Unary(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}
};