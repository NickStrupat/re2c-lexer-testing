#include "TokenIterator.hpp"

#include "lexer.hpp"

#include <string_view>
using namespace std;

//string Token::toString() const {
//	stringstream ss;
//	ss << (this->sv.data() - sv.data()) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "");
//	return ss.str();
//}

TokenIterator::TokenIterator(string_view sv)
	: sv(sv)
	, currentDentLevel()
	, newlineSinceLastNonTab()
	, tabCount() {}

Token TokenIterator::getDentToken(string_view next) {
	if (tabCount > currentDentLevel) {
		++currentDentLevel;
		return { Indent, next };
	}
	else if (tabCount < currentDentLevel) {
		--currentDentLevel;
		return { Dedent, next };
	}
}

Token TokenIterator::next() {
	auto token = lex(sv);

	if (token.type == Newline)
		newlineSinceLastNonTab = true;
	else if (token.type == Tab) {
		if (newlineSinceLastNonTab)
			++tabCount;
	}
	else if (token.type == Eof) {
		if (tabCount != currentDentLevel) {
			return getDentToken({ sv.data(), 0 });
		}
	}
	else if (newlineSinceLastNonTab) {
		if (tabCount != 0) {
			if (tabCount != currentDentLevel) {
				return getDentToken({ sv.data(), 0 });
			}
			else {
				newlineSinceLastNonTab = false;
				tabCount = 0;
			}
		}
	}

	sv = sv.substr(token.sv.length());
	return token;
}