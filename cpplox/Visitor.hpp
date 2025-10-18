#pragma once

class Literal;
class Grouping;
class Unary;
class Binary;

class Visitor {
public:
	virtual void visitLiteral(const Literal& l) = 0;
	virtual void visitGrouping(const Grouping& e) = 0;
	virtual void visitUnary(const Unary& e) = 0;
	virtual void visitBinary(const Binary& e) = 0;
};