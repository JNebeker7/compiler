#pragma once
#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class SymbolTable {
public:
    struct Variable {
        string mLabel;
        int mValue;
    };
    SymbolTable();
    bool Exists(const string & s);
    void AddEntry(const string & s);
    int GetValue(const string & s);
    void SetValue(const string & s, int v);
    int GetIndex(const string & s);
    int GetCount();

    void CoutVariables();

    // bool operator==(const string & rhs) const;
private:
    std::vector<Variable> variables;
};


#endif /* _SYMBOL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */