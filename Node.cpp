#include "include/Node.h"

Node::~Node(){
    // MSG("NODE DELETE");
}

StartNode::~StartNode() {
    MSG("START DELETE");
    delete this->mProgramNode; 
}
void StartNode::Interpret() {

}

ProgramNode::~ProgramNode() {
    MSG("PROGRAM DELETE");
    delete this->mBlockNode;
}
void ProgramNode::Interpret() {

}

BlockNode::~BlockNode() {
    MSG("BLOCK DELETE");
    delete this->mStatementGroupNode;
}
void BlockNode::Interpret() {

}
// IntegerNode::~IntegerNode() {}




void StatementGroupNode::AddStatement( StatementNode * StatementNode ) {
    this->mStatementGroupNodes.push_back( StatementNode );
}
StatementGroupNode::~StatementGroupNode() {
    MSG("STATEMENTGROUPNODE DELETE");
    for (int i = 0; i < mStatementGroupNodes.size(); i++) {
        MSG("STATEMENTNODE " << i << " DELETE");
        delete mStatementGroupNodes[i];
    }
}
void StatementGroupNode::Interpret() {
    
}

DeclarationStatmentNode::~DeclarationStatmentNode() {
    delete this->mIdentifierNode;
}
void DeclarationStatmentNode::Interpret() {

}

AssignmentStatementNode::~AssignmentStatementNode() {
    delete this->mExpressionNode;
    delete this->mIdentifierNode;
}
void AssignmentStatementNode::Interpret() {

}

CoutStatementNode::~CoutStatementNode() {
    delete this->mExpressionNode;
}
void CoutStatementNode::Interpret() {
    
}

ExpressionNode::~ExpressionNode() {
    // MSG("")
}

IntegerNode::~IntegerNode() {
    
}
int IntegerNode::Evaluate() {
    return this->mValue;
}

IdentifierNode::~IdentifierNode() {

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

// BinaryOperatorNode::~BinaryOperatorNode() {
//     delete this->mLeft; delete this->mRight;
// }

// int PlusNode::Evaluate() {
//     return this->mLeft->Evaluate() + this->mRight->Evaluate();
// }