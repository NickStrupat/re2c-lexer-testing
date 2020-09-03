#include "TokenIterator.hpp"

#include "lexer.hpp"

#include <string_view>
using namespace std;

//string Token::toString() const {
//	stringstream ss;
//	ss << (this->sv.data() - sv.data()) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "");
//	return ss.str();
//}

TokenIterator::TokenIterator(string_view sv) : sv(sv) {}

Token TokenIterator::next() {
	auto token = lex(sv);
	sv = sv.substr(token.sv.length());
	return token;
}