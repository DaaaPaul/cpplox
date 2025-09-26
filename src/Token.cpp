#include "Token.hpp"

Token::Token():line{-1}, literal{}, lexeme{}, type{TokenType::EMPTY} {}

Token::Token(int line, std::vector<char> literal, std::string lexeme, TokenType type):line{line}, literal{literal}, lexeme{lexeme}, type{type} {}

std::string Token::toString() const {
	return std::to_string(static_cast<int>(type)) + lexeme + std::string(literal.begin(), literal.end());
}
