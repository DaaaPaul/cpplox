#pragma once

#include <vector>
#include "Token.hpp"
#include "Expr.h"

class Parser {
	private:
	std::vector<Token> tokens;
	int current;

	Expr expression() const;
	Expr equality() const;

	bool match() const;
	bool check() const;
	inline Token advance() const;
	inline bool atEnd() const;
	inline Token peek() const;
	inline Token previous() const;

	public:
	Parser(std::vector<Token>&& tokensIn);
};