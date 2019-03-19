#include "include/Scanner.h"
#include "include/Symbol.h"
#include "include/Debug.h"
#include "include/Node.h"
#include "include/Symbol.h"

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

bool test_node() {
	MSG("\nTest Nodes");
	SymbolTable symbolTable = SymbolTable();

	// cout << sum;
	IntegerNode * intCoutNode = new IntegerNode(11);
	CoutStatementNode * coutStatement = new CoutStatementNode(intCoutNode);

	// sum = int + int;
	IntegerNode * intNode = new IntegerNode(11);
	IdentifierNode * identifierInteger = new IdentifierNode("y", &symbolTable);
	AssignmentStatementNode * assignmentStatement = new AssignmentStatementNode(identifierInteger, intNode);

	// int sum;
	IdentifierNode * indentifierDeclaration = new IdentifierNode("x", &symbolTable);
	DeclarationStatmentNode * declarationStatement = new DeclarationStatmentNode(indentifierDeclaration);

	StatementGroupNode * statementGroup = new StatementGroupNode();
	statementGroup->AddStatement(coutStatement);
	statementGroup->AddStatement(assignmentStatement);
	statementGroup->AddStatement(declarationStatement);
	
	BlockNode * block = new BlockNode(statementGroup);
	ProgramNode * program = new ProgramNode(block);
	StartNode * start = new StartNode(program);

	delete start;
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

int main() {
	const int tests_count = 5;
	Tests tests[tests_count] = {
		test_token_type,
		test_scanner,
		test_symbols,
		test_node,
		test_expressions,
	};

	for (int i = 0; i < tests_count; i++) {
		if (!tests[i]())
			return 1;
	}
    return 0;
}






