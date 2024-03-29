#include "include/Scanner.h"
#include "include/Symbol.h"
#include "include/Debug.h"
#include "include/Node.h"
#include "include/Symbol.h"
#include "include/Parser.h"
#include "include/Instructions.h"

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
	do {
		t = s.GetNextToken();
		int lineNumber = s.getLineNumber();
		cout << "line: [" << lineNumber << "] " << t << endl;
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


bool test_expressions() {
	MSG("\nTesting Expressions and Binary Operators");

	IntegerNode *intTwo = new IntegerNode(2);
	IntegerNode *intFour = new IntegerNode(4);
	PlusNode *plus = new PlusNode(intTwo, intFour);
	int result = plus->Evaluate();

	MSG(intTwo->Evaluate() << "+" << intFour->Evaluate() << "=" << result);
	return true;
}

bool test_parserNoOutput() {
	MSG("\nTest parser no output");
	SymbolTable symbolTable = SymbolTable();
	ScannerClass scanner("code.cpp");
	ParserClass parser(&scanner, &symbolTable);
	parser.Start();
	MSG("Test parser no output DONE\n ");
	return true;
}

bool test_parserWithOutput() {
	MSG("\nTest parser with output");
	SymbolTable symbolTable = SymbolTable();
	ScannerClass scanner("code.cpp");
	// ParserClass parser(&scanner, &symbolTable);
	ParserClass * start = new ParserClass(&scanner, &symbolTable);
	start->Start();
	delete start; //
	MSG("Test parser with output DONE\n ");
	return true;
}

bool test_interpreter() {
	MSG("\nTest interpreter");
	SymbolTable symbolTable = SymbolTable();
	ScannerClass scanner("code.cpp");
	// ParserClass parser(&scanner, &symbolTable);
	ParserClass * parser = new ParserClass(&scanner, &symbolTable);
	StartNode * root = parser->Start();
	root->Interpret();
	delete root; //
	MSG("Test interpreter\n ");
	return true;
}

bool test_code() {
	MSG("\nTest Code");
	ScannerClass scanner("code.cpp");
	SymbolTable symbolTable = SymbolTable();
	ParserClass * parser = new ParserClass(&scanner, &symbolTable);
	StartNode * root = parser->Start();
	InstructionsClass code;
	root->Code(code);
    code.Finish();
	// code.PrintAllMachineCodes();
    code.Execute();

}

int main() {
	const int tests_count = 8;
	Tests tests[tests_count] = {
		test_token_type,
		test_scanner,
		test_symbols,
		test_expressions,
		test_parserNoOutput,
		test_parserWithOutput,
		test_interpreter,
		test_code,
	};

	for (int i = 0; i < tests_count; i++) {
		if (!tests[i]())
			return 1;
	}
    return 0;
}






