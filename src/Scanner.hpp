#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <string>
#include <vector>
#include "Token.hpp"
#include "TokenType.h"

class Scanner {
	private:
	std::string source;
	std::vector<Token> tokens;
	int start;
	int current;
	int line;

	public:
	Scanner();
	Scanner(std::string source);

	bool isAtEnd() const;
	char currentAndIncrement();
	void addToken(TokenType type, std::vector<char> literal);
	void addToken(TokenType type);
	void scanToken();
	std::vector<Token> scanTokens();
};

#endif
