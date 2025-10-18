#include "Parser.hpp"
#include "Lox.hpp"
#include "ParseError.h"
#include <memory>

Parser::Parser(std::vector<Token>&& tokensIn)
    : tokens(std::move(tokensIn)), current(0) {
}

std::unique_ptr<Expr> Parser::parse() noexcept {
    try {
        return expression();
    }
    catch (const ParseError&) {
        return nullptr;
    }
}

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> comparisonExpr = comparison();
    return resolveEqualities(std::move(comparisonExpr));
}

std::unique_ptr<Expr> Parser::resolveEqualities(std::unique_ptr<Expr> left) {
    if (!match({ TokenType::NOT_EQUAL, TokenType::EQUAL_EQUAL })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = comparison();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(Binary(std::move(left), op, std::move(right)));
    return resolveEqualities(std::move(binary));
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> left = additive();
    return resolveComparisons(std::move(left));
}

std::unique_ptr<Expr> Parser::resolveComparisons(std::unique_ptr<Expr> left) {
    if (!match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESSER, TokenType::LESSER_EQUAL })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = additive();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(Binary(std::move(left), op, std::move(right)));
    return resolveComparisons(std::move(binary));
}

std::unique_ptr<Expr> Parser::additive() {
    std::unique_ptr<Expr> left = multiplicitive();
    return resolveAdditives(std::move(left));
}

std::unique_ptr<Expr> Parser::resolveAdditives(std::unique_ptr<Expr> left) {
    if (!match({ TokenType::PLUS, TokenType::MINUS })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = multiplicitive();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(Binary(std::move(left), op, std::move(right)));
    return resolveAdditives(std::move(binary));
}

std::unique_ptr<Expr> Parser::multiplicitive() {
    std::unique_ptr<Expr> left = unary();
    return resolveMultiplicitives(std::move(left));
}

std::unique_ptr<Expr> Parser::resolveMultiplicitives(std::unique_ptr<Expr> left) {
    if (!match({ TokenType::STAR, TokenType::SLASH })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(Binary(std::move(left), op, std::move(right)));
    return resolveMultiplicitives(std::move(binary));
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({ TokenType::NOT, TokenType::MINUS })) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        std::unique_ptr<Expr> unary = std::make_unique<Unary>(Unary(op, std::move(right)));
        return unary;
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({ TokenType::FALSE })) return std::make_unique<Literal>(false);
    else if (match({ TokenType::TRUE })) return std::make_unique<Literal>(true);
    else if (match({ TokenType::NIL })) return std::make_unique<Literal>(std::monostate{});
    else if (match({ TokenType::STRING_LITERAL, TokenType::NUMERIC_LITERAL })) return std::make_unique<Literal>(previous().getLiteral());

    if (match({ TokenType::LEFT_PARENTHESE })) {
        std::unique_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PARENTHESE, "Expected ')' after expression.");
        std::unique_ptr<Expr> grouping = std::make_unique<Grouping>(Grouping(std::move(expr)));
        return grouping;
    }

    throw error(peek(), "Expected expression.");
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType t : types) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (atEnd()) return false;
    return peek().getType() == type;
}

void Parser::synchronize() {
    advance();
    while (!atEnd()) {
        if (previous().getType() == TokenType::SEMICOLON) return;
        switch (peek().getType()) {
        case TokenType::CLASS: case TokenType::FUN: case TokenType::VAR:
        case TokenType::FOR: case TokenType::IF: case TokenType::WHILE:
        case TokenType::PRINT: case TokenType::RETURN:
            return;
        }
        advance();
    }
}

inline Token Parser::advance() {
    if (!atEnd()) ++current;
    return previous();
}

inline Token Parser::consume(TokenType type, std::string const& msg) {
    if (check(type)) return advance();
    throw error(peek(), msg);
}

inline ParseError Parser::error(Token const& token, std::string const& msg) {
    Lox::reportError(token, msg);
    return ParseError(msg);
}

inline bool Parser::atEnd() const {
    return current >= static_cast<int>(tokens.size());
}

inline Token Parser::peek() const {
    return tokens[current];
}

inline Token Parser::previous() const {
    return tokens[current - 1];
}