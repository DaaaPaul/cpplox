#include <iostream>
#include "GenerateAst.hpp"

int main() {
	GenerateAst::generateExpr(R"(..\cpplox)", "Expr", { "Literal~literal", "Grouping~grouping", "Unary~unary", "Binary~binary" }, {});

	GenerateAst::generateExprSubclass(R"(..\cpplox)", "Literal", "", { "std::any~value" }, { "<any>" });
	GenerateAst::generateExprSubclass(R"(..\cpplox)", "Grouping", "", { "Expr~expression" }, { "Expr.h", "<memory>" });
	GenerateAst::generateExprSubclass(R"(..\cpplox)", "Unary", "", { "Token~operator", "Expr~right" }, { "Expr.h", "Token.hpp", "<memory>" });
	GenerateAst::generateExprSubclass(R"(..\cpplox)", "Binary", "", { "Expr~left", "Token~operator", "Expr~right" }, { "Expr.h", "Token.hpp", "<memory>" });

	GenerateAst::generateExprVisitor(R"(..\cpplox)", "Visitor", { "Literal", "Grouping", "Unary", "Binary" });
}