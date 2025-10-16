#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <stdexcept>
#include "Token.hpp"
#include "Expr.hpp"
#include "ParseError.h"

class Parser {
	private:
	std::vector<Token> tokens;
	int current;

	std::unique_ptr<Expr> expression();
	std::unique_ptr<Expr> equality();
	std::unique_ptr<Expr> resolveEqualities(std::unique_ptr<Expr> left);
	std::unique_ptr<Expr> comparison();
	std::unique_ptr<Expr> resolveComparisons(std::unique_ptr<Expr> left);
	std::unique_ptr<Expr> additive();
	std::unique_ptr<Expr> resolveAdditives(std::unique_ptr<Expr> left);
	std::unique_ptr<Expr> multiplicitive();
	std::unique_ptr<Expr> resolveMultiplicitives(std::unique_ptr<Expr> left);
	std::unique_ptr<Expr> unary();
	std::unique_ptr<Expr> primary();

	bool match(std::initializer_list<TokenType> types);
	bool check(TokenType type) const;
	void synchronize();
	inline Token advance();
	inline Token consume(TokenType type, std::string const& potentialErrorMessage);
	inline ParseError error(Token const& token, std::string const& message);
	inline bool atEnd() const;
	inline Token peek() const;
	inline Token previous() const;

	public:
	Parser(std::vector<Token>&& tokensIn);
	std::unique_ptr<Expr> parse() noexcept;
};