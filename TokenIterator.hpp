#ifndef RE2C_LEXER_TESTING__TOKENITERATOR_HPP__INCLUDED
#define RE2C_LEXER_TESTING__TOKENITERATOR_HPP__INCLUDED

#include <cstdint>
#include <string_view>

#include "lexer.hpp"

class TokenIterator {
	std::string_view sv;
public:
	TokenIterator(std::string_view sv);
	Token next();
};

#endif