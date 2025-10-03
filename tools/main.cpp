#include <iostream>
#include "GenerateAst.hpp"

int main() {
	GenerateAst::generate(R"(..\cpplox)", "Expr", "", {}, {});
	GenerateAst::generate(R"(..\cpplox)", "Literal", "Expr", { "std::any~value" }, { "Expr.h", "<any>"});
	GenerateAst::generate(R"(..\cpplox)", "Grouping", "Expr", { "Expr~expr" }, { "Expr.h" });
	GenerateAst::generate(R"(..\cpplox)", "Unary", "Expr", { "Token~op", "Expr~right" }, { "Expr.h", "Token.hpp" });
	GenerateAst::generate(R"(..\cpplox)", "Binary", "Expr", { "Expr~left", "Token~op", "Expr~right" }, { "Expr.h", "Token.hpp" });
}