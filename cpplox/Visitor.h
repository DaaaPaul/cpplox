#pragma once

class Literal;
class Grouping;
class Unary;
class Binary;
class ExprStmt;
class Print;

class Visitor {
public:
	virtual void visitLiteral(Literal& l) = 0;
	virtual void visitGrouping(Grouping& e) = 0;
	virtual void visitUnary(Unary& e) = 0;
	virtual void visitBinary(Binary& e) = 0;
	virtual void visitExprStmt(ExprStmt& s) = 0;
	virtual void visitPrint(Print& s) = 0;
};