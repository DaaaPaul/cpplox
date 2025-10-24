#pragma once

#include <memory>
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