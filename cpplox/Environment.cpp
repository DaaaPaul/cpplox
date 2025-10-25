#include "Environment.hpp"
#include "LoxRuntimeError.h"
#include <iostream>

Environment::Environment(Environment const& e) : variables(e.variables) {
	if (e.enclosing) {
		enclosing = std::make_unique<Environment>(*(e.enclosing));
	} else {
		enclosing = nullptr;
	}
}

Environment& Environment::operator=(Environment const& e) {
	 if (this == &e) return *this;
	 variables = e.variables;

	 if (e.enclosing) {
		 enclosing = std::make_unique<Environment>(*(e.enclosing));
	 } else {
		 enclosing = nullptr;
	 }

	 return *this;
}

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

void Environment::setEnclosing(Environment const& e) {
	enclosing = std::make_unique<Environment>(e);
}