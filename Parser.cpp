#include "include/Parser.h"

using namespace std;

StartNode * ParserClass::Start() {
    ProgramNode * programNode = Program();
    Match(ENDFILE_TOKEN);
    StartNode * startNode = new StartNode(programNode);
    return startNode;
}

ParserClass::~ParserClass() {
    // if (mScanner) {
        // delete mScanner;
    // }
}

ProgramNode * ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode * blockNode = Block();
    ProgramNode * programNode = new ProgramNode(blockNode);
    return programNode;
}

BlockNode * ParserClass::Block() {
    Match(LCURLY_TOKEN);
    BlockNode * blockNode = new BlockNode(StatementGroup());
    Match(RCURLY_TOKEN);
    return blockNode;
}

StatementGroupNode * ParserClass::StatementGroup() {
    StatementGroupNode * statementGroupNode = new StatementGroupNode();
    StatementNode * statementNode;
    do {
        statementNode = Statement();
        if (statementNode != NULL) statementGroupNode->AddStatement(statementNode);
    } while ( statementNode != NULL );
    return statementGroupNode;
}

StatementNode * ParserClass::Statement() {
    TokenClass tc = mScanner->PeekNextToken();
    if (tc.GetTokenType() == INT_TOKEN) {
        DeclarationStatementNode * declarationStatementNode = DeclarationStatement();
        return declarationStatementNode;
    } else if (tc.GetTokenType() == IDENTIFIER_TOKEN) {
        AssignmentStatementNode * assignmentStatementNode = AssignmentStatement();
        return assignmentStatementNode;
    } else if (tc.GetTokenType() == COUT_TOKEN) {
        CoutStatementNode * coutStatementNode = CoutStatement();
        return coutStatementNode;
    }
    return NULL;
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    IdentifierNode * identifierNode = Identifier();
    DeclarationStatementNode * declarationStatementNode = new DeclarationStatementNode(identifierNode);
    Match(SEMICOLON_TOKEN);
    return declarationStatementNode;
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {

    IdentifierNode * identifierNode = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode * expressionNode = Expression();
    Match(SEMICOLON_TOKEN);
    return NULL;
}

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
    return NULL;
}

IdentifierNode * ParserClass::Identifier() {
    // Match(IDENTIFIER_TOKEN);
    TokenClass tt = Match(IDENTIFIER_TOKEN);
    IdentifierNode * identifierNode = new IdentifierNode(tt.GetLexeme(), mSymbolTable);
    return identifierNode;
    // check if already exists after you match tt
    // mSymbolTable->AddEntry(tt.GetLexeme()); // lexeme is i
}

void ParserClass::Integer() {
    Match(INTEGER_TOKEN);
}

ExpressionNode * ParserClass::Expression() {
    Relational();
    return NULL;
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

