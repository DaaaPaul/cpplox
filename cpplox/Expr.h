	#pragma once

#include <variant>
#include <memory>
#include <iostream>
#include "Visitor.h"
#include "Token.hpp"

struct Expr;

struct Grouping {
	std::unique_ptr<Expr> expression;

	Grouping(Grouping const& g) : expression(std::make_unique<Expr>(*g.expression)) {}
	Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}
};

struct Binary {
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Binary(Binary const& b) : left(std::make_unique<Expr>(*b.left)), op(b.op), right(std::make_unique<Expr>(*b.right)) {}
	Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : left(std::move(left)), op(op), right(std::move(right)) {}
};

struct Unary {
	Token op;
	std::unique_ptr<Expr> right;

	Unary(Unary const& u) : op(u.op), right(std::make_unique<Expr>(*u.right)) {}
	Unary(Token op, std::unique_ptr<Expr> right) : op(op), right(std::move(right)) {}
};

struct Literal {
	std::any value;

	Literal(std::any value) : value(value) {}
};

struct Expr {
	std::variant<Grouping, Binary, Unary, Literal> variant;

	Expr(Expr const& e) : variant(e.variant) {}
	Expr(Expr&& e) noexcept : variant(std::move(e.variant)) {}
	Expr(Grouping const& g) : variant(g) {}
	Expr(Binary const& b) : variant(b) {}
	Expr(Unary const& u) : variant(u) {}
	Expr(Literal const& l) : variant(l) {}

	template<class R>
	R accept(const Visitor<R>& visitor) const {
		return std::visit(visitor, variant);
	}
};