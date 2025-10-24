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
	void accept(Visitor& visitor) { visitor.visitExprStmt(*this); }
};

class Print : public Stmt {
public:
	std::unique_ptr<Expr> expr;

	Print(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) { visitor.visitPrint(*this); }
};