#include "../include/Node.h"

Node::~Node(){}
StartNode::~StartNode() { delete this->mProgramNode; }
ProgramNode::~ProgramNode() { delete this->mBlockNode; }
BlockNode::~BlockNode() { delete this->mStatementGroupNode; }

void StatementGroupNode::AddStatement( StatementNode * StatementNode ) {
    this->mStatementGroupNodes.push_back( StatementNode );
}
StatementGroupNode::~StatementGroupNode() {
    for (int i = 0; i < mStatementGroupNodes.size(); i++) {
        delete mStatementGroupNodes[i];
    }
}