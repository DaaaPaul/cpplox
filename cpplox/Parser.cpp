//#include "Parser.hpp"
//#include <utility>
//#include <initializer_list>
//
//Parser::Parser(std::vector<Token>&& tokensIn) : tokens(std::move(tokensIn)), current{ 0 } {}
//
//Expr Parser::expression() {
//	return equality();
//}
//
//Expr Parser::equality() {
//	Expr veryFirst(comparison());
//	while (match({ TokenType::EQUAL_EQUAL, TokenType::NOT_EQUAL })) {
//		Token which = previous();
//		Expr aRight(comparison());
//	}
//
//}
//
//Expr Parser::comparison() {
//
//}
//
//bool Parser::match(std::initializer_list<TokenType> types) {
//	bool foundMatch = false;
//
//	for(TokenType const& t : types) {
//		if(check(t)) {
//			advance();
//			foundMatch = true;
//		}
//	}
//
//	return foundMatch;
//}
//
//bool Parser::check(TokenType type) const {
//	if (atEnd()) return false;
//	return peek().getType() == type;
//}
//
//inline Token Parser::advance() {
//	if (!atEnd()) ++current;
//	return previous();
//}
//
//inline bool Parser::atEnd() const {
//	return (current >= tokens.size()) ? true : false;
//}
//
//inline Token Parser::peek() const {
//	return tokens[current];
//}
//
//inline Token Parser::previous() const {
//	return tokens[current - 1];
//}