#include <iostream>
#include <cassert>
using namespace std;

#include "lexer.hpp"

int main() {
	cout << tokenTypeString.at(lex("_asdf")) << endl;
	cout << tokenTypeString.at(lex("69_420")) << endl;
	cout << tokenTypeString.at(lex("69i16")) << endl;
	cout << tokenTypeString.at(lex("0xdeadbeef")) << endl;
	cout << tokenTypeString.at(lex("0b1001_0101u8")) << endl;
	cout << tokenTypeString.at(lex("3.1415_e69_f80")) << endl;
	return 0;
}
