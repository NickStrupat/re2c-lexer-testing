//#ifndef RE2C_LEXER_TESTING__TYPE_HPP__INCLUDED
//#define RE2C_LEXER_TESTING__TYPE_HPP__INCLUDED
#pragma once

#include <map>
#include <string_view>

#include "Definition.hpp"
#include "Function.hpp"
#include "Property.hpp"

struct Type : Definition {
	std::map<std::string_view, Type, Type::CompareByName> types;
	std::map<std::string_view, Function, Function::CompareByName> functions;
	std::map<std::string_view, Property, Property::CompareByName> properties;
};

//#endif