#include "include/Instructions.h"
int main() {
    InstructionsClass code;

    code.PushValue(5);
    code.PopAndWrite();

    code.Finish();
    code.Execute();

    return 1;
}