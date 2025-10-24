#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>
#include "Expr.h"
#include "Token.hpp"

class Environment {
public:
	void define(std::string const& name, std::variant<bool, double, std::string, std::monostate> const& value);
	std::variant<bool, double, std::string, std::monostate> get(Token const& nameToken) const;

private:
	std::unordered_map<std::string, std::variant<bool, double, std::string, std::monostate>> variables{};
};

