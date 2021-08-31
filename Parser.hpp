#pragma once

#include <cstddef>
#include <stack>
#include <string_view>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Listener.hpp"
#include "Model/Repository.hpp"

template<typename TokenIterator>
class Parser {
	struct UnexpectedTokenException : std::exception {
		Token const token;
		explicit UnexpectedTokenException(Token token) : token(token) {}
		char const * what() const override { return "Unexpected token type"; }
	};

	TokenIterator it;
	Token current;
	Repository repo;

	void nextToken()                                            { current = it.next(); }
	void unexpected() const                                     { throw UnexpectedTokenException(current); }

	void skipOne(TokenType tokenType)                           { if (current.type == tokenType) nextToken(); }
	void skipOneOfAny(std::unordered_set<TokenType> tokenTypes) { if (tokenTypes.contains(current.type)) nextToken(); }
	void skipAll(TokenType tokenType)                           { while (tokenType == current.type) nextToken(); }
	void skipAllOfAny(std::unordered_set<TokenType> tokenTypes) { while (tokenTypes.contains(current.type)) nextToken(); }

	bool foundOne(TokenType tokenType) { return current.type == tokenType; }
	//bool foundSeq(std::initializer_list<TokenType>)
public:
	explicit Parser(TokenIterator & tokenIterator, Repository & repo, Listener & listener) : it(tokenIterator), current(), repo(repo) {}

	void parseNamespace() {
		nextToken();
		skipAllOfAny({ TokenType::Whitespace, TokenType::Tab });
		while (foundOne(TokenType::Identifier)) {
			listener.enterNamespace(current);
			nextToken();
			if (!foundOne(TokenType::Dot))
				break;
		}
		skipAll(TokenType::Newline);
		skipAll(TokenType::Tab);
		if (foundOne(TokenType::Indent)) {
			do {
				parseNamespaceMember();
				skipAll(TokenType::Newline);
				skipAll(TokenType::Tab);
			} while (foundOne(TokenType::Dent))
			if (foundOne(TokenType::Dedent)) {

			}
		}
	}

	void parseType() {}
	void parseFunction() {}

	void parseNamespaceMember() {
		for (;;) {
			nextToken();
			switch (current.type) {
				case TokenType::Namespace: parseNamespace(); break;
				case TokenType::Type: parseType(); break;
				case TokenType::Func: parseFunction(); break;
				case TokenType::Newline: break;
				case TokenType::Eof: return;
				default: unexpected();
			}
		}
	}
};