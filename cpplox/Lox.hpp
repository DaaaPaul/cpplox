#ifndef LOX_HPP
#define LOX_HPP
#include <string>

class Lox {
	private:
	static bool hadError;

	public:
	static void runFile(std::string path);
	static void runPrompt();
	static void run(std::string source);
	static void reportError(int line, std::string message);
};
#endif
