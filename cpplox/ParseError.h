#pragma once

#include <stdexcept>

class ParseError : public std::runtime_error {
	using std::runtime_error::runtime_error;
};