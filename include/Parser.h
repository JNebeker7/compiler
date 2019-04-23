#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include "Debug.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include <iostream>

class ParserClass {
public:
    ParserClass(ScannerClass *scanner, SymbolTable *symbolTable)
        : mScanner(scanner), mSymbolTable(symbolTable) {};
    ~ParserClass();
    StartNode * Start();
    ProgramNode * Program();
    BlockNode * Block();
    StatementGroupNode * StatementGroup();
    StatementNode * Statement();
    DeclarationStatementNode * DeclarationStatement();
    RepeatNode * Repeat();
    AssignmentStatementNode * AssignmentStatement();
    CoutStatementNode * CoutStatement();
    IfStatementNode * IfStatement();
    WhileStatementNode * WhileStatement();
    DoWhileStatementNode * DoWhileStatement();
    IdentifierNode * Identifier();
    ExpressionNode * Integer();
    ExpressionNode * Expression();
    ExpressionNode * LogicalOR();
    ExpressionNode * LogicalAND();
    ExpressionNode * Relational();
    ExpressionNode * PlusMinus();
    ExpressionNode * TimesDivide();
    ExpressionNode * Exponent();
    ExpressionNode * Factor();
    TokenClass Match(TokenType expectedType);
private:
    ScannerClass * mScanner;
    SymbolTable * mSymbolTable;
    StartNode * start;
};



#endif /* _PARSER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */