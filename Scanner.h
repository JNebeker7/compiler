#pragma once
#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "Token.h"
#include <fstream>

using std::ifstream;

class ScannerClass {
private:
    ifstream mFin;
    int mLineNumber;
public:
    ScannerClass( string file );
    TokenClass GetNextToken();
    int getLineNumber();
};



#endif /* _SCANNER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */