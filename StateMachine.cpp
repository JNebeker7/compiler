#include "StateMachine.h"
#include <regex>

using std::regex;
using std::regex_match;
using std::string;

StateMachineClass::StateMachineClass() {
	
	mCurrentState = START_STATE;

	for ( int i = 0; i < LAST_STATE; i++ ) {
		for ( int j = 0; j < LAST_CHAR; j++ ) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	// spin on whitespace
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	// returen char
	mLegalMoves[START_STATE][RETURN_CHAR] = START_STATE;
	// letter and underscore and digit
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[START_STATE][UNDERSCORE_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][UNDERSCORE_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
	// ()
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	// <
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	// <<
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	// {}
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	mLegalMoves[RCURLY_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	// =
	mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
	// digits
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	// ;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	// +
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	// EOF
	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

	// comments initial
	for ( int i = 0; i < LAST_CHAR; i++ ) {
		mLegalMoves[LINE_COMMENT_STATE][i] = LINE_COMMENT_STATE;
	}
	// comments
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINE_COMMENT_STATE;
	// block comments
	mLegalMoves[DIVIDE_STATE][STAR_CHAR] = BLOCK_COMMENT_STATE;

	mLegalMoves[LINE_COMMENT_STATE][RETURN_CHAR] = START_STATE;
	mLegalMoves[LINE_COMMENT_STATE][ENDFILE_CHAR] = START_STATE;
	// end of comments

	// block comments
	for ( int i = 0; i < LAST_CHAR; i++ ) {
		mLegalMoves[BLOCK_COMMENT_STATE][i] = BLOCK_COMMENT_STATE;
	}
	mLegalMoves[BLOCK_COMMENT_STATE][STAR_CHAR] = HALF_DONE_STATE;
	for ( int i = 0; i < LAST_CHAR; i++ ) {
		mLegalMoves[HALF_DONE_STATE][i] = BLOCK_COMMENT_STATE;
	}
	mLegalMoves[HALF_DONE_STATE][DIVIDE_CHAR] = START_STATE;
	// end of block comments
	
    for ( int i = 0; i < LAST_STATE; i++ ) {
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}

    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[BAD_STATE] = BAD_TOKEN;

}

MachineState StateMachineClass::UpdateState(char currentCharacter, 
    TokenType & correspondingTokenType) {
    // convert the input character into an input character type
	CharacterType charType = BAD_CHAR;

	bool is_digit = std::regex_match( string( 1,currentCharacter ), regex( "[0-9]" ));
	bool is_alpha = std::regex_match( string( 1,currentCharacter ), regex( "[a-zA-Z]" ));
	bool is_whitespace = std::regex_match( string( 1,currentCharacter ), regex( "[[:space:]]" ));

	switch ( currentCharacter ) {
		case '+': charType = PLUS_CHAR; break;
		case '(': charType = LPAREN_CHAR; break;
		case ')': charType = RPAREN_CHAR; break;
		case '_': charType = UNDERSCORE_CHAR; break;
		case '<': charType = LESS_CHAR; break;
		case '{': charType = LCURLY_CHAR; break;
		case '}': charType = RPAREN_CHAR; break;
		case '=': charType = EQUAL_CHAR; break;
		case ';': charType = SEMICOLON_CHAR; break;
		case '/': charType = DIVIDE_CHAR; break;
		case '*': charType = STAR_CHAR; break;
		case '!': charType = NOT_CHAR; break;
		default:  charType = BAD_CHAR; break;
	}

	if ( is_digit ) charType = DIGIT_CHAR;
	if ( is_alpha ) charType = LETTER_CHAR;
	if ( is_whitespace ) charType = WHITESPACE_CHAR;
	if ( currentCharacter == EOF ) charType = ENDFILE_CHAR;
	if ( currentCharacter == '\n' ) charType = RETURN_CHAR;

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}




	// else if ( currentCharacter == '+' ) charType = PLUS_CHAR;
	// else if ( currentCharacter == '(' ) charType = LPAREN_CHAR;
	// else if ( currentCharacter == ')' ) charType = RPAREN_CHAR;
	// else if ( currentCharacter == '_' ) charType = UNDERSCORE_CHAR;
	// else if ( currentCharacter == '<' ) charType = LESS_CHAR;
	// else if ( currentCharacter == '{' ) charType = LCURLY_CHAR;
	// else if ( currentCharacter == '}' ) charType = RPAREN_CHAR;
	// else if ( currentCharacter == '=' ) charType = EQUAL_CHAR;
	// else if ( currentCharacter == ';' ) charType = SEMICOLON_CHAR;
	// else if ( currentCharacter == EOF ) {
	// 	charType = ENDFILE_CHAR;
	// } else {
	// 	return BAD_STATE;
	// }