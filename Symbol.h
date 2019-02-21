#pragma once
#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>
#include <vector>

using namespace std;


class SymbolTable {
public:
    struct Variable {
        string mLabel;
        int mValue;
    };
    SymbolTable();
    bool Exists(const string & s);

private:
    std::vector<Variable> variables;
};

#endif /* _SYMBOL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */