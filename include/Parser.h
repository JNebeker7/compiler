#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include "Debug.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include <iostream>

class ParserClass {
public:
    ParserClass(ScannerClass *scanner, SymbolTable *symbolTable)
        : mScanner(scanner), mSymbolTable(symbolTable) {};
    void Start();
    void Program();
    void Block();
    void StatementGroup();
    bool Statement();
    bool DeclarationStatement();
    bool AssignmentStatement();
    bool CoutStatement();
    void Identifier();
    void Expression();
    void Relational();
    void PlusMinus();
    void TimesDivide();
    void Factor();
    void Integer();
    TokenClass Match(TokenType expectedType);
private:
    ScannerClass *mScanner;
    SymbolTable *mSymbolTable;
};



#endif /* _PARSER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */