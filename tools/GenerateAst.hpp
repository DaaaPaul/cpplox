#pragma once

#include <string>
#include <vector>

class GenerateAst {
public:
	static void generate(std::string folder, std::string name, std::string parent, std::vector<std::string> fields, std::vector<std::string> includes);

private:
	static void removeSpaces(std::string& s);
};

