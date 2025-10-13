#include "Parser.hpp"
#include <utility>

Parser::Parser(std::vector<Token>&& tokensIn) : tokens(std::move(tokensIn)), current{ 0 } {}

Expr Parser::expression() const {

}

Expr Parser::equality() const {

}

bool Parser::match() const {

}

bool Parser::check() const {

}

inline Token Parser::advance() const {

}

inline bool Parser::atEnd() const {

}

inline Token Parser::peek() const {

}

inline Token Parser::previous() const {

}