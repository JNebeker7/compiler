#include "Scanner.h"
#include "Symbol.h"
#include "Debug.h"

using std::cout;
using std::endl;

typedef bool(*Tests)();

bool test_token_type() {
	TokenType tt = VOID_TOKEN;
	string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	return true;
}

bool test_scanner() {
	ScannerClass s("code.cpp");
	TokenClass t;
	cout << "+----------+------+----------------+" << endl;
	cout << "| Line #   | NAME | TYPE           |" << endl;
	cout << "+----------+------+----------------+" << endl;
	do {
		t = s.GetNextToken();
		int lineNumber = s.getLineNumber();
		if (lineNumber < 10) {
			cout << "| Line[" << lineNumber << "]  | " << t << endl;
		}
		if (lineNumber >= 10) {
			cout << "| Line[" << lineNumber << "] | " << t << endl;
		}
	} while (t.GetTokenType() != ENDFILE_TOKEN);
	cout << "+----------+------+----------------+" << endl;
	return true;
}

bool test_symbols() {
	cout << "symbol test" << endl;
	SymbolTable s;
	MSG("setting x = 5");
	s.AddEntry("x");
	s.SetValue("x", 5);
	s.CoutVariables();
	MSG("setting y = 11");
	s.AddEntry("y");
	s.SetValue("y", 11);
	s.CoutVariables();
	MSG("getting index of y");
	int index = s.GetIndex("y");
	MSG("y = " << index);
	MSG("Getting number of variables");
	int count = s.GetCount();
	MSG("count is " << count);
	MSG("adding entry x again ");
	s.AddEntry("x");
	MSG("Setting new value to x ");
	s.SetValue("x", 42);
	s.CoutVariables();
	return true;
}

int main() {
	const int tests_count = 3;
	Tests tests[tests_count] = {
		test_token_type,
		test_scanner,
		test_symbols
	};

	for (int i = 0; i < tests_count; i++) {
		if (!tests[i]())
			return 1;
	}
    return 0;
}






