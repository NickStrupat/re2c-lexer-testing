#ifndef RE2C_LEXER_TESTING_DENTEDTOKENITERATOR_HPP
#define RE2C_LEXER_TESTING_DENTEDTOKENITERATOR_HPP

#include <cstdint>
#include <string_view>
#include <type_traits>

#include "lexer.hpp"

template<TokenType NewlineTT, TokenType IndentationTT, TokenType IndentTT, TokenType DedentTT, TokenType EofTT>
class DentedTokenIterator {
	std::string_view sv;
	uint64_t currentDentLevel;
	bool newlineSinceLastNonTab;
	uint64_t tabCount;

	Token getDentToken(std::string_view next) {
		if (tabCount > currentDentLevel) {
			++currentDentLevel;
			return { IndentTT, next };
		}
		else if (tabCount < currentDentLevel) {
			--currentDentLevel;
			return { DedentTT, next };
		}
	}
public:
	DentedTokenIterator(std::string_view sv) : sv(sv), currentDentLevel(), newlineSinceLastNonTab(), tabCount() {}

	Token next() {
		auto token = lex(sv);

		switch (token.type) {
			case NewlineTT:
				newlineSinceLastNonTab = true;
				break;
			case IndentationTT:
				if (newlineSinceLastNonTab)
					++tabCount;
				break;
			case EofTT:
				if (tabCount != currentDentLevel)
					return getDentToken({ sv.data(), 0 });
				break;
			default:
				if (newlineSinceLastNonTab) {
					if (tabCount != 0) {
						if (tabCount != currentDentLevel)
							return getDentToken({ sv.data(), 0 });
						else {
							newlineSinceLastNonTab = false;
							tabCount = 0;
						}
					}
				}
				break;
		}

		sv = sv.substr(token.sv.length());
		return token;
	}
};

#endif