//#ifndef RE2C_LEXER_TESTING__DEFINITION_HPP__INCLUDED
//#define RE2C_LEXER_TESTING__DEFINITION_HPP__INCLUDED
#pragma once

#include <string_view>

struct Definition {
	std::string_view name;
	std::string_view text;

	struct CompareByName {
		bool operator()(Definition const& a, Definition const& b) const {
			return a.name < b.name;
		}
	};
};

//#endif