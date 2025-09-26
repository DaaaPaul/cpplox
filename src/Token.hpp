#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <vector>
#include "TokenType.h"

class Token {
	private:
	int line;
	std::vector<char> literal;
	std::string lexeme;
	TokenType type;

	public:
	Token();
	Token(int line, std::vector<char> literal, std::string lexeme, TokenType type);
	std::string toString() const;
};

#endif
