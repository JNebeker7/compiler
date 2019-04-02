#include "include/Node.h"

Node::~Node(){
    // MSG("NODE DELETE");
}

StartNode::~StartNode() {
    MSG("START DELETE");
    delete this->mProgramNode; 
}
void StartNode::Interpret() {
    this->mProgramNode->Interpret();
}

ProgramNode::~ProgramNode() {
    MSG("PROGRAM DELETE");
    delete this->mBlockNode;
}
void ProgramNode::Interpret() {
    this->mBlockNode->Interpret();
}

BlockNode::~BlockNode() {
    MSG("BLOCK DELETE");
    delete this->mStatementGroupNode;
}
void BlockNode::Interpret() {
    this->mStatementGroupNode->Interpret();
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
void StatementGroupNode::Interpret() {
    for (int i = 0; i < mStatementGroupNodes.size(); i++) {
        this->mStatementGroupNodes[i]->Interpret();
    }
}

DeclarationStatementNode::~DeclarationStatementNode() {
    // MSG("DECLARATIONSTATEMENT DELETE");
    delete this->mIdentifierNode;
}
void DeclarationStatementNode::Interpret() {
    this->mIdentifierNode->DeclareVariable();
}

AssignmentStatementNode::~AssignmentStatementNode() {
    // MSG("ASSIGNMENTSTATEMENT DELETE")
    delete this->mExpressionNode;
    delete this->mIdentifierNode;
}
void AssignmentStatementNode::Interpret() {
    int val = this->mExpressionNode->Evaluate();
    this->mIdentifierNode->SetValue(val);
}

CoutStatementNode::~CoutStatementNode() {
    // MSG("COUTSTATEMENTNODE DELETE");
    delete this->mExpressionNode;
}
void CoutStatementNode::Interpret() {
    cout << this->mExpressionNode->Evaluate() << endl;
}

ExpressionNode::~ExpressionNode() {
    // MSG("")
}

IntegerNode::~IntegerNode() {
    MSG("INTEGERNODE DELETE");
}
int IntegerNode::Evaluate() {
    return this->mValue;
}

IdentifierNode::~IdentifierNode() {
    MSG("IDENTIFIERNODE DELETE");
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
    MSG("BINARYOPERATORNODE DELETE");
    delete this->mLeft; delete this->mRight;
}

int PlusNode::Evaluate() {
    return this->mLeft->Evaluate() + this->mRight->Evaluate();
}

int MinusNode::Evaluate() {
    return this->mLeft->Evaluate() - this->mRight->Evaluate();
}

int TimesNode::Evaluate() {
    return this->mLeft->Evaluate() * this->mRight->Evaluate();
}

int DivideNode::Evaluate() {
    return this->mLeft->Evaluate() / this->mRight->Evaluate();
}

int LessNode::Evaluate() {
    return (this->mLeft->Evaluate() < this->mRight->Evaluate()) ? 1 : 0;
}

int LessEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() <= this->mRight->Evaluate()) ? 1 : 0;
}

int GreaterNode::Evaluate() {
    return (this->mLeft->Evaluate() > this->mRight->Evaluate()) ? 1 : 0;
}

int GreaterEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() >= this->mRight->Evaluate()) ? 1 : 0;
}

int EqualNode::Evaluate() {
    return (this->mLeft->Evaluate() == this->mRight->Evaluate()) ? 1 : 0;
}

int NotEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() != this->mRight->Evaluate()) ? 1 : 0;
}

