#include "Scanner.h"
#include "StateMachine.h"
#include <string>
#include "Debug.h"

using std::string;

ScannerClass::ScannerClass(string file) {
	mFin.open(file);
	if (!mFin) {
		throw "Failed to open file.";
	}
	MSG("Initilizing ScannerClass object");
	mLineNumber = 1;
}

TokenClass ScannerClass::GetNextToken() {
	TokenType tt;
	StateMachineClass sm;
	MachineState state;
	string lexeme;
	char c;
	do {
		c = mFin.get();
		if ( c == '\n' ) {
			mLineNumber++;
			// std::cout << "new line " << std::endl;
		}
		lexeme += c;
		state = sm.UpdateState(c, tt);
		if (state == START_STATE) {
			lexeme = "";
        }
		if ( state == BAD_STATE ) {
			std::cerr << "bad character __" << lexeme << "__ at a line number" << std::endl; 
			throw "Bad character";	
		}
		
	} while (state != CANTMOVE_STATE);
	if ( c == '\n' ) {
		mLineNumber--;
	}
	mFin.unget();
	lexeme.pop_back();
	TokenClass T(tt, lexeme);
	T.CheckReserved();
	return T;
}

int ScannerClass::getLineNumber() {
	return mLineNumber;
}