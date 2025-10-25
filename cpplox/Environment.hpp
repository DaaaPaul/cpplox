#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>
#include "Expr.h"
#include "Token.hpp"

class Environment {
public:
	Environment() = default;
	Environment(std::unique_ptr<Environment>&& en) : enclosing(std::move(en)) {}
	Environment(Environment const& e) : enclosing(std::make_unique<Environment>(*(e.enclosing))), variables(e.variables) {}
	void operator=(Environment const& e) { enclosing = std::make_unique<Environment>(*(e.enclosing)); variables = e.variables; }

	void define(std::string const& name, std::variant<bool, double, std::string, std::monostate> const& value);
	void assign(Token const& nameToken, std::variant<bool, double, std::string, std::monostate> const& value);
	std::variant<bool, double, std::string, std::monostate> get(Token const& nameToken) const;

private:
	std::unique_ptr<Environment> enclosing{};
	std::unordered_map<std::string, std::variant<bool, double, std::string, std::monostate>> variables{};
};

