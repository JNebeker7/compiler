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
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode * declarationStatementNode = new DeclarationStatementNode(identifierNode);
    return declarationStatementNode;
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {

    IdentifierNode * identifierNode = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode * expressionNode = Expression();
    Match(SEMICOLON_TOKEN);
    AssignmentStatementNode * asn = new AssignmentStatementNode(identifierNode, expressionNode);
    return asn;
}

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode * expressionNode =  Expression();
    Match(SEMICOLON_TOKEN);
    CoutStatementNode * coutStatementNode = new CoutStatementNode(expressionNode);
    return coutStatementNode;
}

IdentifierNode * ParserClass::Identifier() {
    TokenClass tt = Match(IDENTIFIER_TOKEN);
    IdentifierNode * identifierNode = new IdentifierNode(tt.GetLexeme(), mSymbolTable);
    return identifierNode;
}

ExpressionNode * ParserClass::Integer() {
    TokenClass tt = Match(INTEGER_TOKEN);
    return new IntegerNode(atoi(tt.GetLexeme().c_str()));
}

ExpressionNode * ParserClass::Expression() {
    // call logical or -> logical and -> relational -> plus minus -> times divide -> factor
    ExpressionNode * relational = Relational();
    return relational;
}

ExpressionNode * ParserClass::Relational() {
    ExpressionNode * current = PlusMinus();
    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    ExpressionNode * rhs;
    switch (tt)
    {
        case LESS_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new LessNode( current, rhs );
            break;
        case LESSEQUAL_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new LessEqualNode( current, rhs );
            break;
        case GREATER_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new GreaterNode( current, rhs );
            break;
        case GREATEREQUAL_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new GreaterEqualNode( current, rhs );
            break;
        case EQUAL_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new EqualNode( current, rhs );
            break;
        case NOTEQUAL_TOKEN:
            Match(tt);
            rhs = PlusMinus();
            return new NotEqualNode( current, rhs );
            break;
        default:
            return current;
    }
}

ExpressionNode * ParserClass::PlusMinus() {
    ExpressionNode * current = TimesDivide();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case PLUS_TOKEN:
                Match(tt);
                current = new PlusNode( current, TimesDivide() );
                break;
            case MINUS_TOKEN:
                Match(tt);
                current = new MinusNode( current, TimesDivide() );
                break;
            default:
                return current;
        }
    }
}

ExpressionNode * ParserClass::TimesDivide() {
    ExpressionNode * current = Factor();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case TIMES_TOKEN:
                Match(tt);
                current = new TimesNode( current, Factor() );
                break;
            case DIVIDE_TOKEN:
                Match(tt);
                current = new DivideNode( current, Factor() );
                break;
            default:
                return current;
        }
    }
}

ExpressionNode * ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    ExpressionNode * expression;
    switch (tt)
    {
        case IDENTIFIER_TOKEN:
            return Identifier();
            break;
        case INTEGER_TOKEN:
            return Integer();
            break;
        case LPAREN_TOKEN:
            Match(LPAREN_TOKEN);
            expression = Expression();
            Match(RPAREN_TOKEN);
            return expression;
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

