#include "include/Parser.h"

using namespace std;

void ParserClass::Start() {
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    Block();
}

void ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroup();
    Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    bool found = true;
    do {
        found = Statement();
    } while ( found == true );
}

bool ParserClass::Statement() {
    TokenClass tc = mScanner->PeekNextToken();
    if (tc.GetTokenType() == INT_TOKEN) {
        // int token
        IntegerStatement();
        // semi colon token
    } else if (tc.GetTokenType() == IDENTIFIER_TOKEN) {
        IdentifierStatement();
        // assignment token
        // Expression()
        // Semi colon token
    } else if (tc.GetTokenType() == COUT_TOKEN) {
        // cout token
        // insertion token
        CoutStatement();
        // semi colon token
    }
    return false;
}

bool ParserClass::IntegerStatement() {
    return true;
}

bool ParserClass::IdentifierStatement() {
    return true;
}

bool ParserClass::CoutStatement() {
    return true;
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass currentToken = mScanner->GetNextToken();
    if (currentToken.GetTokenType() != expectedType) {
        cerr << "Error in ParserClass::Match. " << endl;
        cerr << "Expected token type " <<
            TokenClass::GetTokenTypeName(expectedType) <<
            ", but got type " << currentToken.GetTokenTypeName()
            << endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " <<
        currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
        currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed.
}

