//
// Created by Nick on 3/26/2020.
//

#ifndef RE2C_LEXER_TESTING_LEXER_HPP
#define RE2C_LEXER_TESTING_LEXER_HPP

#include <map>
#include <string>

enum class TokenType
{
	Invalid = -1,
	Whitespace,
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
	BinaryRealHalfLiteral,
	Identifier
};

#define TOKEN(x) { TokenType::x, #x }
std::map<TokenType, std::string const> const tokenTypeString {
	TOKEN(Invalid),
	TOKEN(Whitespace),
	TOKEN(NewLine),
	TOKEN(Use),
	TOKEN(Namespace),
	TOKEN(Type),
	TOKEN(True),
	TOKEN(False),
	TOKEN(Arrow),
	TOKEN(DecimalIntegerLiteral),
	TOKEN(HexadecimalIntegerLiteral),
	TOKEN(BinaryIntegerLiteral),
	TOKEN(DecimalRealLiteral),
	TOKEN(BinaryRealHalfLiteral),
	TOKEN(Identifier),
};

struct Token {
	TokenType type;
	char const * end;
};

TokenType lex(char const *YYCURSOR);

#endif //RE2C_LEXER_TESTING_LEXER_HPP
