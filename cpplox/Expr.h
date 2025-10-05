#pragma once

#include "Visitor.h"
#include <variant>
#include <memory>
#include <utility>

struct Literal; struct Grouping; struct Unary; struct Binary;

struct Expr {
	std::variant<Literal, Grouping, Unary, Binary> variant;

	template<class T>
	explicit Expr(T&& t) : variant(std::forward<T>(t)) {}

	Expr(const Expr&) = delete;
	Expr& operator=(const Expr&) = delete;

	Expr(Expr&&) = default;
	Expr& operator=(Expr&&) = default;

	template<class R>
	R accept(const Visitor<R>& visitor) const {
		return std::visit(visitor, variant);
	}
};