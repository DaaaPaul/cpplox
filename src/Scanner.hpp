#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"
#include "TokenType.h"

class Scanner {
	private:
	const static std::unordered_map<std::string, TokenType> keywords;
	std::string source;
	std::vector<Token> tokens;
	int start;
	int next;
	int line;

	public:
	Scanner();
	Scanner(std::string source);

	static bool isDigit(char c);
	static bool isAlpha(char c);
	static bool isAlphaDigit(char c);
	bool atEnd() const;
	char consume();
	char peek() const;
	char peekFar() const;
	bool nextIs(char expected) const;
	void addToken(TokenType type, std::any literal);
	void addToken(TokenType type);
	void stringLiteral();
	void numericLiteral();
	void identifierKeyword();
	void scanToken();
	std::vector<Token> scanTokens();
};

#endif
