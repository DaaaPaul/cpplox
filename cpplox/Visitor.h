#pragma once

struct Expr; struct Literal; struct Grouping; struct Unary; struct Binary;

template<class R> struct Visitor {
	virtual R operator()(const Literal& e) const = 0;
	virtual R operator()(const Grouping& e) const = 0;
	virtual R operator()(const Unary& e) const = 0;
	virtual R operator()(const Binary& e) const = 0;
};