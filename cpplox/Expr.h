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

	template<class R>
	R accept(Visitor<R>& visitor) {
		return std::visit(visitor, variant);
	}
};