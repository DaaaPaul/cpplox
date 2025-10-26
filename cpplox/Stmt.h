#pragma once

#include <memory>
#include <vector>
#include "Expr.h"
#include "Visitor.h"

class Stmt {
public:
	virtual ~Stmt() {}
	virtual void accept(Visitor& visitor) = 0;
};

class ExprStmt : public Stmt {
public:
	std::unique_ptr<Expr> expr;

	ExprStmt(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitExprStmt(*this); }
};

class Print : public Stmt {
public:
	std::unique_ptr<Expr> expr;

	Print(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitPrint(*this); }
};

class Var : public Stmt {
public:
	Token name;
	std::unique_ptr<Expr> initializer;

	Var(Token const& n, std::unique_ptr<Expr>&& e) : name(n), initializer(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitVar(*this); }
};

class Block : public Stmt {
public:
	std::vector<std::unique_ptr<Stmt>> innerStatements;

	Block(std::vector<std::unique_ptr<Stmt>>&& s) : innerStatements(std::move(s)) {}
	void accept(Visitor& visitor) override { visitor.visitBlock(*this); }
};

class If : public Stmt {
public:
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> thenThis;
	std::unique_ptr<Stmt> elseThis;

	If(std::unique_ptr<Expr>&& c, std::unique_ptr<Stmt>&& t, std::unique_ptr<Stmt>&& e) : condition(std::move(c)), thenThis(std::move(t)), elseThis(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitIf(*this); }
};