#include "Expr.hpp"

void Literal::accept(Visitor& visitor) const {
	visitor.visitLiteral(*this);
}

void Grouping::accept(Visitor& visitor) const {
	visitor.visitGrouping(*this);
}

void Unary::accept(Visitor& visitor) const {
	visitor.visitUnary(*this);
}

void Binary::accept(Visitor& visitor) const {
	visitor.visitBinary(*this);
}