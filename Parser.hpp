#pragma once

#include <cstddef>
#include <stack>
#include <string_view>

#include "Token.hpp"
#include "TokenType.hpp"

template<typename TokenIterator>
class Parser {
	struct NamespaceNode {
		std::string_view value;
		NamespaceNode const * next;

		NamespaceNode(NamespaceNode const &) = delete;
		NamespaceNode(NamespaceNode &&) = delete;
		NamespaceNode & operator=(NamespaceNode const &) = delete;
		NamespaceNode & operator=(NamespaceNode &&) = delete;
		void * operator new (std::size_t size) throw (std::bad_alloc) = delete;
	};

	struct UnexpectedTokenException : std::exception {
		Token const token;
		explicit UnexpectedTokenException(Token token) : token(token) {}
		char const * what() const override { return "Unexpected token type"; }
	};

	TokenIterator it;
	Token current;
	stack<Token> namespaceIdentifiers;

	void nextToken()                                            { current = it.next(); }
	void unexpected() const                                     { throw UnexpectedTokenException(current); }

	void skipOne(TokenType tokenType)                           { if (current.type == tokenType) nextToken(); }
	void skipOneOfAny(std::unordered_set<TokenType> tokenTypes) { if (tokenTypes.contains(current.type)) nextToken(); }
	void skipAll(TokenType tokenType)                           { while (tokenType == current.type) nextToken(); }
	void skipAllOfAny(std::unordered_set<TokenType> tokenTypes) { while (tokenTypes.contains(current.type)) nextToken(); }

	bool foundOne(TokenType tokenType) { return current.type == tokenType; }
	//bool foundSeq(std::initializer_list<TokenType>)
public:
	explicit Parser(TokenIterator & tokenIterator) : it(tokenIterator), current(), namespaceIdentifiers() {}

	void parseNamespace() {
		nextToken();
		skipAllOfAny({ TokenType::Whitespace, TokenType::Tab });
		while (foundOne(TokenType::Identifier)) {
			namespaceIdentifiers.push(current);
			nextToken();
			if (!foundOne(TokenType::Dot))
				break;
		}
		skipAll(TokenType::Newline);
		skipAll(TokenType::Tab);
		if (foundOne(TokenType::Indent)) {
			parseNamespaceMember();
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
			}
		}
	}
};