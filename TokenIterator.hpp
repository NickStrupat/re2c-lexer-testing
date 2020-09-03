#ifndef RE2C_LEXER_TESTING_TOKENITERATOR_HPP
#define RE2C_LEXER_TESTING_TOKENITERATOR_HPP

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