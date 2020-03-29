/*!include:re2c "unicode.re.txt" */
/*!re2c
	whiteSpace = Zs | '\x09' | '\x0b' | '\x0c';

	newLine = '\r\n' | '\r' | '\n' | '\x85' | '\u2028' | '\u2029';

	letterCharacter = L | Nl;
	combiningCharacter = Mn | Mc;
	decimalDigitCharacter = Nd;
	connectingCharacter = Pc;
	formattingCharacter = Cf;

	identifierStartCharacter = letterCharacter | '_';
	identifierPartCharacter = letterCharacter | combiningCharacter | decimalDigitCharacter | connectingCharacter | formattingCharacter;
	identifier = identifierStartCharacter identifierPartCharacter*;

	booleanLiteral = "true" | "false";

	digitSeparator = "_";
	decimalDigit = [0-9];
	decimalInteger = decimalDigit (decimalDigit | digitSeparator)*;
	integerTypeSuffix = [iu];
	integerTypeStorageSizeSuffix = decimalInteger;
	decimalIntegerLiteral = decimalInteger integerTypeSuffix? integerTypeStorageSizeSuffix?;
	hexadecimalDigit = [0-9a-fA-F];
	hexadecimalInteger = hexadecimalDigit (hexadecimalDigit | digitSeparator)*;
	hexadecimalIntegerLiteral = "0x" hexadecimalInteger integerTypeSuffix? integerTypeStorageSizeSuffix?;
	binaryDigit = [01];
	binaryInteger = binaryDigit (binaryDigit | digitSeparator)*;
	binaryIntegerLiteral = "0b" binaryInteger integerTypeSuffix? integerTypeStorageSizeSuffix?;

	realTypeSuffix = "f";
	realTypeStorageSizeSuffix = "16" | "32" | "64" | "80" | "128";
	sign = [+-];
	exponentPart = 'e' sign? decimalInteger;
	decimalReal = decimalInteger "." decimalInteger exponentPart;
	decimalRealLiteral = decimalReal realTypeSuffix? realTypeStorageSizeSuffix?;
*/

#include "lexer.hpp"

TokenType lex(char const * YYCURSOR)
{
	const char *YYMARKER;
	int count = 0;
	loop:
	/*!re2c
	re2c:define:YYCTYPE = char;
	re2c:yyfill:enable = 0;

	decimalIntegerLiteral { return TokenType::DecimalIntegerLiteral; }
	hexadecimalIntegerLiteral { return TokenType::HexadecimalIntegerLiteral; }
	binaryIntegerLiteral { return TokenType::BinaryIntegerLiteral; }
	decimalRealLiteral { return TokenType::DecimalRealLiteral; }
	identifier { return TokenType::Identifier; }
	newLine { return TokenType::NewLine; }
	'use' { return TokenType::Use; }
	'namespace' { return TokenType::Namespace; }
	'type' { return TokenType::Type; }
	'true' { return TokenType::True; }
	'false' { return TokenType::False; }
	* { return TokenType::Invalid; }

	*/
}