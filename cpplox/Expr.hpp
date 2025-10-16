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

	void accept(Visitor const& visitor) const override;
};

class Grouping : public Expr {
public:
	std::unique_ptr<Expr> expr;

	void accept(Visitor const& visitor) const override;
};

class Unary : public Expr {
public:
	Token op;
	std::unique_ptr<Expr> right;

	void accept(Visitor const& visitor) const override;
};

class Binary : public Expr {
public:
	std::unique_ptr<Expr> left;
	Token op;
	std::unique_ptr<Expr> right;

	void accept(Visitor const& visitor) const override;
};