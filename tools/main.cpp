#include <iostream>
#include "GenerateAst.hpp"

int main() {
	GenerateAst::generateExpr(R"(..\cpplox)", "Expr", "", {}, {});
	GenerateAst::generateExpr(R"(..\cpplox)", "Literal", "Expr", { "std::any~value" }, { "Expr.h", "<any>"});
	GenerateAst::generateExpr(R"(..\cpplox)", "Grouping", "Expr", { "Expr~expr" }, { "Expr.h" });
	GenerateAst::generateExpr(R"(..\cpplox)", "Unary", "Expr", { "Token~op", "Expr~right" }, { "Expr.h", "Token.hpp" });
	GenerateAst::generateExpr(R"(..\cpplox)", "Binary", "Expr", { "Expr~left", "Token~op", "Expr~right" }, { "Expr.h", "Token.hpp" });
}