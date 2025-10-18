#pragma once

#include <variant>
#include <memory>
#include <string>
#include "Token.hpp"
#include "Visitor.hpp"

class Expr {
public:
	virtual ~Expr() {}
	virtual void accept(Visitor const& visitor) const = 0;
};

class Literal : public Expr {
public:
	std::variant<bool, double, std::string, std::monostate> value;

	Literal(bool const& b) : value(b) {}
	Literal(double const& d) : value(d) {}
	Literal(std::string const& s) : value(s) {}
	Literal(std::monostate const& m) : value(m) {}
	Literal(std::variant<bool, double, std::string, std::monostate> const& v) : value(v) {}
	void accept(Visitor const& visitor) const override;
};

class Grouping : public Expr {
public:
	std::unique_ptr<Expr> expr;

	Grouping(std::unique_ptr<Expr>&& e) : expr(std::move(e)) {}
	void accept(Visitor const& visitor) const override;
};

class Unary : public Expr {
public:
	Token op;
	std::unique_ptr<Expr> right;

	Unary(Token const& o, std::unique_ptr<Expr>&& r) : op(o), right(std::move(r)) {}
	void accept(Visitor const& visitor) const override;
};

class Binary : public Expr {
public:
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	Binary(std::unique_ptr<Expr>&& l, Token const& o, std::unique_ptr<Expr>&& r) : left(std::move(l)), op(o), right(std::move(r)) {}
	void accept(Visitor const& visitor) const override;
};