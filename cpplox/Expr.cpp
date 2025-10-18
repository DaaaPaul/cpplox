#include "Expr.hpp"

void Literal::accept(Visitor& visitor) {
	visitor.visitLiteral(*this);
}

void Grouping::accept(Visitor& visitor) {
	visitor.visitGrouping(*this);
}

void Unary::accept(Visitor& visitor) {
	visitor.visitUnary(*this);
}

void Binary::accept(Visitor& visitor) {
	visitor.visitBinary(*this);
}