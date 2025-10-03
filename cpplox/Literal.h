#pragma once

#include "Expr.h"
#include <any>

struct Literal : Expr {
	const std::any value;
};