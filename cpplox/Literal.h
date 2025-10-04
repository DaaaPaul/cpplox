#pragma once

#include <any>

struct Literal {
	const std::any value;

	Literal(std::any value) : value(std::move(value)) {}
};