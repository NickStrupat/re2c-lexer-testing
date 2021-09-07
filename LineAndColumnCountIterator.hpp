#pragma once

#include "Token.hpp"

template<typename TokenIterator>
class LineAndColumnCountIterator {
	TokenIterator it;
	uint64_t _line;
	uint64_t _column;
public:
	LineAndColumnCountIterator(TokenIterator it) : it(it), _line(1), _column(1) {}

	uint64_t line() const { return _line; }
	uint64_t column() const { return _column; }

	Token next() {
		Token token = it.next();
		if (token.type == TokenType::Newline) {
			_line++;
			_column = 1;
		}
		else {
			_column += token.sv.length();
		}
		return token;
	}
};