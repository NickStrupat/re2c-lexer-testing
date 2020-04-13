#ifndef RE2C_LEXER_TESTING_LEXER_HPP
#define RE2C_LEXER_TESTING_LEXER_HPP

#include <cstdint>
#include <map>
#include <string>
#include <string_view>

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include "magic_enum.hpp"

enum TokenType : std::uint8_t
{
	BinaryRealHalfLiteral,
	DecimalIntegerLiteral,
	HexadecimalIntegerLiteral,
	BinaryIntegerLiteral,
	DecimalRealLiteral,

	NewLine,
	Identifier,
	Whitespace,
	Use,
	Namespace,
	Type,
	Enum,
	Struct,
	Interface,
	Trait,
	Delegate,
	Field,
	Prop,
	Func,
	Local,
	True,
	False,
	Arrow,
	LessOrEqual,
	GreaterOrEqual,
	Range,
	InRange,
	NotInRange,
	LessThan,
	GreaterThan,
	NotEqual,
	Equal,
	And,
	Or,
	Power,
	Minus,
	Not,
	Multiply,
	Divide,
	Modulo,
	Plus,
	Octothorp,
	Tilde,
	Dot,
	EqualsSign,
	LeftParenthesis,
	RightParenthesis,
	LeftBrace,
	RightBrace,
	LeftBracket,
	RightBracket,
	SemiColon,
	Comma,

	Eof,
	Invalid,
};

struct Token {
	TokenType const type;
	std::string_view const sv;
};

Token lex(string_view sv);

class TokenIterator {
	string_view sv;
public:
	TokenIterator(string_view sv);
	Token getNextToken();
};

#endif