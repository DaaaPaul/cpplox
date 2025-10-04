#include "GenerateAst.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
#include <limits>

void GenerateAst::removeSpaces(std::string& s) {
	for (std::string::iterator i = s.begin(); i < s.end(); ++i) if (std::isspace(*i)) s.erase(i);
}

void GenerateAst::generateExpr(std::string folder, std::string name, std::vector<std::string> fields, std::vector<std::string> includes) {
	std::ofstream fout(folder + R"(\)" + name + ".h");

	if (fout.is_open()) {
		fout << "#pragma once\n\n";
		fout << "#include \"Visitor.h\"\n";
		fout << "#include <variant>\n";
		fout << "#include <memory>\n\n";

		std::string variantTypes;
		for (size_t i = 0; i < fields.size(); ++i) {
			std::string s = fields[i];
			removeSpaces(s);
			std::string type = s.substr(0, s.find("~"));
			if (i > 0) variantTypes += ", ";
			variantTypes += type;
		}

		fout << "struct Literal; struct Grouping; struct Unary; struct Binary;\n\n";
		fout << "using " << name << "Variant = std::variant<" << variantTypes << ">;\n\n";

		fout << "struct " << name << " {\n";
		fout << "\t" << name << "Variant variant;\n\n";

		for (std::string s : fields) {
			std::string type = s.substr(0, s.find("~"));
			std::string varName = s.substr(s.find("~") + 1);
			removeSpaces(type);
			removeSpaces(varName);
			fout << "\texplicit " << name << "(" << type << " " << varName << ") : variant(std::move(" << varName << ")) {}\n";
		}

		fout << "\n\ttemplate<class R>\n";
		fout << "\tR accept(Visitor<R>& visitor) {\n";
		fout << "\t\treturn std::visit(visitor, variant);\n";
		fout << "\t}\n";
		fout << "};";
	}
	else {
		std::cerr << "Failed to create file at " << (folder + R"(\)" + name + ".h");
	}
}

void GenerateAst::generateExprSubclass(std::string folder, std::string name, std::string parent, std::vector<std::string> fields, std::vector<std::string> includes) {
	std::ofstream fout(folder + R"(\)" + name + ".h");

	if (fout.is_open()) {
		fout << "#pragma once\n\n";

		if (!includes.empty()) {
			for (std::string s : includes) {
				removeSpaces(s);
				if (s[0] == '<' && s[s.size() - 1] == '>') fout << "#include " << s << '\n';
				else fout << "#include \"" << s << "\"\n";
			}
			fout << '\n';
		}

		fout << "struct " << name << " {\n";

		if (!fields.empty()) {
			for (std::string s : fields) {
				removeSpaces(s);
				std::string type = s.substr(0, s.find("~"));
				std::string variableName = s.substr(s.find("~") + 1, INT_MAX);
				if (type == "Expr") type = "std::unique_ptr<Expr>";
				fout << "\tconst " << type << " " << variableName << ";\n";
			}
			fout << '\n';

			std::string ctorArgs, ctorInit;
			for (std::string s : fields) {
				removeSpaces(s);
				std::string type = s.substr(0, s.find("~"));
				std::string variableName = s.substr(s.find("~") + 1, INT_MAX);
				if (type == "Expr") type = "std::unique_ptr<Expr>";
				if (!ctorArgs.empty()) {
					ctorArgs += ", ";
					ctorInit += ", ";
				}
				ctorArgs += type + " " + variableName;
				ctorInit += variableName + "(std::move(" + variableName + "))";
			}
			fout << "\t" << name << "(" << ctorArgs << ") : " << ctorInit << " {}\n";
		}

		fout << "};";
		fout.close();
	}
	else {
		std::cerr << "Failed to create file at " << (folder + R"(\)" + name + ".h");
	}
}

void GenerateAst::generateExprVisitor(std::string folder, std::string name, std::vector<std::string> exprTypes) {
	std::ofstream fout(folder + R"(\)" + name + ".h");

	if (fout.is_open()) {
		fout << "#pragma once\n\n";

		if (!exprTypes.empty()) {
			for (std::string s : exprTypes) {
				removeSpaces(s);
				fout << "#include \"" << s << ".h\"\n";
			}
			fout << '\n';
		}

		fout << "template<class R> struct " << name << " {\n";

		for (std::string s : exprTypes) {
			fout << "\tR operator()(const " << s << "&) const { return visit" << s << "(static_cast<const " << s << "&>(expr)); }\n";
		}

		fout << "\n";

		for (std::string s : exprTypes) {
			fout << "\tvirtual R visit" << s << "(const " << s << "&) const = 0;\n";
		}

		fout << "};";
	}
	else {
		std::cerr << "Failed to create file at " << (folder + R"(\)" + name + ".h");
	}
}