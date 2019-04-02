#include "include/Token.h"
#include <iostream>
#include <iomanip>

using std::setw;

using namespace std;

TokenClass::TokenClass() {
    // default constructor
}

TokenClass::TokenClass( TokenType tt, const string & lexeme ) 
    : mType( tt ), mLexeme( lexeme ) {

}

void TokenClass::CheckReserved() {
    if ( mLexeme == "void" ) mType = VOID_TOKEN;
    if ( mLexeme == "main" ) mType = MAIN_TOKEN;
    if ( mLexeme == "int" ) mType = INT_TOKEN;
    if ( mLexeme == "cout" ) mType = COUT_TOKEN;
    if ( mLexeme == "if" ) mType = IF_TOKEN;
}

ostream & operator<<(ostream & out, const TokenClass & tc) {
    out << tc.GetLexeme() << " | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]";
    return out;
}
