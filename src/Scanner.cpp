#include "Scanner.hpp"
#include "TokenType.h"
#include "Lox.hpp"

Scanner::Scanner():source{}, tokens{}, start{0}, current{0}, line{0} {}
Scanner::Scanner(std::string source):source{source}, tokens{}, start{0}, current{0}, line{0} {}

bool Scanner::atEnd() const {
	return current >= source.size();
}

char Scanner::consume() {
	return source[current++];
}

char Scanner::peek() const {
	if(atEnd()) return '\0';
	else return source[current];
}

bool Scanner::currentIs(char expected) const {
	if(atEnd()) return false;
	else if(source[current] != expected) return false;
	else return true;
}

void Scanner::addToken(TokenType type, std::vector<char> literal) {
	tokens.push_back(Token(line, literal, source.substr(start, current), type));
}

void Scanner::addToken(TokenType type) {
	addToken(type, std::vector<char>{});
}

void Scanner::scanToken() {
	char c = consume();
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
		case '!': (currentIs('=')) ? addToken(TokenType::NOT_EQUAL) : addToken(TokenType::NOT); break;
		case '=': (currentIs('=')) ? addToken(TokenType::EQUAL_EQUAL) : addToken(TokenType::EQUAL); break;
		case '>': (currentIs('=')) ? addToken(TokenType::GREATER_EQUAL) : addToken(TokenType::GREATER); break;
		case '<': (currentIs('=')) ? addToken(TokenType::LESSER_EQUAL) : addToken(TokenType::LESSER); break;
		case '/': 
			if(currentIs('/')) {
				while((peek() != '\n') && (!atEnd())) consume();
			} else {
				addToken(TokenType::SLASH);
			}
			break;
		case ' ':
		case '\r':
		case '\t': break;
		case '\n': ++line; break;
		default: Lox::reportError(line, "Undefined character"); break;
	}
}

std::vector<Token> Scanner::scanTokens() {
	while(!atEnd()) {
		start = current;
		scanToken();
	}
	tokens.push_back(Token(line, std::vector<char>{}, std::string{}, TokenType::END_OF_FILE));
}
