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
#include "Parser.hpp"

#include "model/CompilationUnit.hpp"
#include "model/File.hpp"

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include "magic_enum.hpp"
using namespace magic_enum;

#define SQLITE_ORM_OPTIONAL_SUPPORTED
#include <sqlite_orm.h>

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
	parser.parseNamespaceMember();
	/*for (auto token = parser.next(); token.type != Eof; token = it.next()) {
		cout << (token.sv.data() - sv.data()) << "\t" << token.sv.length() << "\t" << "\t" << setw(30) << left << enum_name(token.type) << (token.sv.find_first_of('\n') == -1 ? token.sv : "") << endl;
	}*/
	
	return 0;
}