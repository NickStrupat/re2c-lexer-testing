#include "DentedTokenIterator.hpp"

Token DentedTokenIterator::getDentToken() {
	if (tabCount > currentDentLevel) {
		++currentDentLevel;
		return { TokenType::Indent, { sv.data(), 0 } };
	}
	else if (tabCount < currentDentLevel) {
		--currentDentLevel;
		return { TokenType::Dedent, { sv.data(), 0 } };
	}
	else {
		return { TokenType::Dent, { sv.data(), 0 } };
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
			tabCount = 0;
			if (currentDentLevel > 0) {
				--currentDentLevel;
				return { TokenType::Dedent, { sv.data(), 0 } };
			}
			break;
		default:
			if (newlineSinceLastNonTab) {
				auto dentToken = getDentToken();
				if (tabCount == currentDentLevel) {
					newlineSinceLastNonTab = false;
					tabCount = 0;
				}
				return dentToken;
			}
			break;
	}

	sv = sv.substr(token.sv.length());
	return token;
}