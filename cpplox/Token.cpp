#include "Token.hpp"
#include "TokenType.h"

Token::Token() :line{ -1 }, literal{ std::monostate{} }, lexeme{""}, type{ TokenType::EMPTY } {}

Token::Token(int line, std::variant<bool, double, std::string, std::monostate> literal, std::string lexeme, TokenType type):line{line}, literal{literal}, lexeme{lexeme}, type{type} {}

std::string Token::toString() const {
	return tokenTypeString(type) + " " + lexeme;
}

std::string Token::toLexeme() const {
	return lexeme;
}