#pragma once

#include "Expr.h"
#include "Token.hpp"

struct Unary : Expr {
	const Token op;
	const Expr right;
};