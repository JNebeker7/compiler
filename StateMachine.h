#pragma once
#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include "Token.h"
#include "Debug.h"

enum MachineState {
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE,
	CANTMOVE_STATE, PLUS_STATE, LPAREN_STATE,
	RPAREN_STATE, INSERTION_STATE, LESS_STATE,
	ASSIGNMENT_STATE, SEMICOLON_STATE, LCURLY_STATE,
	RCURLY_STATE, ENDFILE_STATE, DIVIDE_STATE,
	BAD_STATE, BLOCK_COMMENT_STATE, HALF_DONE_STATE,

	LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR,
	PLUS_CHAR, BAD_CHAR, LPAREN_CHAR,
	RPAREN_CHAR, UNDERSCORE_CHAR, LESS_CHAR,
	LCURLY_CHAR, RCURLY_CHAR, EQUAL_CHAR,
	SEMICOLON_CHAR, ENDFILE_CHAR, DIVIDE_CHAR,
	STAR_CHAR,

	LAST_CHAR
};

class StateMachineClass {
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType & correspondingTokenType);

private:
	MachineState mCurrentState;

	// The matrix of legal moves:
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

	// Which end-machine-states correspond to which token types.
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};


#endif /* _STATEMACHINE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */