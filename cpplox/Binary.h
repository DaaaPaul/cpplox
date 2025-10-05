#pragma once

#include "Token.hpp"
#include <memory>

struct Expr;

struct Binary {
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}
};