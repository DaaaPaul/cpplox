#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <string>

enum class TokenType {
	// single character
	LEFT_PARENTHESE, RIGHT_PARENTHESE, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// multi character
	NOT, NOT_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESSER, LESSER_EQUAL,

	// literals and identifier
	IDENTIFIER, STRING_LITERAL, NUMERIC_LITERAL,

	// keywords
	NIL, AND, OR, IF, ELSE, FOR, WHILE, TRUE, FALSE, PRINT, VAR, 
	FUN, RETURN, CLASS, SUPER, THIS, DIH,

	// util
	EMPTY, END_OF_FILE
};

inline std::string tokenTypeString(TokenType t) {
	switch(t) {
		case TokenType::LEFT_PARENTHESE:
			return "LEFT_PARENTHESE";
		case TokenType::RIGHT_PARENTHESE:
			return "RIGHT_PARENTHESE";
		case TokenType::LEFT_BRACE:
			return "LEFT_BRACE";
		case TokenType::RIGHT_BRACE:
			return "RIGHT_BRACE";
		case TokenType::COMMA:
			return "COMMA";
		case TokenType::DOT:
			return "DOT";
		case TokenType::MINUS:
			return "MINUS";
		case TokenType::PLUS:
			return "PLUS";
		case TokenType::SEMICOLON:
			return "SEMICOLON";
		case TokenType::SLASH:
            return "SLASH";
        case TokenType::STAR:
            return "STAR";
        case TokenType::NOT:
            return "NOT";
        case TokenType::NOT_EQUAL:
            return "NOT_EQUAL";
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case TokenType::GREATER:
            return "GREATER";
        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case TokenType::LESSER:
            return "LESSER";
        case TokenType::LESSER_EQUAL:
            return "LESSER_EQUAL";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::STRING_LITERAL:
            return "STRING_LITERAL";
        case TokenType::NUMERIC_LITERAL:
            return "NUMERIC_LITERAL";
        case TokenType::NIL:
            return "NIL";
        case TokenType::AND:
            return "AND";
        case TokenType::OR:
            return "OR";
        case TokenType::IF:
            return "IF";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::FOR:
            return "FOR";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::TRUE:
            return "TRUE";
        case TokenType::FALSE:
            return "FALSE";
        case TokenType::PRINT:
            return "PRINT";
        case TokenType::VAR:
            return "VAR";
        case TokenType::FUN:
            return "FUN";
        case TokenType::RETURN:
            return "RETURN";
        case TokenType::CLASS:
            return "CLASS";
        case TokenType::SUPER:
            return "SUPER";
        case TokenType::THIS:
            return "THIS";
        case TokenType::EMPTY:
            return "EMPTY";
        case TokenType::END_OF_FILE:
            return "END_OF_FILE";
		default:
			return "Token type not found";
	}
}

#endif
