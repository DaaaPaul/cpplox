#include "Scanner.hpp"
#include "TokenType.h"
#include "Lox.hpp"
#include <iostream>

Scanner::Scanner():source{}, tokens{}, start{0}, current{0}, line{1} {}
Scanner::Scanner(std::string source):source{source}, tokens{}, start{0}, current{0}, line{1} {}

const std::unordered_map<std::string, TokenType> Scanner::keywords = {
	{"nil", TokenType::NIL},
	{"and", TokenType::AND},
	{"or", TokenType::OR},
	{"if", TokenType::IF},
	{"else", TokenType::ELSE},
	{"for", TokenType::FOR},
	{"while", TokenType::WHILE},
	{"true", TokenType::TRUE},
	{"false", TokenType::FALSE},
	{"print", TokenType::PRINT},
	{"var", TokenType::VAR},
	{"fun", TokenType::FUN},
	{"return", TokenType::RETURN},
	{"class", TokenType::CLASS},
	{"super", TokenType::SUPER},
	{"this", TokenType::THIS},
	{"dih", TokenType::DIH}
};

bool Scanner::isDigit(char c) {
	return (c >= '0' && c <= '9');
}

bool Scanner::isAlpha(char c) {
	return ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			(c == '_'));
}

bool Scanner::isAlphaDigit(char c) {
	return isDigit(c) || isAlpha(c);
}

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

char Scanner::peekFar() const {
	if(atEnd()) return '\0';
	else return source[current + 1];
}

bool Scanner::currentIs(char expected) const {
	if(atEnd()) return false;
	else if(source[current] != expected) return false;
	else return true;
}

void Scanner::addToken(TokenType type, std::any literal) {
	tokens.push_back(Token(line, literal, source.substr(start, current - start), type));
}

void Scanner::addToken(TokenType type) {
	addToken(type, nullptr);
}

void Scanner::stringLiteral() {
	while(peek() != '"' && !atEnd()) {
		if(peek() == '\n') ++line;
		consume();
	}
	
	if(peek() == '"') {
		consume();
		addToken(TokenType::STRING_LITERAL, source.substr(start + 1, current - start - 1));
	} else if(atEnd()) {
		Lox::reportError(line, "Unfinished string literal");
	}
}

void Scanner::numericLiteral() {
	while(isDigit(peek()) && !atEnd()) consume();

	if(peek() == '.' && isDigit(peekFar())) {
		consume();
		while(isDigit(peek()) && !atEnd()) consume();
	} 

	addToken(TokenType::NUMERIC_LITERAL, std::stod(source.substr(start, current - start)));
}

void Scanner::identifierKeyword() {
	while(isAlphaDigit(peek()) && !atEnd()) consume();

	std::string lexeme = source.substr(start, current - start);

	addToken((keywords.contains(lexeme)) ? keywords.at(lexeme) : TokenType::IDENTIFIER);
}

void Scanner::blockComment() {
	int leftCount = 1;
	int rightCount = 0;
	
	while(leftCount != rightCount) {
		while(!(peek() == '*' && peekFar() == '/') && 
			  !(peek() == '/' && peekFar() == '*') &&
			  !atEnd()) consume();

		if(peek() == '*' && peekFar() == '/') {
			++rightCount;
			consume(); consume();
		} else if(peek() == '/' && peekFar() == '*') {
			++leftCount;
			consume(); consume();
		} else if(atEnd()) {
			Lox::reportError(line, "Unfinished block comment");
		}
	}
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
			} else if(currentIs('*')) {
				blockComment();
			} else {
				addToken(TokenType::SLASH);
			}
			break;
		case ' ': 
		case '\r':
		case '\t': break;
		case '\n': ++line; break;
		case '"': stringLiteral(); break;
		default: 
			if(isDigit(c)) {
				numericLiteral();
				break;
			}
			if(isAlpha(c)) {
				identifierKeyword();
				break;
			}
			Lox::reportError(line, "Undefined character"); break;
	}
}

std::vector<Token> Scanner::scanTokens() {
	while(!atEnd()) {
		start = current;
		scanToken();
	}

	return tokens;
}
