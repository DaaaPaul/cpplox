#pragma once

#include "Token.hpp"
#include <memory>

struct Expr;

struct Unary {
	const Token op;
	const std::unique_ptr<Expr> right;

	Unary(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}
};