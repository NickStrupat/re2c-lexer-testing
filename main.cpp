#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string_view>
#include <vector>
using namespace std;

#include "lexer.hpp"
using namespace magic_enum;

#include "Utf8UnicodeEscapeSequenceIterator.hpp"
//#include "unescape.hpp"

struct Foo {
	char c;
	int i;
};

Foo bar() {
	return { 'c', 42 };
}

int main() {
	string_view const sv("0xbeef\r\n43 0b0100_1011 func namespace someVariable <> 1..3 0b1.01011.1000010000");
	TokenIterator it(sv);
	for (;;) {
		auto const token = it.getNextToken();
		if (token.type == TokenType::Eof)
			break;
		cout << (&token.sv[0] - &sv[0]) << "\t" << token.sv.length() << "\t" << token.sv << "\t" << enum_name(token.type) << endl;
	}
	
	return 0;
}
