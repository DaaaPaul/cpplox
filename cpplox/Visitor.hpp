#pragma once

class Literal;
class Grouping;
class Unary;
class Binary;

class Visitor {
public:
	virtual void visitLiteral(const Literal& l) const = 0;
	virtual void visitGrouping(const Grouping& e) const = 0;
	virtual void visitUnary(const Unary& e) const = 0;
	virtual void visitBinary(const Binary& e) const = 0;
};