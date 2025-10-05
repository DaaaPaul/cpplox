#pragma once

#include <memory>

struct Expr;

struct Grouping {
	std::unique_ptr<Expr> expression;

	Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}
};