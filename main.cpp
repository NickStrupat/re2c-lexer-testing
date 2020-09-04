#include <iomanip>
#include <iostream>
#include <stack>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
using namespace std;

#include "lexer.hpp"
#include "TokenIterator.hpp"
#include "DentedTokenIterator.hpp"

#include "ast/CompilationUnit.hpp"

#include "magic_enum.hpp"
using namespace magic_enum;

class Parser {
	DentedTokenIterator it;
	Token current;
	queue<string_view> namespaces;

	void nextsym() {
		current = it.next();
	}

	void error(char const* msg) {
		throw exception(msg);
	}

	void warning(char const* msg) {
		cerr << msg << endl;
	}

	bool accept(std::unordered_set<TokenType> tokenTypes) {
		Token t;
		return accept(tokenTypes, t);
	}
	bool accept(std::unordered_set<TokenType> tokenTypes, Token& matched) {
		if (tokenTypes.contains(current.type)) {
			matched = current;
			nextsym();
			return true;
		}
		return false;
	}

	bool expect(std::unordered_set<TokenType> tokenTypes) {
		Token t;
		return expect(tokenTypes, t);
	}
	bool expect(std::unordered_set<TokenType> tokenTypes, Token& matched) {
		if (accept(tokenTypes, matched))
			return true;
		error(string("Unexpected token type: ").append(enum_name(current.type)).c_str());
	}

public:
	Parser(DentedTokenIterator & tokenIterator) : it(tokenIterator), current(this->it.next()) {}

	CompilationUnit compilationUnit() {
		CompilationUnit cu;

		while (accept({ TokenType::Newline }))
			;

		Token matched;
		while (accept({ TokenType::Namespace })) {
			expect({ TokenType::Whitespace });
			namespaces.push(current.sv);
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

//struct Namespace {
//	vector<Namespace> namespaces;
//	vector<Type> types;
//	vector<Function> functions;
//};
//struct Type {};
//struct Function {};
//
//struct Expression : variant<
//	unique_ptr<Expression>
//> {};
//
//typedef variant<
//	Namespace,
//	Type,
//	Function,
//	Expression
//> TopLevel;
//
//TopLevel parseTopLevel(TokenIterator& it);
//Namespace parseNamespace(TokenIterator& it);
//Type parseType(TokenIterator& it);
//Function parseFunction(TokenIterator& it);
//
//void throwUnexpected(Token const & token) {
//	throw exception(string("Unexpected token type: `").append(enum_name(token.type)).c_str());
//}
//
////void skipWhitespacesAndTabs(TokenIterator& it, Token& token) {
////	while (token.type == TokenType::Whitespace | token.type == TokenType::Tab)
////		token = it.next();
////}
//
//void skip(TokenIterator & it, Token & token, unordered_set<TokenType> const & tokenTypesToSkip) {
//	while (tokenTypesToSkip.contains(token.type))
//		token = it.next();
//}
//
//TopLevel parseTopLevel(TokenIterator& it) {
//	for (;;) {
//		auto const token = it.next();
//		switch (token.type) {
//			case TokenType::Namespace: return parseNamespace(it);
//			case TokenType::Type: return parseType(it);
//			case TokenType::Func: return parseFunction(it);
//
//			case TokenType::Newline: continue;
//
//			//case TokenType::Eof: return {};
//			default: throwUnexpected(token);
//		}
//	}
//}

//Namespace parseNamespace(TokenIterator& it) {
//	auto token = it.next();
//	skip(it, token, { TokenType::Whitespace, TokenType::Tab });
//	if (token.type != TokenType::Identifier)
//		throwUnexpected(token);
//	token = it.next();
//	skip(it, token, { TokenType::Newline, TokenType::Tab });
//	switch (token.type) {
//		case TokenType::Type: 
//	}
//}

int main() {
	//string_view const sv("0xbeef\r\n43 0b0100_1011 func namespace someVariable <> 1..3 0b1.01011.1000010000\r\nif x is Int32 and x < 42\r\n\tsomeFunc()");
	string_view const sv(R"cova(
namespace System
	namespace Empty
	namespace What
		type Nick
		type Strupat
	namespace Okay
		type More
		type Types
)cova");
	cout << sv << endl << endl;

	DentedTokenIterator it(sv);
	for (auto token = it.next(); token.type != TokenType::Eof; token = it.next()) {
		auto const position = token.sv.data() - sv.data();
		auto const length = token.sv.length();
		auto const name = enum_name(token.type);
		auto const text = token.sv.find_first_of('\n') == -1 ? token.sv : "";
		cout << position << "\t" << length << "\t" << "\t" << setw(30) << left << name << text << endl;
		//cout << (token.sv.length() == 0 ? enum_name(token.type) : token.sv);
	}

	it = sv;
	Parser parser(it);
	auto cu = parser.compilationUnit();
	/*for (auto token = parser.next(); token.type != Eof; token = it.next()) {
		cout << (token.sv.data() - sv.data()) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "") << endl;
	}*/
	
	return 0;
}