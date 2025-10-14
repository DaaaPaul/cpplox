#pragma once

#include <vector>
#include <initializer_list>
#include "Token.hpp"
#include "Expr.h"

class Parser {
	private:
	std::vector<Token> tokens;
	int current;

	Expr expression();
	Expr equality();
	Expr comparison();

	bool match(std::initializer_list<TokenType> types);
	bool check(TokenType type) const;
	inline Token advance();
	inline bool atEnd() const;
	inline Token peek() const;
	inline Token previous() const;

	public:
	Parser(std::vector<Token>&& tokensIn);
};