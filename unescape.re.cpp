#include "unescape.hpp"

//Unescaped::Unescaped(char32_t value, std::byte length) : value(value), length(length) {}

#include <cstdlib>
#include <cstddef>
using namespace std;

#include "unilib/unilib/utf8.h"
using namespace ufal::unilib;
typedef DecodedType DT;

Unescaped unescape(char const* YYCURSOR) {
	auto start = YYCURSOR;
	char const* YYMARKER;
	/*!re2c
	re2c:define:YYCTYPE = 'char';
	re2c:yyfill:enable = 0;

	hexdecimalDigit = [0-9A-Fa-f];
	"\\U" hexdecimalDigit{8} { return { DT::Unescaped8, static_cast<char32_t>(strtoul(start + 2, nullptr, 16)), byte(10) }; }
	"\\u" hexdecimalDigit{4} { return { DT::Unescaped4, static_cast<char32_t>(strtoul(start + 2, nullptr, 16)), byte(6) }; }
	"\\x" hexdecimalDigit{2} { return { DT::Unescaped2, static_cast<char32_t>(strtoul(start + 2, nullptr, 16)), byte(4) }; }
	"\\n"  . { return { DT::Unescaped1, static_cast<char32_t>('\n'), byte(1) }; }
	"\\r"  . { return { DT::Unescaped1, static_cast<char32_t>('\r'), byte(1) }; }
	"\\t"  . { return { DT::Unescaped1, static_cast<char32_t>('\t'), byte(1) }; }
	"\\\\" . { return { DT::Unescaped1, static_cast<char32_t>('\\'), byte(1) }; }
	"\\\'" . { return { DT::Unescaped1, static_cast<char32_t>('\''), byte(1) }; }
	"\\\"" . { return { DT::Unescaped1, static_cast<char32_t>('\"'), byte(1) }; }
	[\x00-\x7f] { return { DT::Raw, utf8::first(start), byte(1) }; }
	[\x80-\u07ff] { return { DT::Raw, utf8::first(start), byte(2) }; }
	[\u0800-\uffff] { return { DT::Raw, utf8::first(start), byte(3) }; }
	[\U00010000-\U0010ffff] { return { DT::Raw, utf8::first(start), byte(4) }; }
	*/
}
//* { return { DT::Invalid, static_cast<char32_t>(*YYCURSOR), (std::byte)(YYCURSOR - start) }; }
//* { return DT::Invalid, char32_t(0), byte(}