#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <any>
#include "TokenType.h"

class Token {
	private:
	int line;
	std::any literal;
	std::string lexeme;
	TokenType type;

	public:
	Token();
	Token(int line, std::any literal, std::string lexeme, TokenType type);
	std::string toString() const;
};

#endif
