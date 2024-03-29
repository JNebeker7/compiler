#include "include/Symbol.h"
#include <algorithm>
#include "include/Debug.h"

using namespace std;
using std::cout;
using std::endl;


SymbolTable::SymbolTable() {    
    // variables.push_back(Variable());
    // variables[0].mLabel = "init";
    // variables[0].mValue = -1;
}

// returns true if <s> is already in the symbol table.
bool SymbolTable::Exists(const string & s) {
    
    for (int i = 0; i < variables.size(); i++) {
        if ( variables[i].mLabel == s )
            return true;
    }
    return false;
}

// adds <s> to the symbol table, 
// or quits if it was already there
void SymbolTable::AddEntry(const std::string & s) {
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i].mLabel == s) {
            MSG(s << " already exists");
            return;
        }
    }

    Variable v;
    v.mLabel = s;
    v.mValue = -1;
    variables.push_back(v);
}
// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTable::GetValue(const std::string & s) {
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i].mLabel == s)
            return variables[i].mValue;
    }
    MSG("No value for " << s);
    return -1;
}
// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTable::SetValue(const std::string & s, int v) {
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i].mLabel == s)
            variables[i].mValue = v;
    }
}
// returns the index of where variable <s> is.
// returns -1 if variable <s> is not there.
int SymbolTable::GetIndex(const std::string & s) {
    std::vector<Variable>::iterator it;
    it = find_if(
        variables.begin(),
        variables.end(),
        [s] ( const Variable& i ) {
            return i.mLabel == s;
        }
    );
    if ( it != variables.end() ) {
        auto index = distance(variables.begin(), it);
        return index;
    } else {
        auto index = distance(variables.begin(), it);
        return index;
    }
}
// returns the current number of variables in the symbol
// table. 
int SymbolTable::GetCount() {
    return variables.size();
}

void SymbolTable::CoutVariables() {
    for (int i = 0; i < variables.size(); i++) {
        cout << variables[i].mLabel << " " << variables[i].mValue << endl;
    }  
}

// bool SymbolTable::operator==(const string & rhs) const {
//     return true
// }