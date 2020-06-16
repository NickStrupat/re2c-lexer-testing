#include <iomanip>
#include <iostream>
#include <stack>
#include <string_view>
#include <vector>
using namespace std;

#include "lexer.hpp"
using namespace magic_enum;

struct Type2 {
	vector<string> qualifiers;
	string name;
};

struct CompilationUnit {
	vector<Type2> types;
};

class Parser {
	TokenIterator it;
	Token current;
	stack<string_view> qualifiers;

	void nextsym() {
		current = it.next();
	}

	void error(char const* msg) {
		throw exception(msg);
	}

	void warning(char const* msg) {
		cerr << msg << endl;
	}

	bool accept(std::initializer_list<TokenType> tokenTypes) {
		Token t;
		return accept(tokenTypes, t);
	}
	bool accept(std::initializer_list<TokenType> tokenTypes, Token& matched) {
		for (auto tokenType : tokenTypes)
			if (current.type == tokenType) {
				matched = current;
				nextsym();
				return true;
			}
		return false;
	}

	bool expect(std::initializer_list<TokenType> tokenTypes) {
		Token t;
		return expect(tokenTypes, t);
	}
	bool expect(std::initializer_list<TokenType> tokenTypes, Token& matched) {
		if (accept(tokenTypes, matched))
			return true;
		error(string("Unexpected token type: ").append(enum_name(current.type)).c_str());
	}

public:
	Parser(TokenIterator & tokenIterator) : it(tokenIterator), current(this->it.next()) {}

	CompilationUnit compilationUnit() {
		CompilationUnit cu;

		while (accept({ NewLine }))
			;

		Token matched;
		while (accept({ Qualifier })) {
			expect({ Whitespace });
			qualifiers.push(current.sv);
		}

		return cu;
	}

//#define IFTK(tokenName) if (current.type == TokenType::tokenName)
//	void parseNamespace() {
//		expect(Whitespace);
//		IFTK(Identifier)
//
//	}
//
//	void parse() {
//		for (next(); current.type != TokenType::Eof; next())
//		{
//			IFTK(NewLine)
//				continue;
//			else IFTK(Namespace)
//				parseNamespace();
//			else IFTK(Type)
//				parseType();
//			else
//				throw exception("unexpected token");
//		}
//	}
//#undef IS
};


int main() {
	//string_view const sv("0xbeef\r\n43 0b0100_1011 func namespace someVariable <> 1..3 0b1.01011.1000010000\r\nif x is Int32 and x < 42\r\n\tsomeFunc()");
	string_view const sv(R"cova(
qual System
	qual What
		type Nick
)cova");
	cout << sv << endl << endl;

	TokenIterator it(sv);
	/*for (auto token = it.next(); token.type != Eof; token = it.next()) {
		cout << (&token.sv[0] - &sv[0]) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "") << endl;
	}*/

	Parser parser(it);
	auto cu = parser.compilationUnit();
	/*for (auto token = parser.next(); token.type != Eof; token = it.next()) {
		cout << (&token.sv[0] - &sv[0]) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "") << endl;
	}*/
	
	return 0;
}