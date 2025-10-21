#ifndef LOX_HPP
#define LOX_HPP
#include <string>
#include "Interpreter.hpp"
#include "Token.hpp"
#include "LoxRuntimeError.h"

class Lox {
	private:
	static bool hadError;
	static bool hadRuntimeError;
	static Interpreter interpreter;

	public:
	static void runFile(std::string path);
	static void runPrompt();
	static void run(std::string source);
	static void reportError(Token const& token, std::string const& message);
	static void reportRuntimeError(LoxRuntimeError const& error);
};
#endif
