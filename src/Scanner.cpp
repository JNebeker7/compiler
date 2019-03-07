#include "../include/Scanner.h"
#include "../include/StateMachine.h"
#include <string>
#include "../include/Debug.h"

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
		}
		lexeme += c;
		state = sm.UpdateState(c, tt);
		if (state == START_STATE) {
			lexeme = "";
        }
		if ( state == BAD_STATE ) {
			MSG("Bad character"  << lexeme << " on line " << mLineNumber )
			exit(2);
		}
		// if ( state == CANTMOVE_STATE ) {
		// 	MSG("Bad character"  << lexeme << " on line " << mLineNumber );
		// 	throw "bad character";
		// }
		
	} while (state != CANTMOVE_STATE);
	if ( c == '\n' ) {
		mLineNumber--;
	}
	if ( tt == BAD_TOKEN ) {
		MSG("Bad character "  << lexeme << " on line " << mLineNumber )
		exit(2);
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