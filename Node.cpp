#include "include/Node.h"

Node::~Node(){
    // MSG("NODE DELETE");
}
StartNode::~StartNode() {
    MSG("START DELETE");
    delete this->mProgramNode; 
}
ProgramNode::~ProgramNode() {
    MSG("PROGRAM DELETE");
    delete this->mBlockNode;
}
BlockNode::~BlockNode() {
    MSG("BLOCK DELETE");
    delete this->mStatementGroupNode;
}
// IntegerNode::~IntegerNode() {}

void StartNode::Interpret() {

}

void ProgramNode::Interpret() {

}

void BlockNode::Interpret() {

}

void StatementGroupNode::Interpret() {
    
}

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

// DeclarationStatmentNode::~DeclarationStatmentNode() {
//     delete this->mIdentifierNode;
// }

// AssignmentStatementNode::~AssignmentStatementNode() {
//     delete this->mExpressionNode;
//     delete this->mIdentifierNode;
// }

// CoutStatementNode::~CoutStatementNode() {
//     delete this->mExpressionNode;
// }

// int IntegerNode::Evaluate() {
//     return this->mValue;
// }

// void IdentifierNode::DeclareVariable() {
//     this->mSymbolTable->AddEntry(this->mLabel);
// }

// void IdentifierNode::SetValue(int v) {
//     this->mSymbolTable->SetValue(this->mLabel, v);
// }

// int IdentifierNode::GetIndex() {
//     return this->mSymbolTable->GetIndex(this->mLabel);
// }

// int IdentifierNode::Evaluate() {
//     return this->mSymbolTable->GetValue(this->mLabel);
// }

// BinaryOperatorNode::~BinaryOperatorNode() {
//     delete this->mLeft; delete this->mRight;
// }

// int PlusNode::Evaluate() {
//     return this->mLeft->Evaluate() + this->mRight->Evaluate();
// }