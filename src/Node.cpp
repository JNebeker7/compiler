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

DeclarationStatmentNode::~DeclarationStatmentNode() {
    delete this->mIdentifierNode;
}

AssignmentStatementNode::~AssignmentStatementNode() {
    delete this->mExpressionNode;
    delete this->mIdentifierNode;
}

CoutStatementNode::~CoutStatementNode() {
    delete this->mExpressionNode;
}

IntegerNode::~IntegerNode() {
    
}

int IntegerNode::Evaluate() {
    return this->mValue;
}

void IdentifierNode::DeclareVariable() {
    this->mSymbolTable->AddEntry(this->mLabel);
}

void IdentifierNode::SetValue(int v) {
    this->mSymbolTable->SetValue(this->mLabel, v);
}

int IdentifierNode::GetIndex() {
    return this->mSymbolTable->GetIndex(this->mLabel);
}

int IdentifierNode::Evaluate() {
    return this->mSymbolTable->GetValue(this->mLabel);
}

BinaryOperatorNode::~BinaryOperatorNode() {
    delete this->mLeft; delete this->mRight;
}

int PlusNode::Evaluate() {
    return this->mLeft->Evaluate() + this->mRight->Evaluate();
}