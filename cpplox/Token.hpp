#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <variant>
#include "TokenType.h"

class Token {
	private:
	int line;
	std::variant<bool, double, std::string, std::monostate> literal;
	std::string lexeme;
	TokenType type;

	public:
	Token();
	Token(int line, std::variant<bool, double, std::string, std::monostate> literal, std::string lexeme, TokenType type);
	std::string toString() const;
	std::string toLexeme() const;
	TokenType getType() const { return type; }
	std::variant<bool, double, std::string, std::monostate> getLiteral() const { return literal; }
	int getLine() const { return line; }
};

#endif
