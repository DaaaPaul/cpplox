#pragma once

#include "Visitor.h"
#include <unordered_map>
#include <string>

class CheckType : public Visitor {
public:
	void visitLiteral(Literal& l);
	void visitGrouping(Grouping& e);
	void visitUnary(Unary& e);
	void visitBinary(Binary& e);
	void visitExprStmt(ExprStmt& s);
	void visitPrint(Print& s);
	void visitVar(Var& v);
	void visitVariable(Variable& v);
	void visitAssign(Assign& a);
	void visitBlock(Block& b);

	std::unordered_map<std::string, bool> whichType = {
		{"LITERAL", false},
		{"GROUPING", false},
		{"UNARY", false},
		{"BINARY", false},
		{"EXPRSTMT", false},
		{"PRINT", false},
		{"VAR", false},
		{"VARIABLE", false},
		{"ASSIGN", false},
		{"BLOCK", false},
	};
};

