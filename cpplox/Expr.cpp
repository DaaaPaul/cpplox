#include "Expr.hpp"

void Literal::accept(Visitor const& visitor) const {
	visitor.visitLiteral(*this);
}

void Grouping::accept(Visitor const& visitor) const {
	visitor.visitGrouping(*this);
}

void Unary::accept(Visitor const& visitor) const {
	visitor.visitUnary(*this);
}

void Binary::accept(Visitor const& visitor) const {
	visitor.visitBinary(*this);
}