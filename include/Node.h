#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include "Symbol.h"
#include "Debug.h"
#include "Instructions.h"
#include <vector>
#include <string>
#include <math.h>

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
class IfStatementNode;
class WhileStatementNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;
class PlusEqualNode;
class MinusNode;
class TimesNode;
class ExponentNode;
class DivideNode;
class RepeatNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;
class LogicalANDnode;
class LogicalORnode;

// Node
// StartNode
// ProgramNode
// BlockNode
// StatementGroupNode   **** This will call Code on all of the items in its vector
//    DeclarationStatementNode  
//    CoutStatementNode
//    AssignmentStatementNode


// *** Interpret calls evaluate & Code calls codeEvaluate


class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass &code) = 0;
};

class StartNode : public Node {
public:
    StartNode( ProgramNode * ProgramNode ) : mProgramNode(ProgramNode) {};
    ~StartNode();
    void Interpret();
    void Code( InstructionsClass &code );
private:
    ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
    ProgramNode( BlockNode * BlockNode ) : mBlockNode(BlockNode) {};
    ~ProgramNode();
    void Interpret();
    void Code( InstructionsClass &code );
private:
    BlockNode * mBlockNode;
};

class StatementNode : public Node {
public:
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass &code) = 0;
};

class StatementGroupNode : public Node {
public:
    StatementGroupNode() {};
    ~StatementGroupNode();
    void AddStatement( StatementNode * StatementNode );
    virtual void Interpret();
    void Code( InstructionsClass &code );
private:
    vector<StatementNode *> mStatementGroupNodes;
};

class BlockNode : public StatementNode {
public:
    BlockNode( StatementGroupNode * StatementGroupNode ) : mStatementGroupNode(StatementGroupNode) {};
    ~BlockNode();
    void Interpret();
    void Code( InstructionsClass &code );
private:
    StatementGroupNode * mStatementGroupNode;
};

class DeclarationStatementNode : public StatementNode {
public:
    DeclarationStatementNode(IdentifierNode * IdentifierNode) 
                            : mIdentifierNode(IdentifierNode) {};
    ~DeclarationStatementNode();
    virtual void Interpret();
    void Code( InstructionsClass &code );
protected:
    IdentifierNode * mIdentifierNode;
};

// // 8
class AssignmentStatementNode : public StatementNode {
public:
    AssignmentStatementNode(IdentifierNode * IdentifierNode, ExpressionNode * ExpressionNode) 
                            : mIdentifierNode(IdentifierNode), mExpressionNode(ExpressionNode) {};
    ~AssignmentStatementNode();
    IdentifierNode * getIdentifier() {
        return this->mIdentifierNode;
    };
    ExpressionNode * getExpression() {
        return this->mExpressionNode;
    };
    virtual void Interpret();
    virtual void Code( InstructionsClass &code );
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
    virtual void Interpret();
    virtual void Code( InstructionsClass &code );
private:
    ExpressionNode * mExpressionNode;
};

class IfStatementNode : public StatementNode {
public:
    IfStatementNode(ExpressionNode * expression = NULL, StatementNode * sn1 = NULL, StatementNode * sn2 = NULL)
        : mExpression(expression), mStatement1(sn1), mStatement2(sn2) {};
    ~IfStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &code);
private:
    ExpressionNode * mExpression;
    StatementNode * mStatement1;
    StatementNode * mStatement2;
};

class WhileStatementNode : public StatementNode {
public:
    WhileStatementNode(ExpressionNode * expression, StatementNode * statement)
        : mExpression(expression), mStatement(statement) {};
    ~WhileStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &code);
private:
    ExpressionNode * mExpression;
    StatementNode * mStatement;
};

class RepeatNode : public StatementNode {
public:
    RepeatNode(ExpressionNode * expression, StatementNode * statement)
        : mExpression(expression), mStatement(statement) {};
    ~RepeatNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &code);
private:
    ExpressionNode * mExpression;
    StatementNode * mStatement;
};

// // 10
class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass &code) = 0;
};

// // 11
class IntegerNode : public ExpressionNode {
public:
    IntegerNode(int value)
                : mValue(value) {};
    ~IntegerNode();
    int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
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
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
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
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class PlusEqualNode : public AssignmentStatementNode {
public:
    PlusEqualNode(IdentifierNode * left, ExpressionNode * right)
        : AssignmentStatementNode(left, right) {};
    virtual void Interpret();
    virtual void Code(InstructionsClass &code);
};

// chapter 5
class MinusNode : public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class TimesNode : public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class ExponentNode : public BinaryOperatorNode {
public:
    ExponentNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class DivideNode : public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class LessNode : public BinaryOperatorNode {
public:
    LessNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class LessEqualNode : public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class GreaterNode : public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class EqualNode : public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class NotEqualNode : public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class LogicalANDnode : public BinaryOperatorNode {
public:
    LogicalANDnode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};

class LogicalORnode : public BinaryOperatorNode {
public:
    LogicalORnode(ExpressionNode * left, ExpressionNode * right)
        : BinaryOperatorNode(left, right) {};
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &code);
};



#endif /* _NODE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */