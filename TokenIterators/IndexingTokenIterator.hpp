#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

#include "LineAndColumnCountIterator.hpp"

struct TokenEx {
	Token token;
	uint64_t offset;
	uint64_t line;
	uint64_t column;
};

using TokenMap = std::vector<std::vector<TokenEx>>;

template<typename TokenIterator>
class IndexingTokenIterator {
	uint64_t offset;
	LineAndColumnCountIterator<TokenIterator> & it;
	TokenMap & tokenMap;
public:
	IndexingTokenIterator(LineAndColumnCountIterator<TokenIterator> & it, TokenMap & tokenMap) : offset(0), it(it), tokenMap(tokenMap) {}

	Token next() {
		auto line = it.line();
		auto column = it.column();
		Token token = it.next();
		TokenEx tokenEx{ token, offset, line, column };
		offset += token.sv.length();
		if (tokenMap.size() < tokenEx.line)
			tokenMap.resize(tokenEx.line);
		tokenMap[tokenEx.line - 1].push_back(tokenEx);
		return token;
	}
};