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
	Expr resolveEqualities(const Expr left);
	Expr comparison();
	Expr resolveComparisons(const Expr left);
	Expr additive();
	Expr resolveAdditives(const Expr left);
	Expr multiplicitive();
	Expr resolveMultiplicitives(const Expr left);
	Expr unary();
	Expr primary();

	bool match(std::initializer_list<TokenType> types);
	bool check(TokenType type) const;
	inline Token advance();
	inline bool atEnd() const;
	inline Token peek() const;
	inline Token previous() const;

	public:
	Parser(std::vector<Token>&& tokensIn);
};