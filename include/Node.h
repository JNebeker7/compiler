#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include "Symbol.h"
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
private:
    ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
    ProgramNode( BlockNode * BlockNode ) : mBlockNode(BlockNode) {};
    ~ProgramNode();
private:
    BlockNode * mBlockNode;
};

class BlockNode : public Node {
public:
    BlockNode( StatementGroupNode * StatementGroupNode ) : mStatementGroupNode(StatementGroupNode) {};
    ~BlockNode();
private:
    StatementGroupNode * mStatementGroupNode;
};

class StatementNode : public Node {
};

class StatementGroupNode : public Node {
public:
    StatementGroupNode();
    ~StatementGroupNode();
    void AddStatement( StatementNode * StatementNode );
private:
    vector<StatementNode *> mStatementGroupNodes;
};

class DeclarationStatmentNode : public StatementNode {
public:
    DeclarationStatmentNode(IdentifierNode * IdentifierNode) 
                            : mIdentifierNode(IdentifierNode) {};
    ~DeclarationStatmentNode();
protected:
    IdentifierNode * mIdentifierNode;
};

// 8
class AssignmentStatementNode : public StatementNode {
public:
    AssignmentStatementNode(IdentifierNode * IdentifierNode, ExpressionNode * ExpressionNode) 
                            : mIdentifierNode(IdentifierNode), mExpressionNode(ExpressionNode) {};
    ~AssignmentStatementNode();
private:
    IdentifierNode * mIdentifierNode;
    ExpressionNode * mExpressionNode;
};

// 9
class CoutStatementNode : public StatementNode {
public:
    CoutStatementNode();
    ~CoutStatementNode();
private:
    ExpressionNode * mExpressionNode;
};

// 10
class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;   
};

// 11
class IntegerNode : public ExpressionNode {
public:
    IntegerNode(int value)
                : mValue(value) {};
    int Evaluate();
private:
    int mValue;
};

// 12
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

// 13
class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(ExpressionNode * left, ExpressionNode * right)
                        : mLeft(left), mRight(right) {};
    ~BinaryOperatorNode();
    // virtual int Evaluate() = 0;
protected:
    ExpressionNode * mLeft;
    ExpressionNode * mRight;
};

// 14
class PlusNode : public BinaryOperatorNode {
public:
    PlusNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    int Evaluate();
};


#endif /* _NODE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */