#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include <vector>

using namespace std;

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementNode;
class StatementGroupNode;
class DeclarationStatementNode;

class Node {
public:
    virtual ~Node();
};

class StartNode : public Node {
public:
    StartNode( ProgramNode * ProgramNode ) :mProgramNode(ProgramNode) {};
    ~StartNode();
private:
    ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
    ProgramNode( BlockNode * BlockNode ) :mBlockNode(BlockNode) {};
    ~ProgramNode();
private:
    BlockNode * mBlockNode;
};

class BlockNode : public Node {
public:
    BlockNode( StatementGroupNode * StatementGroupNode ) :mStatementGroupNode(StatementGroupNode) {};
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

// #7


#endif /* _NODE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */