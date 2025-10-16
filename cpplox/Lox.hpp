#ifndef LOX_HPP
#define LOX_HPP
#include <string>
#include "Token.hpp"

class Lox {
	private:
	static bool hadError;

	public:
	static void runFile(std::string path);
	static void runPrompt();
	static void run(std::string source);
	static void reportError(Token const& token, std::string const& message);
};
#endif
