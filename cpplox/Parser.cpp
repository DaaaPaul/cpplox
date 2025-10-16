#include "Parser.hpp"
#include "Lox.hpp"
#include "ParseError.h"
#include <utility>
#include <initializer_list>
#include <vector>
#include <tuple>

Parser::Parser(std::vector<Token>&& tokensIn) : tokens(std::move(tokensIn)), current{ 0 } {}

Expr Parser::expression() {
	return equality();
}

Expr Parser::equality() {
	Expr firstComparison(comparison());
	return resolveEqualities(firstComparison);
}

Expr Parser::resolveEqualities(const Expr left) {
	if (!match({ TokenType::NOT_EQUAL, TokenType::EQUAL_EQUAL })) return left;

	Token op = previous();
	Expr right = comparison();
	
	return resolveEqualities(Expr(Binary(left, op, right)));
}

Expr Parser::comparison() {
	Expr firstAdditive(additive());
	return resolveComparisons(firstAdditive);
}

Expr Parser::resolveComparisons(const Expr left) {
	if (!match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESSER, TokenType::LESSER_EQUAL })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveComparisons(Expr(Binary(left, op, right)));
}

Expr Parser::additive() {
	Expr firstMultiplicitive(multiplicitive());
	return resolveAdditives(firstMultiplicitive);
}

Expr Parser::resolveAdditives(const Expr left) {
	if (!match({ TokenType::PLUS, TokenType::MINUS })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveAdditives(Expr(Binary(left, op, right)));
}

Expr Parser::multiplicitive() {
	Expr firstUnary(unary());
	return resolveMultiplicitives(firstUnary);
}

Expr Parser::resolveMultiplicitives(const Expr left) {
	if (!match({ TokenType::STAR, TokenType::SLASH })) return left;

	Token op = previous();
	Expr right = comparison();

	return resolveAdditives(Expr(Binary(left, op, right)));
}

Expr Parser::unary() {
	if (match({ TokenType::NOT, TokenType::MINUS })) {
		Token op = previous();
		Expr right = unary();
		return Expr(Unary(op, right));
	}

	return primary();
}

Expr Parser::primary() {
	if (match({ TokenType::FALSE })) return Expr(Literal(false));
	if (match({ TokenType::TRUE })) return Expr(Literal(true));
	if (match({ TokenType::NIL })) return Expr(Literal(std::monostate{}));

	if (match({ TokenType::STRING_LITERAL, TokenType::NUMERIC_LITERAL })) return Expr(Literal(previous().getLiteral()));

	if (match({ TokenType::LEFT_PARENTHESE })) {
		Expr expr = expression();
		consume(TokenType::RIGHT_PARENTHESE, "Expected closing ')' after expression");
		return Expr(Grouping(expr));
	}
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