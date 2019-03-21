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
        return DeclarationStatement();
    } else if (tc.GetTokenType() == IDENTIFIER_TOKEN) {
        return AssignmentStatement();
    } else if (tc.GetTokenType() == COUT_TOKEN) {
        return CoutStatement();
    }
    return false;
}

bool ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    Identifier();
    Match(SEMICOLON_TOKEN);
    return true;
}

bool ParserClass::AssignmentStatement() {
    Identifier();
    Match(ASSIGNMENT_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
    return true;
}

bool ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
    return true;
}

void ParserClass::Identifier() {
    Match(IDENTIFIER_TOKEN);
    // TokenClass tt = Match(IDENTIFIER_TOKEN);
    // check if already exists after you match tt
    // mSymbolTable->AddEntry(tt.GetLexeme()); // lexeme is i
}

void ParserClass::Integer() {
    Match(INTEGER_TOKEN);
}

void ParserClass::Expression() {
    Relational();
}

void ParserClass::Relational() {
    PlusMinus();
    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    switch (tt)
    {
        case LESS_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        case LESSEQUAL_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        case GREATER_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        case GREATEREQUAL_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        case EQUAL_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        case NOTEQUAL_TOKEN:
            Match(tt);
            PlusMinus();
            break;
        default:
            return;
    }
}

void ParserClass::PlusMinus() {
    TimesDivide();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case PLUS_TOKEN:
                Match(tt);
                TimesDivide();
                break;
            case MINUS_TOKEN:
                Match(tt);
                TimesDivide();
                break;
            default:
                return;
        }
    }
}

void ParserClass::TimesDivide() {
    Factor();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case TIMES_TOKEN:
                Match(tt);
                break;
            case DIVIDE_TOKEN:
                Match(tt);
                break;
            default:
                return;
        }
    }
}

void ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    switch (tt)
    {
        case IDENTIFIER_TOKEN:
            Identifier();
            break;
        case INTEGER_TOKEN:
            Integer();
            break;
        case LPAREN_TOKEN:
            Match(LPAREN_TOKEN);
            Expression();
            Match(RPAREN_TOKEN);
            break;
        default:
            cerr << "There was an error in the Factor method" << endl;
            exit(1);
            break;
    }
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

