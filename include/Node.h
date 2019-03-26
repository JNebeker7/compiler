#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include "Symbol.h"
#include "Debug.h"
#include <vector>
#include <string>

using namespace std;

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementNode;
class StatementGroupNode;
class DeclarationStatementNode;
class IdentifierNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;

class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
};

class StartNode : public Node {
public:
    StartNode( ProgramNode * ProgramNode ) : mProgramNode(ProgramNode) {};
    ~StartNode();
    void Interpret();
private:
    ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
    ProgramNode( BlockNode * BlockNode ) : mBlockNode(BlockNode) {};
    ~ProgramNode();
    void Interpret();
private:
    BlockNode * mBlockNode;
};

class BlockNode : public Node {
public:
    BlockNode( StatementGroupNode * StatementGroupNode ) : mStatementGroupNode(StatementGroupNode) {};
    ~BlockNode();
    void Interpret();
private:
    StatementGroupNode * mStatementGroupNode;
};

class StatementNode : public Node {
};

class StatementGroupNode : public Node {
public:
    StatementGroupNode() {};
    ~StatementGroupNode();
    void AddStatement( StatementNode * StatementNode );
    void Interpret();
private:
    vector<StatementNode *> mStatementGroupNodes;
};

class DeclarationStatementNode : public StatementNode {
public:
    DeclarationStatementNode(IdentifierNode * IdentifierNode) 
                            : mIdentifierNode(IdentifierNode) {};
    ~DeclarationStatementNode();
    void Interpret();
protected:
    IdentifierNode * mIdentifierNode;
};

// // 8
class AssignmentStatementNode : public StatementNode {
public:
    AssignmentStatementNode(IdentifierNode * IdentifierNode, ExpressionNode * ExpressionNode) 
                            : mIdentifierNode(IdentifierNode), mExpressionNode(ExpressionNode) {};
    ~AssignmentStatementNode();
    void Interpret();
private:
    IdentifierNode * mIdentifierNode;
    ExpressionNode * mExpressionNode;
};

// // 9
class CoutStatementNode : public StatementNode {
public:
    CoutStatementNode(ExpressionNode * express)
                        : mExpressionNode(express) {};
    ~CoutStatementNode();
    void Interpret();
private:
    ExpressionNode * mExpressionNode;
};

// // 10
class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;   
};

// // 11
class IntegerNode : public ExpressionNode {
public:
    IntegerNode(int value)
                : mValue(value) {};
    ~IntegerNode();
    int Evaluate();
private:
    int mValue;
};

// // 12
class IdentifierNode : public ExpressionNode {
public:
    IdentifierNode(string label, SymbolTable * SymbolTable)
                    : mLabel(label), mSymbolTable(SymbolTable) {};
    ~IdentifierNode();
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();
private:
    string mLabel;
    SymbolTable * mSymbolTable;
};

// // 13
class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(ExpressionNode * left, ExpressionNode * right)
                        : mLeft(left), mRight(right) {};
    ~BinaryOperatorNode();
    virtual int Evaluate() = 0;
protected:
    ExpressionNode * mLeft;
    ExpressionNode * mRight;
};

// // 14
class PlusNode : public BinaryOperatorNode {
public:
    PlusNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

// chapter 5
class MinusNode : public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class TimesNode : public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class DivideNode : public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class LessNode : public BinaryOperatorNode {
public:
    LessNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class GreaterNode : public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class EqualNode : public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};



#endif /* _NODE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */