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
    this->mExpressionNode->CodeEvaluate(code);
    int index = this->mIdentifierNode->GetIndex();
    code.PopAndStore(index);
}


CoutStatementNode::~CoutStatementNode() {
    // MSG("COUTSTATEMENTNODE DELETE");
    for (int i = 0; i < mExpressionNode.size(); i++) {
        delete mExpressionNode[i];
    }
}
void CoutStatementNode::AddExpression(ExpressionNode *expression) {
    this->mExpressionNode.push_back( expression );
}
void CoutStatementNode::Interpret() {
    for (int i = 0; i < mExpressionNode.size(); i++) {
        cout << mExpressionNode[i]->Evaluate() << endl;
    }
}
void CoutStatementNode::Code(InstructionsClass &code) {

    for (int i = 0; i < mExpressionNode.size(); i++) {
        mExpressionNode[i]->CodeEvaluate(code);
        code.PopAndWrite();
    }
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
void IfStatementNode::Code(InstructionsClass &code) {
    this->mExpression->CodeEvaluate(code); // code expression
    unsigned char * jumpAddress = code.SkipIfZeroStack(); // note where we are to fill in later // jumps over that statement
	unsigned char * address1 = code.GetAddress(); // note the beggining of the jump
    this->mStatement1->Code(code); // code statement 1
    unsigned char * jumpAddress2 = code.Jump(); // note where we are to fill in later
    unsigned char * address2 = code.GetAddress(); // end of one jump | beggining of second
    code.SetOffset(jumpAddress, (int)(address2 - address1)); // fills in the address later from zerostack

    if (this->mStatement2 != NULL) {
        this->mStatement2->Code(code);
        unsigned char * address3 = code.GetAddress(); // note where we are
        code.SetOffset(jumpAddress2, (int)(address3 - address2)); // fills in address later from code.Jump()
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
void WhileStatementNode::Code(InstructionsClass &code) {
    unsigned char * address0 = code.GetAddress();
	this->mExpression->CodeEvaluate(code);
	unsigned char * afterWhile = code.SkipIfZeroStack();
	unsigned char * address1 = code.GetAddress();
	this->mStatement->Code(code);
	unsigned char * start = code.Jump();
	unsigned char * address2 = code.GetAddress();
	code.SetOffset(afterWhile, (int)(address2 - address1));
	code.SetOffset(start, (int)(address0 - address2));
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
void RepeatNode::Code(InstructionsClass &code) {

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
void IntegerNode::CodeEvaluate(InstructionsClass &code) {
    code.PushValue(this->mValue);
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
void IdentifierNode::CodeEvaluate(InstructionsClass &code) {
    code.PushVariable(GetIndex());
}


BinaryOperatorNode::~BinaryOperatorNode() {
    // MSG("BINARYOPERATORNODE DELETE");
    delete this->mLeft; delete this->mRight;
}

int PlusNode::Evaluate() {
    return this->mLeft->Evaluate() + this->mRight->Evaluate();
}
void PlusNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopAddPush();
}

void PlusEqualNode::Interpret() {
    int new_value = this->getIdentifier()->Evaluate() + this->getExpression()->Evaluate();
    this->getIdentifier()->SetValue(new_value);
}
void PlusEqualNode::Code(InstructionsClass &code) {
    this->getIdentifier()->CodeEvaluate(code);
    this->getExpression()->CodeEvaluate(code);
    code.PopPopAddPush();
    code.PopAndStore(this->getIdentifier()->GetIndex());
}

void MinusEqualNode::Interpret() {
    int new_value = this->getIdentifier()->Evaluate() - this->getExpression()->Evaluate();
    this->getIdentifier()->SetValue(new_value);
}
void MinusEqualNode::Code(InstructionsClass &code) {
    this->getIdentifier()->CodeEvaluate(code);
    this->getExpression()->CodeEvaluate(code);
    code.PopPopSubPush();
    code.PopAndStore(this->getIdentifier()->GetIndex());
}

int MinusNode::Evaluate() {
    return this->mLeft->Evaluate() - this->mRight->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopSubPush();
}

int TimesNode::Evaluate() {
    return this->mLeft->Evaluate() * this->mRight->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopMulPush();
}

int ExponentNode::Evaluate() {
    return pow(this->mLeft->Evaluate(), this->mRight->Evaluate());
}
void ExponentNode::CodeEvaluate(InstructionsClass &code) {

}

int ModNode::Evaluate() {
    return this->mLeft->Evaluate() % this->mRight->Evaluate();
}
void ModNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopModPush();
}

int DivideNode::Evaluate() {
    return this->mLeft->Evaluate() / this->mRight->Evaluate();
}
void DivideNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopDivPush();
}
/////////
int LessNode::Evaluate() {
    return (this->mLeft->Evaluate() < this->mRight->Evaluate()) ? 1 : 0;
}
void LessNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopLessPush();
}

int LessEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() <= this->mRight->Evaluate()) ? 1 : 0;
}
void LessEqualNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopLessEqualPush();
}

int GreaterNode::Evaluate() {
    return (this->mLeft->Evaluate() > this->mRight->Evaluate()) ? 1 : 0;
}
void GreaterNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopGreaterPush();
}

int GreaterEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() >= this->mRight->Evaluate()) ? 1 : 0;
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopGreaterEqualPush();
}

int EqualNode::Evaluate() {
    return (this->mLeft->Evaluate() == this->mRight->Evaluate()) ? 1 : 0;
}
void EqualNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopEqualPush();
}

int NotEqualNode::Evaluate() {
    return (this->mLeft->Evaluate() != this->mRight->Evaluate()) ? 1 : 0;
}
void NotEqualNode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopNotEqualPush();
}

int LogicalANDnode::Evaluate() {
    return ( this->mLeft->Evaluate() && this->mRight->Evaluate() ) ? 1 : 0;
}
void LogicalANDnode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopAndPush();
}

int LogicalORnode::Evaluate() {
    return ( this->mLeft->Evaluate() || this->mRight->Evaluate() ) ? 1 : 0;
}
void LogicalORnode::CodeEvaluate(InstructionsClass &code) {
    this->mLeft->CodeEvaluate(code);
    this->mRight->CodeEvaluate(code);
    code.PopPopOrPush();
}
