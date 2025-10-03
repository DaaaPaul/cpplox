#pragma once

#include "Expr.h"
#include "Token.hpp"

struct Binary : Expr {
	const Expr left;
	const Token op;
	const Expr right;
};