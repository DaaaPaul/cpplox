#include "Scanner.hpp"
#include "TokenType.h"
#include "Lox.hpp"

Scanner::Scanner():source{}, tokens{}, start{0}, current{0}, line{0} {}
Scanner::Scanner(std::string source):source{source}, tokens{}, start{0}, current{0}, line{0} {}

bool Scanner::isAtEnd() const {
	return current >= source.size();
}

char Scanner::currentAndIncrement() {
	return source[current++];
}

void Scanner::addToken(TokenType type, std::vector<char> literal) {
	tokens.push_back(Token(line, literal, source.substr(start, current), type));
}

void Scanner::addToken(TokenType type) {
	addToken(type, std::vector<char>{});
}

void Scanner::scanToken() {
	char c = currentAndIncrement();
	switch(c) {
		case '(': addToken(TokenType::LEFT_PARENTHESE); break;
		case ')': addToken(TokenType::RIGHT_PARENTHESE); break;
		case '{': addToken(TokenType::LEFT_BRACE); break;
		case '}': addToken(TokenType::RIGHT_BRACE); break;
		case ',': addToken(TokenType::COMMA); break;
		case '.': addToken(TokenType::DOT); break;
		case '-': addToken(TokenType::MINUS); break;
		case '+': addToken(TokenType::PLUS); break;
		case ';': addToken(TokenType::SEMICOLON); break;
		case '*': addToken(TokenType::STAR); break;
		// MORE
		default: Lox::reportError(line, "Undefined character");
	}
}

std::vector<Token> Scanner::scanTokens() {
	while(!isAtEnd()) {
		start = current;
		scanToken();
	}
	tokens.push_back(Token(line, std::vector<char>{}, std::string{}, TokenType::END_OF_FILE));
}
