#pragma once

#include "Expr.h"

struct Grouping : Expr {
	const Expr expr;
};