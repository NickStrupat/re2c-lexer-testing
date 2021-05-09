#include "DentedTokenIterator.hpp"

Token DentedTokenIterator::getDentToken(std::string_view next) {
	if (tabCount > currentDentLevel) {
		++currentDentLevel;
		return { TokenType::Indent, next };
	}
	else if (tabCount < currentDentLevel) {
		--currentDentLevel;
		return { TokenType::Dedent, next };
	}
}

DentedTokenIterator::DentedTokenIterator(std::string_view sv) : sv(sv), currentDentLevel(), newlineSinceLastNonTab(), tabCount() {}

Token DentedTokenIterator::next() {
	auto token = lex(sv);

	switch (token.type) {
		case TokenType::Newline:
			newlineSinceLastNonTab = true;
			break;
		case TokenType::Tab:
			if (newlineSinceLastNonTab)
				++tabCount;
			break;
		case TokenType::Eof:
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