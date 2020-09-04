#ifndef RE2C_LEXER_TESTING_DENTEDTOKENITERATOR_HPP
#define RE2C_LEXER_TESTING_DENTEDTOKENITERATOR_HPP

#include <cstdint>
#include <string_view>
#include <type_traits>

#include "lexer.hpp"

class DentedTokenIterator {
	std::string_view sv;
	uint64_t currentDentLevel;
	bool newlineSinceLastNonTab;
	uint64_t tabCount;

	Token getDentToken(std::string_view next);
public:
	DentedTokenIterator(std::string_view sv);
	Token next();
};

#endif