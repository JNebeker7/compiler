#pragma once
#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

using namespace std;

enum TokenType {
    // Reserved Words:
    VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, ENDL_TOKEN,
    IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, REPEAT_TOKEN,
    // Relational Operators:
    LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
    // Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, MOD_TOKEN,
    EXPONENT_TOKEN, PLUSEQUAL_TOKEN,
    // Other Characters:
    SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
    // Other Token Types:
    IDENTIFIER_TOKEN, INTEGER_TOKEN, LAND_TOKEN, LOR_TOKEN,
    BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const string gTokenTypeNames[] = {
    "VOID", "MAIN", "INT", "COUT", "ENDL",
    "IF_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN", "REPEAT_TOKEN",
    "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
    "INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", "MOD",
    "EXPONENT", "PLUSEQUAL",
    "SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
    "IDENTIFIER", "INTEGER", "LOGICAL AND", "LOGICAL OR"
    "BAD", "ENDFILE"
};

class TokenClass {
    public:
        TokenClass();
        TokenClass(TokenType type, const string & lexeme);
        TokenType GetTokenType() const { return mType; }
        const string & GetTokenTypeName() const { return gTokenTypeNames[mType]; }
        string GetLexeme() const { return mLexeme; }
        void CheckReserved();
        
        static const string & GetTokenTypeName(TokenType type) { return gTokenTypeNames[type]; }
    private:
        TokenType mType;
        string mLexeme;
};

ostream & operator<<(ostream & out, const TokenClass & tc);

#endif /* _TOKEN_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */