#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <memory>
#include "Token.hpp"
#include "Expr.h"
#include "ParseError.h"
#include "Stmt.h"
#include "Lox.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    int current;

    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> varDeclaration();
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> printStatement();
    std::unique_ptr<Stmt> expressionStatement();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> comma();
    std::unique_ptr<Expr> resolveCommas(std::unique_ptr<Expr> left);
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> resolveEqualities(std::unique_ptr<Expr> left);
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> resolveComparisons(std::unique_ptr<Expr> left);
    std::unique_ptr<Expr> additive();
    std::unique_ptr<Expr> resolveAdditives(std::unique_ptr<Expr> left);
    std::unique_ptr<Expr> multiplicitive();
    std::unique_ptr<Expr> resolveMultiplicitives(std::unique_ptr<Expr> left);
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type) const;
    void synchronize();
    Token advance() { if (!atEnd()) ++current; return previous(); }
    Token consume(TokenType type, std::string const& msg) { if (check(type)) return advance(); throw error(peek(), msg); }
    ParseError error(Token const& token, std::string const& msg) { Lox::reportError(token, msg); return ParseError(msg); }
    bool atEnd() const { return current >= static_cast<int>(tokens.size() - 1); }
    Token peek() const { return tokens[current]; }
    Token previous() const { return tokens[current - 1]; }

public:
    Parser(std::vector<Token>&& tokensIn);
    std::vector<std::unique_ptr<Stmt>> parse() noexcept;
};