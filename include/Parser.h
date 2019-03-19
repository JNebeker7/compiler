#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include "Debug.h"
#include "Token.h"
#include "Scanner.h"
#include <iostream>

class ParserClass {
public:
    ParserClass(ScannerClass *scanner)
        : mScanner(scanner) {};
    void Start();
    void Program();
    void Block();
    void StatementGroup();
    TokenClass Match(TokenType expectedType);
private:
    ScannerClass *mScanner;
};



#endif /* _PARSER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */