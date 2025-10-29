#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include "Expr.h"
#include "Visitor.h"

class Stmt {
public:
	virtual ~Stmt() {}
	virtual void accept(Visitor& visitor) = 0;
	virtual std::unique_ptr<Stmt> returnCopy() const = 0;
};

class ExprStmt : public Stmt {
public:
	std::unique_ptr<Expr> expr;

	ExprStmt(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitExprStmt(*this); }
	std::unique_ptr<Stmt> returnCopy() const override { return std::make_unique<ExprStmt>((expr) ? expr->returnCopy() : nullptr); }
};

class Print : public Stmt {
public:
	std::unique_ptr<Expr> expr;

	Print(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitPrint(*this); }
	std::unique_ptr<Stmt> returnCopy() const override { return std::make_unique<Print>((expr) ? expr->returnCopy() : nullptr); }
};

class Var : public Stmt {
public:
	Token name;
	std::unique_ptr<Expr> initializer;

	Var(Token const& n, std::unique_ptr<Expr>&& e) : name(n), initializer(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitVar(*this); }
	std::unique_ptr<Stmt> returnCopy() const override { return std::make_unique<Var>(name, (initializer) ? initializer->returnCopy() : nullptr); }
};

class Block : public Stmt {
public:
	std::vector<std::unique_ptr<Stmt>> innerStatements;

	Block(std::vector<std::unique_ptr<Stmt>>&& s) : innerStatements(std::move(s)) {}
	void accept(Visitor& visitor) override { visitor.visitBlock(*this); }
	std::unique_ptr<Stmt> returnCopy() const override {
		std::vector<std::unique_ptr<Stmt>> theBlockInnardsBack;

		for(std::unique_ptr<Stmt> const& s : innerStatements) {
			theBlockInnardsBack.push_back((s) ? s->returnCopy() : nullptr);
		}

		return std::make_unique<Block>(std::move(theBlockInnardsBack));
	}
};

class If : public Stmt {
public:
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> thenThis;
	std::unique_ptr<Stmt> elseThis;

	If(std::unique_ptr<Expr>&& c, std::unique_ptr<Stmt>&& t, std::unique_ptr<Stmt>&& e) : condition(std::move(c)), thenThis(std::move(t)), elseThis(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitIf(*this); }
	std::unique_ptr<Stmt> returnCopy() const override { return std::make_unique<If>((condition) ? condition->returnCopy() : nullptr, (thenThis) ? thenThis->returnCopy() : nullptr, (elseThis) ? elseThis->returnCopy() : nullptr); }
};

class While : public Stmt {
public:
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> repeated;

	While(std::unique_ptr<Expr>&& c, std::unique_ptr<Stmt>&& r) : condition(std::move(c)), repeated(std::move(r)) {}
	void accept(Visitor& visitor) override { visitor.visitWhile(*this); }
	std::unique_ptr<Stmt> returnCopy() const override { return std::make_unique<While>((condition) ? condition->returnCopy() : nullptr, (repeated) ? repeated->returnCopy() : nullptr); }
};