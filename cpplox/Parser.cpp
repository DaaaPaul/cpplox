#include "Parser.hpp"
#include "Lox.hpp"
#include "ParseError.h"
#include <utility>
#include <initializer_list>
#include <vector>
#include <tuple>

Parser::Parser(std::vector<Token>&& tokensIn) : tokens(std::move(tokensIn)), current{ 0 } {}

std::unique_ptr<Expr> Parser::parse() noexcept {
	try {
		return expression();
	} catch(ParseError error) {
		return Expr(std::monostate{});
	}
}

std::unique_ptr<Expr> Parser::expression() {
	return equality();
}

std::unique_ptr<Expr> Parser::equality() {
	std::unique_ptr<Expr> firstComparison(comparison());
	return resolveEqualities(std::move(firstComparison));
}

std::unique_ptr<Expr> Parser::resolveEqualities(std::unique_ptr<Expr> left) {
	if (!match({ TokenType::NOT_EQUAL, TokenType::EQUAL_EQUAL })) return left;

	Token op = previous();
	std::unique_ptr<Expr> right = comparison();

	return resolveEqualities(Expr(Binary(left, op, right)));
}

std::unique_ptr<Expr> Parser::comparison() {
	Expr firstAdditive(additive());
	return resolveComparisons(firstAdditive);
}

std::unique_ptr<Expr> Parser::resolveComparisons(std::unique_ptr<Expr> left) {
	if (!match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESSER, TokenType::LESSER_EQUAL })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveComparisons(Expr(Binary(left, op, right)));
}

std::unique_ptr<Expr> Parser::additive() {
	Expr firstMultiplicitive(multiplicitive());
	return resolveAdditives(firstMultiplicitive);
}

std::unique_ptr<Expr> Parser::resolveAdditives(std::unique_ptr<Expr> left) {
	if (!match({ TokenType::PLUS, TokenType::MINUS })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveAdditives(Expr(Binary(left, op, right)));
}

std::unique_ptr<Expr> Parser::multiplicitive() {
	Expr firstUnary(unary());
	return resolveMultiplicitives(firstUnary);
}

std::unique_ptr<Expr> Parser::resolveMultiplicitives(std::unique_ptr<Expr> left) {
	if (!match({ TokenType::STAR, TokenType::SLASH })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveMultiplicitives(Expr(Binary(left, op, right)));
}

std::unique_ptr<Expr> Parser::unary() {
	if (match({ TokenType::NOT, TokenType::MINUS })) {
		Token op = previous();
		Expr right = unary();
		return Expr(Unary(op, right));
	}

	return primary();
}

std::unique_ptr<Expr> Parser::primary() {
	if (match({ TokenType::FALSE })) return Expr(Literal(false));
	if (match({ TokenType::TRUE })) return Expr(Literal(true));
	if (match({ TokenType::NIL })) return Expr(Literal(std::monostate{}));

	if (match({ TokenType::STRING_LITERAL, TokenType::NUMERIC_LITERAL })) return Expr(Literal(previous().getLiteral()));

	if (match({ TokenType::LEFT_PARENTHESE })) {
		Expr expr = expression();
		consume(TokenType::RIGHT_PARENTHESE, "Expected closing ')' after expression");
		return Expr(Grouping(expr));
	}

	throw error(peek(), "Expected expression");
}

bool Parser::match(std::initializer_list<TokenType> types) {
	for(TokenType const& t : types) {
		if(check(t)) {
			advance();
			return true;
		}
	}

	return false;
}

bool Parser::check(TokenType type) const {
	if (atEnd()) return false;
	return peek().getType() == type;
}

void Parser::synchronize() {
	advance();

	while(!atEnd()) {
		if(previous().getType() == TokenType::SEMICOLON) {
			return;
		}

		switch(peek().getType()) {
			case TokenType::CLASS: case TokenType::FOR: case TokenType::FUN: case TokenType::IF: case TokenType::PRINT:
			case TokenType::RETURN: case TokenType::VAR: case TokenType::WHILE: return;
		}

		advance();
	}
}

inline Token Parser::advance() {
	if (!atEnd()) ++current;
	return previous();
}

inline Token Parser::consume(TokenType type, std::string const& potentialErrorMessage) {
	if (check(type)) return advance();
	else throw error(peek(), potentialErrorMessage);
}

inline ParseError Parser::error(Token const& token, std::string const& message) {
	Lox::reportError(token, message);
	return ParseError(message);
}

inline bool Parser::atEnd() const {
	return (current >= tokens.size()) ? true : false;
}

inline Token Parser::peek() const {
	return tokens[current];
}

inline Token Parser::previous() const {
	return tokens[current - 1];
}