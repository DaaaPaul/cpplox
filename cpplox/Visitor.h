#pragma once

#include "Literal.h"
#include "Grouping.h"
#include "Unary.h"
#include "Binary.h"

template<class R> struct Visitor {
	R operator()(const Literal& e) const { return visitLiteral(e); }
	R operator()(const Grouping& e) const { return visitGrouping(e); }
	R operator()(const Unary& e) const { return visitUnary(e); }
	R operator()(const Binary& e) const { return visitBinary(e); }

	virtual R visitLiteral(const Literal&) const = 0;
	virtual R visitGrouping(const Grouping&) const = 0;
	virtual R visitUnary(const Unary&) const = 0;
	virtual R visitBinary(const Binary&) const = 0;
};