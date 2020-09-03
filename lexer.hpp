#ifndef RE2C_LEXER_TESTING_LEXER_HPP
#define RE2C_LEXER_TESTING_LEXER_HPP

#include <cstdint>
#include <map>
#include <queue>
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

	Newline,
	Whitespace,
	Tab,
	Indent,
	Dedent,

	Identifier,

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

	If,
	Else,
	Match,

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
	Nand,
	Nor,
	Xor,
	Xnor,
	Not,
	Is,
	Isnt,

	Power,
	Minus,
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
	TokenType type;
	std::string_view sv;

	//std::string toString() const;
};

Token lex(std::string_view sv);

#endif