#pragma once

#include <memory>
#include "Expr.hpp"

class Stmt {
public:
	virtual ~Stmt() {}
};

class ExprStmt : public Stmt {
public:
	std::unique_ptr<Expr> expr;
};

class Print : public Stmt {
public:
	std::unique_ptr<Expr> expr;
};