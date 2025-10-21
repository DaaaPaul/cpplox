#pragma once

#include <stdexcept>
#include "Token.hpp"

class LoxRuntimeError : public std::runtime_error {
public:
	LoxRuntimeError(Token const& t, std::string const& message) : std::runtime_error(message), erroneousToken{t} { }
	const Token erroneousToken;
};