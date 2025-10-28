#include "CheckType.hpp"

void CheckType::visitLiteral(Literal& l) {
	whichType["LITERAL"] = true;
}

void CheckType::visitGrouping(Grouping& e) {
	whichType["GROUPING"] = true;
}

void CheckType::visitUnary(Unary& e) {
	whichType["UNARY"] = true;
}

void CheckType::visitBinary(Binary& e) {
	whichType["BINARY"] = true;
}

void CheckType::visitExprStmt(ExprStmt& s) {
	whichType["EXPRSTMT"] = true;
}

void CheckType::visitPrint(Print& s) {
	whichType["PRINT"] = true;
}

void CheckType::visitVar(Var& v) {
	whichType["VAR"] = true;
}

void CheckType::visitVariable(Variable& v) {
	whichType["VARIABLE"] = true;
}

void CheckType::visitAssign(Assign& a) {
	whichType["ASSIGN"] = true;
}

void CheckType::visitBlock(Block& b) {
	whichType["BLOCK"] = true;
}

void CheckType::visitIf(If& i) {
	whichType["IF"] = true;
}

void CheckType::visitLogical(Logical& i) {
	whichType["LOGICAL"] = true;
}

void CheckType::visitWhile(While& i) {
	whichType["WHILE"] = true;
}