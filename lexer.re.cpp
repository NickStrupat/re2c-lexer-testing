/*!include:re2c "unicode.re.txt" */
/*!re2c
	whitespace = Zs | '\x09' | '\x0b' | '\x0c';

	newLine = '\r\n' | '\r' | '\n' | '\x85' | '\u2028' | '\u2029';

	sign = [+-];
	hexadecimalDigit = [0-9a-fA-F];
	decimalDigit = [0-9];
	binaryDigit = [01];

	digitSeparator = "_";

	hexadecimalPrefix = "0x";
	binaryPrefix = "0b";
	unicodePrefix = "\\u";

	unicodeLiteral = unicodePrefix hexadecimalDigit+;

	letterCharacter = L | Nl; // | (unicodeLiteralPrefix LHexLiterals) | (unicodeLiteralPrefix NlHexLiterals);
	combiningCharacter = Mn | Mc; // | (unicodeLiteralPrefix MnHexLiterals) | (unicodeLiteralPrefix McHexLiterals);
	decimalDigitCharacter = Nd; // | (unicodeLiteralPrefix NdHexLiterals);
	connectingCharacter = Pc; // | (unicodeLiteralPrefix PcHexLiterals);
	formattingCharacter = Cf; // | (unicodeLiteralPrefix CfHexLiterals);

	identifierStartCharacter = letterCharacter | "_";
	identifierPartCharacter = letterCharacter | combiningCharacter | decimalDigitCharacter | connectingCharacter | formattingCharacter;
	identifier = identifierStartCharacter identifierPartCharacter*;

	booleanLiteral = "true" | "false";

	decimalInteger = decimalDigit (decimalDigit | digitSeparator)*;

	integerTypeSuffix = [iu];
	integerTypeStorageSize = decimalInteger;
	integerType = integerTypeSuffix integerTypeStorageSize?;

	decimalIntegerLiteral = decimalInteger integerType?;

	hexadecimalInteger = hexadecimalDigit (hexadecimalDigit | digitSeparator)*;
	hexadecimalIntegerLiteral = hexadecimalPrefix hexadecimalInteger integerType?;

	binaryInteger = binaryDigit (binaryDigit | digitSeparator)*;
	binaryIntegerLiteral = binaryPrefix binaryInteger integerType?;

	realTypeSuffix = "f";
	realTypeStorageSizeHalf     = "16";
	realTypeStorageSizeSingle   = "32";
	realTypeStorageSizeDouble   = "64";
	realTypeStorageSizeExtended = "80";
	realTypeStorageSizeQuad     = "128";
	realTypeStorageSize = realTypeStorageSizeHalf | realTypeStorageSizeSingle | realTypeStorageSizeDouble | realTypeStorageSizeExtended | realTypeStorageSizeQuad;
	realType = realTypeSuffix realTypeStorageSize?;

	decimalExponentPart = [Ee] sign? decimalInteger;
	binaryExponentPart = [Ee] sign? binaryInteger;

	decimalRealLiteral
		= decimalInteger "." decimalInteger decimalExponentPart? realType?
		| "." decimalInteger decimalExponentPart? realType?
		| decimalInteger decimalExponentPart realType?
		| decimalInteger realType
		;

	binaryRealHalfLiteral     = binaryPrefix binaryDigit "." binaryDigit{5}  "." binaryDigit{10}  (realTypeSuffix realTypeStorageSizeHalf)?;
	binaryRealSingleLiteral   = binaryPrefix binaryDigit "." binaryDigit{8}  "." binaryDigit{23}  (realTypeSuffix realTypeStorageSizeSingle)?;
	binaryRealDoubleLiteral   = binaryPrefix binaryDigit "." binaryDigit{11} "." binaryDigit{52}  (realTypeSuffix realTypeStorageSizeDouble)?;
	binaryRealExtendedLiteral = binaryPrefix binaryDigit "." binaryDigit{15} "." binaryDigit{64}  (realTypeSuffix realTypeStorageSizeExtended)?;
	binaryRealQuadLiteral     = binaryPrefix binaryDigit "." binaryDigit{15} "." binaryDigit{112} (realTypeSuffix realTypeStorageSizeQuad)?;
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

	binaryRealHalfLiteral { return TokenType::BinaryRealHalfLiteral; }
	unicodeLiteral { return TokenType::Invalid; }
	decimalIntegerLiteral { return TokenType::DecimalIntegerLiteral; }
	hexadecimalIntegerLiteral { return TokenType::HexadecimalIntegerLiteral; }
	binaryIntegerLiteral { return TokenType::BinaryIntegerLiteral; }
	decimalRealLiteral { return TokenType::DecimalRealLiteral; }
	identifier { return TokenType::Identifier; }
	newLine { return TokenType::NewLine; }
	whitespace { return TokenType::Whitespace; }
	
	'use' { return TokenType::Use; }
	'namespace' { return TokenType::Namespace; }
	'type' { return TokenType::Type; }

	'true' { return TokenType::True; }
	'false' { return TokenType::False; }

	* { return TokenType::Invalid; }

	*/
}