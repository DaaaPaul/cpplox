#pragma once

#include <variant>
#include <memory>
#include <string>
#include "Token.hpp"
#include "Visitor.h"

class Expr {
public:
	virtual ~Expr() {}
	virtual void accept(Visitor& visitor) = 0;
};

class Literal : public Expr {
public:
	std::variant<bool, double, std::string, std::monostate> value;

	Literal(bool const& b) : value(b) {}
	Literal(double const& d) : value(d) {}
	Literal(std::string const& s) : value(s) {}
	Literal(std::monostate const& m) : value(m) {}
	Literal(std::variant<bool, double, std::string, std::monostate> const& v) : value(v) {}
	void accept(Visitor& visitor) override { visitor.visitLiteral(*this); }
};

class Grouping : public Expr {
public:
	std::unique_ptr<Expr> expr;

	Grouping(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitGrouping(*this); }
};

class Unary : public Expr {
public:
	Token op;
	std::unique_ptr<Expr> right;

	Unary(Token const& o, std::unique_ptr<Expr>&& r) : op(o), right(std::move(r)) {}
	void accept(Visitor& visitor) override { visitor.visitUnary(*this); }
};

class Binary : public Expr {
public:
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Binary(std::unique_ptr<Expr>&& l, Token const& o, std::unique_ptr<Expr>&& r) : left(std::move(l)), op(o), right(std::move(r)) {}
	void accept(Visitor& visitor) override { visitor.visitBinary(*this); }
};

class Logical : public Expr {
public:
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Logical(std::unique_ptr<Expr>&& l, Token const& o, std::unique_ptr<Expr>&& r) : left(std::move(l)), op(o), right(std::move(r)) {}
	void accept(Visitor& visitor) override { visitor.visitLogical(*this); }
};

class Variable : public Expr {
public:
	Token identifier;

	Variable(Token const& t) : identifier(t) {}
	void accept(Visitor& visitor) override { visitor.visitVariable(*this); }
};

class Assign : public Expr {
public:
	Token identifier;
	std::unique_ptr<Expr> initializer;

	Assign(Token const& t, std::unique_ptr<Expr>&& e) : identifier(t), initializer(std::move(e)) {}
	void accept(Visitor& visitor) override { visitor.visitAssign(*this); }
};