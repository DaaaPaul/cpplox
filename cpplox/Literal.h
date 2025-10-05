#pragma once

#include <any>

struct Literal {
	std::any value;

	Literal(std::any value) : value(std::move(value)) {}
};