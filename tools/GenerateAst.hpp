#pragma once

#include <string>
#include <vector>

class GenerateAst {
public:
	static void generateExpr(std::string folder, std::string name, std::vector<std::string> fields, std::vector<std::string> includes);
	static void generateExprSubclass(std::string folder, std::string name, std::string parent, std::vector<std::string> fields, std::vector<std::string> includes);
	static void generateExprVisitor(std::string folder, std::string name, std::vector<std::string> exprTypes);

private:
	static void removeSpaces(std::string& s);
};

