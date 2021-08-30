//#ifndef RE2C_LEXER_TESTING__COMPILATIONUNIT_HPP__INCLUDED
//#define RE2C_LEXER_TESTING__COMPILATIONUNIT_HPP__INCLUDED
#pragma once

#include <map>
#include <string_view>

#include "Type.hpp"
#include "Function.hpp"

struct CompilationUnit {
	std::map<std::string_view, Type, Type::CompareByName> types;
	std::map<std::string_view, Function, Function::CompareByName> functions;
};

//#endif