//
// Created by Nick on 3/26/2020.
//

#ifndef RE2C_LEXER_TESTING_LEXER_HPP
#define RE2C_LEXER_TESTING_LEXER_HPP

#include <map>
#include <string>

enum TokenType
{
	Invalid = -1,
	NewLine,
	Use,
	Namespace,
	Type,
	True,
	False,
	Arrow,
	DecimalIntegerLiteral,
	HexadecimalIntegerLiteral,
	BinaryIntegerLiteral,
	DecimalRealLiteral,
	Identifier
};

std::map<TokenType, std::string const> const tokenTypeString {
		{ TokenType::Invalid, "Invalid" },
		{ TokenType::NewLine, "NewLine" },
		{ TokenType::Use, "Use" },
		{ TokenType::Namespace, "Namespace" },
		{ TokenType::Type, "Type" },
		{ TokenType::True, "True" },
		{ TokenType::False, "False" },
		{ TokenType::Arrow, "Arrow" },
		{ TokenType::DecimalIntegerLiteral, "DecimalIntegerLiteral" },
		{ TokenType::HexadecimalIntegerLiteral, "HexadecimalIntegerLiteral" },
		{ TokenType::BinaryIntegerLiteral, "BinaryIntegerLiteral" },
		{ TokenType::DecimalRealLiteral, "DecimalRealLiteral" },
		{ TokenType::Identifier, "Identifier" },
};

struct Token {
	TokenType type;
	char const * end;
};

TokenType lex(char const *YYCURSOR);

#endif //RE2C_LEXER_TESTING_LEXER_HPP
