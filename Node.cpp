#include "include/Node.h"

int gCount = 0;

Node::~Node() {
    // MSG("NODE DELETE");
}


StartNode::~StartNode() {
    // MSG("START DELETE");
    delete this->mProgramNode; 
}
void StartNode::Interpret() {
    this->mProgramNode->Interpret();
}
void StartNode::Code(InstructionsClass &code) {
    this->mProgramNode->Code(code);
}


ProgramNode::~ProgramNode() {
    // MSG("PROGRAM DELETE");
    delete this->mBlockNode;
}
void ProgramNode::Interpret() {
    this->mBlockNode->Interpret();
}
void ProgramNode::Code(InstructionsClass &code) {
    this->mBlockNode->Code(code);
}


BlockNode::~BlockNode() {
    // MSG("BLOCK DELETE");
    delete this->mStatementGroupNode;
}
void BlockNode::Interpret() {
    this->mStatementGroupNode->Interpret();
}
void BlockNode::Code(InstructionsClass &code) {
    this->mStatementGroupNode->Code(code);
}


void StatementGroupNode::AddStatement( StatementNode * StatementNode ) {
    this->mStatementGroupNodes.push_back( StatementNode );
}
StatementGroupNode::~StatementGroupNode() {
    // MSG("STATEMENTGROUPNODE DELETE");
    for (int i = 0; i < mStatementGroupNodes.size(); i++) {
        // MSG("STATEMENTNODE " << i << " DELETE");
        delete mStatementGroupNodes[i];
    }
}
void StatementGroupNode::Interpret() {
    for (int i = 0; i < mStatementGroupNodes.size(); i++) {
        this->mStatementGroupNodes[i]->Interpret();
    }
}
void StatementGroupNode::Code(InstructionsClass &code) {
    for (size_t i = 0; i < mStatementGroupNodes.size(); i++) {
        this->mStatementGroupNodes[i]->Code(code);
    }
}

DeclarationStatementNode::~DeclarationStatementNode() {
    // MSG("DECLARATIONSTATEMENT DELETE");
    delete this->mIdentifierNode;
}
void DeclarationStatementNode::Interpret() {
    this->mIdentifierNode->DeclareVariable();
}
void DeclarationStatementNode::Code(InstructionsClass &code) {
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
void AssignmentStatementNode::Code(InstructionsClass &code) {

}


CoutStatementNode::~CoutStatementNode() {
    // MSG("COUTSTATEMENTNODE DELETE");
    delete this->mExpressionNode;
}
void CoutStatementNode::Interpret() {
    cout << this->mExpressionNode->Evaluate() << endl;
}
void CoutStatementNode::Code(InstructionsClass &code) {

}


IfStatementNode::~IfStatementNode() {
    delete this->mExpression;
    delete this->mStatement1;
    delete this->mStatement2;
    // MSG("IFSTATEMENTNODE DELETE");
}

void IfStatementNode::Interpret() {
    if ( this->mExpression->Evaluate() ) {
        this->mStatement1->Interpret();
    } else if ( this->mStatement2 ) {
        this->mStatement2->Interpret();
    }
}


WhileStatementNode::~WhileStatementNode() {
    delete this->mExpression;
    delete this->mStatement;
    // MSG("WHILESTATEMENTNODE DELETE")
}
void WhileStatementNode::Interpret() {
    // while the expression is true. interpret the statement
    while ( mExpression->Evaluate() ) {
        mStatement->Interpret();
    }
}


RepeatNode::~RepeatNode() {
    delete this->mExpression;
    delete this->mStatement;
}
void RepeatNode::Interpret() {
    gCount = mExpression->Evaluate();
    for ( int i = 0; i < gCount; i++ ) {
        mStatement->Interpret();
        
    }
}


ExpressionNode::~ExpressionNode() {
    // MSG("")
}


IntegerNode::~IntegerNode() {
    // MSG("INTEGERNODE DELETE");
}
int IntegerNode::Evaluate() {
    return this->mValue;
}


IdentifierNode::~IdentifierNode() {
    // MSG("IDENTIFIERNODE DELETE");
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
    // MSG("BINARYOPERATORNODE DELETE");
    delete this->mLeft; delete this->mRight;
}

int PlusNode::Evaluate() {
    return this->mLeft->Evaluate() + this->mRight->Evaluate();
}

void PlusEqualNode::Interpret() {
    int new_value = this->getIdentifier()->Evaluate() + this->getExpression()->Evaluate();
    this->getIdentifier()->SetValue(new_value);
}

int MinusNode::Evaluate() {
    return this->mLeft->Evaluate() - this->mRight->Evaluate();
}

int TimesNode::Evaluate() {
    return this->mLeft->Evaluate() * this->mRight->Evaluate();
}

int ExponentNode::Evaluate() {
    return pow(this->mLeft->Evaluate(), this->mRight->Evaluate());
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

int LogicalANDnode::Evaluate() {
    return ( this->mLeft->Evaluate() && this->mRight->Evaluate() ) ? 1 : 0;
}

int LogicalORnode::Evaluate() {
    return ( this->mLeft->Evaluate() || this->mRight->Evaluate() ) ? 1 : 0;
}
