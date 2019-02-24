#include "Scanner.h"
#include "Symbol.h"

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
	s.AddEntry("second");
	s.AddEntry("third");
	if (s.Exists("third")) {
		cout << "found third" << endl;
	}
	else
		cout << "third not found" << endl;

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






