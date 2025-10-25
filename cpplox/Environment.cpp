#include "Environment.hpp"
#include "LoxRuntimeError.h"
#include <iostream>

void Environment::define(std::string const& name, std::variant<bool, double, std::string, std::monostate> const& value) {
	if(variables.find(name) == variables.end()) {
		variables.insert({ name, value });
	} else {
		variables[name] = value;
	}
}

void Environment::assign(Token const& nameToken, std::variant<bool, double, std::string, std::monostate> const& value) {
	std::string const& name = nameToken.toLexeme();

	if (!(variables.find(name) == variables.end())) {
		variables[name] = value;
	} else if(enclosing != nullptr) {
		enclosing->assign(nameToken, value);
	} else {
		throw LoxRuntimeError(nameToken, "Undefined variable \"" + name + "\"");
	}
}

std::variant<bool, double, std::string, std::monostate> Environment::get(Token const& nameToken) const {
	std::string const& name = nameToken.toLexeme();

	if (!(variables.find(name) == variables.end())) {
		return variables.at(name);
	} else if(enclosing != nullptr) {
		return enclosing->get(nameToken);
	} else {
		throw LoxRuntimeError(nameToken, "Undefined variable \"" + name + "\"");
	}
}