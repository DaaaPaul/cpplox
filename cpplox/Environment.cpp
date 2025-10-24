#include "Environment.hpp"
#include "LoxRuntimeError.h"

void Environment::define(std::string const& name, std::variant<bool, double, std::string, std::monostate> const& value) {
	if(variables.find(name) == variables.end()) {
		variables.insert({ name, value });
	} else {
		variables[name] = value;
	}
}

std::variant<bool, double, std::string, std::monostate> Environment::get(Token const& nameToken) const {
	std::string const& name = nameToken.toLexeme();

	if (!(variables.find(name) == variables.end())) {
		return variables.at(name);
	} else {
		throw LoxRuntimeError(nameToken, "Undefined variable \"" + name + "\"");
	}
}