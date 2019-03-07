#include "../include/Token.h"
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
    
}

ostream & operator<<(ostream & out, const TokenClass & tc) {
    switch (tc.GetTokenType())
    {
        case 10:
            out << tc.GetLexeme() << "   | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]  |";
            return out;
        case 12:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]       |";
            return out;
        case 16:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]  |";
            return out;
        case 17:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]     |";
            return out;
        case 18:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]     |";
            return out;
        case 19:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]     |";
            return out;
        case 11:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "] |";
            return out;
        case 2:
            out << tc.GetLexeme() << "  | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]         |";
            return out;
        case 21:
            out << tc.GetLexeme() << "  | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "] |";
            return out;
        case 24:
            out << tc.GetLexeme() << "    | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]    |";
            return out;
        case 22:
            if ( stoi(tc.GetLexeme()) >= 100 ) {
                // std::cout << "hello world" << std::endl;
                out << tc.GetLexeme() << "  | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]    |";
                return out;
            }
            out << tc.GetLexeme() << "   | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]    |";
            return out;
        default:
            out << tc.GetLexeme() << " | " << tc.GetTokenTypeName() << "[" << tc.GetTokenType() << "]        |";
            return out;
    }
}