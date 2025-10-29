#include "Parser.hpp"
#include "Lox.hpp"
#include "ParseError.h"
#include "Stmt.h"
#include <memory>
#include <vector>
#include <iostream>

Parser::Parser(std::vector<Token>&& tokensIn)
    : tokens(std::move(tokensIn)), current(0) {
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() noexcept {
    std::vector<std::unique_ptr<Stmt>> statements;

    while(!atEnd()) {
        statements.push_back(declaration());
    }

    return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
    try {
        if (match({ TokenType::VAR })) return varDeclaration();
        else return statement();
    } catch(ParseError const& e) {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
    Token identifier = consume(TokenType::IDENTIFIER, "Expected variable name");

    std::unique_ptr<Expr> initializer = nullptr;
    if (match({ TokenType::EQUAL })) initializer = expression();

    consume(TokenType::SEMICOLON, "Expected \";\" after variable declaration");
    return std::make_unique<Var>(identifier, std::move(initializer));
}

std::unique_ptr<Stmt> Parser::statement() {
    if (match({ TokenType::PRINT })) return printStatement();
    else if (match({ TokenType::LEFT_BRACE })) return std::make_unique<Block>(block());
    else if (match({ TokenType::IF })) return ifStatement();
    else if (match({ TokenType::WHILE })) return whileStatement();
    else if (match({ TokenType::FOR })) return forStatement();
    else return expressionStatement();
}

std::vector<std::unique_ptr<Stmt>> Parser::block() {
    std::vector<std::unique_ptr<Stmt>> statements;

    while(!check(TokenType::RIGHT_BRACE) && !atEnd()) {
        statements.push_back(declaration());
    }

    consume(TokenType::RIGHT_BRACE, "Expected \"}\" after block starting with \"{\"");
    return statements;
}

std::unique_ptr<Stmt> Parser::printStatement() {
    std::unique_ptr<Expr> toPrint = expression();
    consume(TokenType::SEMICOLON, "Expected \";\" after expression");
    return std::make_unique<Print>(std::move(toPrint));
}

std::unique_ptr<Stmt> Parser::ifStatement() {
    consume(TokenType::LEFT_PARENTHESE, "Expected \"(\" after if");
    std::unique_ptr<Expr> condition = expression();
    consume(TokenType::RIGHT_PARENTHESE, "Expected closing \")\" after if");
    std::unique_ptr<Stmt> thenBranch = statement();

    std::unique_ptr<Stmt> elseBranch = nullptr;
    if (match( {TokenType::ELSE} )) {
        elseBranch = statement();
    }

    return std::make_unique<If>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
}

std::unique_ptr<Stmt> Parser::whileStatement() {
    consume(TokenType::LEFT_PARENTHESE, "Expected \"(\" after while");
    std::unique_ptr<Expr> condition = expression();
    consume(TokenType::RIGHT_PARENTHESE, "Expected closing \")\" after while");
    std::unique_ptr<Stmt> repeatThis = statement();

    return std::make_unique<While>(std::move(condition), std::move(repeatThis));
}

std::unique_ptr<Stmt> Parser::forStatement() {
    consume(TokenType::LEFT_PARENTHESE, "Expected \"(\" after for");

    std::unique_ptr<Stmt> initializer = nullptr;
    if (match({ TokenType::SEMICOLON }));
    else if (match({ TokenType::VAR })) initializer = varDeclaration(); 
    else initializer = expressionStatement();

    std::unique_ptr<Expr> condition = std::make_unique<Literal>(true);
    if (!check(TokenType::SEMICOLON)) {
        condition = expression();
    }
    consume(TokenType::SEMICOLON, "Expected \";\" after for loop condition");

    std::unique_ptr<Expr> crement = nullptr;
    if (!check(TokenType::RIGHT_PARENTHESE)) {
        crement = expression();
    }
    consume(TokenType::RIGHT_PARENTHESE, "Expected \")\" after for loop crement");

    std::unique_ptr<Stmt> repeatedStatement = statement();

    // begin converting our "raw info" to while AST node
    std::vector<std::unique_ptr<Stmt>> innerStatements;
    innerStatements.push_back(std::move(repeatedStatement));
    innerStatements.push_back(std::make_unique<ExprStmt>(std::move(crement)));
    std::unique_ptr<Stmt> whileBody = std::make_unique<Block>(std::move(innerStatements));

    std::unique_ptr<Stmt> whileLoop = std::make_unique<While>(std::move(condition), std::move(whileBody));
    std::vector<std::unique_ptr<Stmt>> theFinalStatements;
    theFinalStatements.push_back(std::move(initializer));
    theFinalStatements.push_back(std::move(whileLoop));

    return std::make_unique<Block>(std::move(theFinalStatements));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    std::unique_ptr<Expr> expr = expression();
    consume(TokenType::SEMICOLON, "Expected \";\" after expression");
    return std::make_unique<ExprStmt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::expression() {
    return comma();
}

std::unique_ptr<Expr> Parser::comma() {
    std::unique_ptr<Expr> assignExpr = assignment();
    return resolveCommas(std::move(assignExpr));
}

std::unique_ptr<Expr> Parser::resolveCommas(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::COMMA })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = assignment();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(std::move(left), op, std::move(right));
    return resolveCommas(std::move(binary));
}

std::unique_ptr<Expr> Parser::assignment() {
    std::unique_ptr<Expr> expr = logical();

    if(match( {TokenType::EQUAL} )) {
        const Token equals = previous();
        std::unique_ptr<Expr> initializer = assignment();

        try {
            const Token identifier = (dynamic_cast<Variable&>(*expr)).identifier;
            return std::make_unique<Assign>(identifier, std::move(initializer));
        } catch(std::bad_cast const& e) {
            error(equals, "Assignment must be to a valid variable");
        }
    }

    return expr;
}

std::unique_ptr<Expr> Parser::logical() {
    std::unique_ptr expr = equality();
    return resolveLogicals(std::move(expr));
}

std::unique_ptr<Expr> Parser::resolveLogicals(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::AND, TokenType::OR })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = equality();
    std::unique_ptr<Expr> logical = std::make_unique<Logical>(std::move(left), op, std::move(right));
    return resolveLogicals(std::move(logical));
}


std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> comparisonExpr = comparison();
    return resolveEqualities(std::move(comparisonExpr));
}

std::unique_ptr<Expr> Parser::resolveEqualities(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::NOT_EQUAL, TokenType::EQUAL_EQUAL })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = comparison();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(std::move(left), op, std::move(right));
    return resolveEqualities(std::move(binary));
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> additiveExpr = additive();
    return resolveComparisons(std::move(additiveExpr));
}

std::unique_ptr<Expr> Parser::resolveComparisons(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESSER, TokenType::LESSER_EQUAL })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = additive();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(std::move(left), op, std::move(right));
    return resolveComparisons(std::move(binary));
}

std::unique_ptr<Expr> Parser::additive() {
    std::unique_ptr<Expr> multiplicitiveExpr = multiplicitive();
    return resolveAdditives(std::move(multiplicitiveExpr));
}

std::unique_ptr<Expr> Parser::resolveAdditives(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::PLUS, TokenType::MINUS })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = multiplicitive();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(std::move(left), op, std::move(right));
    return resolveAdditives(std::move(binary));
}

std::unique_ptr<Expr> Parser::multiplicitive() {
    std::unique_ptr<Expr> unaryExpr = unary();
    return resolveMultiplicitives(std::move(unaryExpr));
}

std::unique_ptr<Expr> Parser::resolveMultiplicitives(std::unique_ptr<Expr>&& left) {
    if (!match({ TokenType::STAR, TokenType::SLASH, TokenType::PERCENT })) return left;

    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    std::unique_ptr<Expr> binary = std::make_unique<Binary>(std::move(left), op, std::move(right));
    return resolveMultiplicitives(std::move(binary));
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({ TokenType::NOT, TokenType::MINUS })) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        std::unique_ptr<Expr> unary = std::make_unique<Unary>(op, std::move(right));
        return unary;
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({ TokenType::FALSE })) return std::make_unique<Literal>(false);
    else if (match({ TokenType::TRUE })) return std::make_unique<Literal>(true);
    else if (match({ TokenType::NIL })) return std::make_unique<Literal>(std::monostate{});
    else if (match({ TokenType::STRING_LITERAL, TokenType::NUMERIC_LITERAL })) return std::make_unique<Literal>(previous().getLiteral());
    else if (match({ TokenType::IDENTIFIER })) return std::make_unique<Variable>(previous());
    else if (match({ TokenType::LEFT_PARENTHESE })) {
        std::unique_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PARENTHESE, "Expected ')' after expression.");
        std::unique_ptr<Expr> grouping = std::make_unique<Grouping>(std::move(expr));
        return grouping;
    }

    throw error(peek(), "Expected expression");
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