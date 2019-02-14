#include "Scanner.h"

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
	ScannerClass s("code.txt");
	TokenClass t;
	do {
		t = s.GetNextToken();
		int lineNumber = s.getLineNumber();
		cout << "Line[" << lineNumber << "] " << t << endl;
	} while (t.GetTokenType() != ENDFILE_TOKEN);
	return true;
}

int main() {
	const int tests_count = 2;
	Tests tests[tests_count] = {
		test_token_type,
		test_scanner
	};

	for (int i = 0; i < tests_count; i++) {
		if (!tests[i]())
			return 1;
	}
    return 0;
}






