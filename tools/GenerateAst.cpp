#include "GenerateAst.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
#include <limits>

void GenerateAst::removeSpaces(std::string& s) {
    for (std::string::iterator i = s.begin(); i < s.end(); ++i) if (std::isspace(*i)) s.erase(i);
}

void GenerateAst::generateExpr(std::string folder, std::string name, std::string parent, std::vector<std::string> fields, std::vector<std::string> includes) {
    std::ofstream fout(folder + R"(\)" + name + ".h");

    if (fout.is_open()) {
        fout << "#pragma once\n\n";

        if (!includes.empty()) {
            for (std::string s : includes) {
                removeSpaces(s);
                if(s[0] == '<' && s[s.size() - 1] == '>') fout << "#include " << s << '\n';
                else fout << "#include \"" << s << "\"\n";
            }
            fout << '\n';
        }

        if (!parent.empty()) fout << "struct " << name << " : " << parent << " {\n";
        else fout << "struct " << name << " {\n";

        if (!fields.empty()) {
            for (std::string s : fields) {
                removeSpaces(s);
                std::string type = s.substr(0, s.find("~"));
                std::string variableName = s.substr(s.find("~") + 1, INT_MAX);
                fout << '\t' << "const " << type << " " << variableName << ";\n";
            }
        }

        fout << "};";
        fout.close();
    } else {
        std::cerr << "Failed to create file at " << (folder + R"(\)" + name + ".h");
    }
}

void GenerateAst::generateExprVisitor(std::string folder, std::string name, std::vector<std::string> exprTypes) {

}