#include "include/Parser.h"

using namespace std;

StartNode * ParserClass::Start() {
    ProgramNode * programNode = Program();
    Match(ENDFILE_TOKEN);
    this->start = new StartNode(programNode);
    return this->start;
}

ParserClass::~ParserClass() {
    MSG("Delete Start");
    delete this->start;
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
    // TokenClass tc = mScanner->PeekNextToken();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if ( tt == INT_TOKEN ) {
        DeclarationStatementNode * declarationStatementNode = DeclarationStatement();
        return declarationStatementNode;
    } else if ( tt == IDENTIFIER_TOKEN ) {
        AssignmentStatementNode * assignmentStatementNode = AssignmentStatement();
        return assignmentStatementNode;
    } else if ( tt == COUT_TOKEN ) {
        CoutStatementNode * coutStatementNode = CoutStatement();
        return coutStatementNode;
    } else if ( tt == IF_TOKEN ) {
        IfStatementNode * ifStatementNode = IfStatement();
        return ifStatementNode;
    } else if ( tt == WHILE_TOKEN ) {
        WhileStatementNode * whileStatement = WhileStatement();
        return whileStatement;
    } else if ( tt == DO_TOKEN ) {
        DoWhileStatementNode * doWhileStatement = DoWhileStatement();
        return doWhileStatement;
    } else if ( tt == LCURLY_TOKEN ) {
        BlockNode * blockNode = Block();
        return blockNode;
    } else if ( tt == REPEAT_TOKEN ) {
        RepeatNode * repeatNode = Repeat();
        return repeatNode;
        // cout << "found repeat token" << endl;
    }
    return NULL;
}

RepeatNode * ParserClass::Repeat() {
    Match(REPEAT_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expressionNode = Expression();
    // cout << "lockin " << expressionNode->Evaluate() << endl;
    Match(RPAREN_TOKEN);
    StatementNode * statementNode = Statement();
    RepeatNode * r = new RepeatNode(expressionNode, statementNode);
    return r;
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    IdentifierNode * identifierNode = Identifier();
    // 
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    ExpressionNode * expression;
    if (tt == ASSIGNMENT_TOKEN) {
        Match(tt);
        expression = Expression();
        // Match(SEMICOLON_TOKEN);
    }
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode * declarationStatementNode = new DeclarationStatementNode(identifierNode, expression);
    return declarationStatementNode;
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {
    IdentifierNode * identifierNode = Identifier();
    ExpressionNode * expressionNode;
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if ( tt == PLUSEQUAL_TOKEN ) {
        Match(tt);
        expressionNode = Expression();
        Match(SEMICOLON_TOKEN);
        PlusEqualNode * plusEqualNode = new PlusEqualNode(identifierNode, expressionNode);
        return plusEqualNode;
    } else if ( tt == MINUSEQUAL_TOKEN ) {
        Match(tt);
        expressionNode = Expression();
        Match(SEMICOLON_TOKEN);
        MinusEqualNode * minusEqualNode = new MinusEqualNode(identifierNode, expressionNode);
        return minusEqualNode;
    } else if ( tt == ASSIGNMENT_TOKEN ) {
        Match(tt);
        expressionNode = Expression();
        Match(SEMICOLON_TOKEN);
        AssignmentStatementNode * asn = new AssignmentStatementNode(identifierNode, expressionNode);
        return asn;
    } else {
        return NULL;
    }

}

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    CoutStatementNode * coutStatementNode = new CoutStatementNode();
    TokenType tt;

    while(tt != SEMICOLON_TOKEN) {
        Match(INSERTION_TOKEN);
        tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == ENDL_TOKEN) {
            Match(ENDL_TOKEN);
            coutStatementNode->AddExpression(NULL);
        } else {
            coutStatementNode->AddExpression(Expression());
        }
        tt = mScanner->PeekNextToken().GetTokenType();
    }
    Match(SEMICOLON_TOKEN);
    return coutStatementNode;
}

IfStatementNode * ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expressionNode = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * statement1, * statement2;
    statement1 = Statement();
    statement2 = NULL;
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if ( tt == ELSE_TOKEN ) {
        Match(tt);
        statement2 = Statement();
    }
    IfStatementNode * ifStatmentnode = new IfStatementNode(expressionNode, statement1, statement2);
    return ifStatmentnode;
}

WhileStatementNode * ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expressionNode = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * statementNode = Statement();
    WhileStatementNode * whileStatementNode = new WhileStatementNode(expressionNode, statementNode);
    return whileStatementNode;
}

DoWhileStatementNode * ParserClass::DoWhileStatement() {
    Match(DO_TOKEN);
    StatementNode * statementNode = Statement();
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expressionNode = Expression();
    Match(RPAREN_TOKEN);
    Match(SEMICOLON_TOKEN);
    DoWhileStatementNode * doWhileStatement = new DoWhileStatementNode(expressionNode, statementNode);
    return doWhileStatement;
    // do
    // {
    //     /* mStatement->Interpret(); */
    // } while (/* mExpression->Evaluate() */);
    
}

IdentifierNode * ParserClass::Identifier() {
    TokenClass tt = Match(IDENTIFIER_TOKEN);
    // peek for '=' #4 of practice    
    IdentifierNode * identifierNode = new IdentifierNode(tt.GetLexeme(), mSymbolTable);
    return identifierNode;
}

ExpressionNode * ParserClass::Integer() {
    TokenClass tt = Match(INTEGER_TOKEN);
    return new IntegerNode(atoi(tt.GetLexeme().c_str()));
}

ExpressionNode * ParserClass::Expression() {
    // call logical or -> logical and -> relational -> plus minus -> times divide -> factor
    ExpressionNode * expressionNode = LogicalOR();
    return expressionNode;
}

ExpressionNode * ParserClass::LogicalOR() {
    ExpressionNode * current = LogicalAND();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if ( tt == LOR_TOKEN ) {
            Match(tt);
            ExpressionNode * rhs = LogicalAND();
            LogicalORnode * logicalORnode = new LogicalORnode(current, rhs);
            return logicalORnode;
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::LogicalAND() {
    ExpressionNode * current = Relational();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if ( tt == LAND_TOKEN ) {
            Match(tt);
            ExpressionNode * rhs = Relational();
            LogicalANDnode * logicalANDnode = new LogicalANDnode(current, rhs);
            return logicalANDnode;
        } else {
            return current;
        }
    }
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
    ExpressionNode * current = Exponent();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case TIMES_TOKEN:
                Match(tt);
                current = new TimesNode( current, Exponent() );
                break;
            case DIVIDE_TOKEN:
                Match(tt);
                current = new DivideNode( current, Exponent() );
                break;
            default:
                return current;
        }
    }
}

ExpressionNode * ParserClass::Exponent() {
    ExpressionNode * current = Factor();
    while ( true ) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        switch (tt)
        {
            case EXPONENT_TOKEN:
                Match(tt);
                current = new ExponentNode( current, Factor() );
                break;
            case MOD_TOKEN:
                Match(tt);
                current = new ModNode( current, Factor() );
                break;
            default:
                return current;
                break;
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

