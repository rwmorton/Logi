//Logi includes
#include "../InstructionSet.h"
#include "../Transform.h"
#include "../VirtualMachine.h"

namespace Logi
{

/*
The push instructions decrement the stack pointer ($SP) and then place
a value on the stack.
*/

//
// PUSHB $R
// push byte in $R onto the stack
// BB
//
void InstructionSet::PUSHB() const
{
    Transform::byteToStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP)--; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// PUSHW $R
// push word in $R onto the stack
// BB
//
void InstructionSet::PUSHW() const
{
    
    Transform::wordToStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );

    vm->registers.R($SP) -= 2; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// PUSHD $R
// push dword in $R onto the stack
// BB
//
void InstructionSet::PUSHD() const
{
    Transform::dwordToStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 4; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// PUSHQ $R
// push qword in $R onto the stack
// BB
//
void InstructionSet::PUSHQ() const
{
    Transform::qwordToStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 8; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// PUSHF1 $R
// push float in $R onto the stack
// BB
//
void InstructionSet::PUSHF1() const
{
    Transform::floatToStack
    (
        vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 4; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// PUSHF2 $R
// push double in $R onto the stack
// BB
//
void InstructionSet::PUSHF2() const
{
    Transform::doubleToStack
    (
        vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 8; //decrement stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPB $R
// pop byte off stack and store in $R
// BB
//
void InstructionSet::POPB() const
{
    Transform::byteFromStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP)++; //increment stack pointer
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPW $R
// pop word off stack and store in $R
// BB
//
void InstructionSet::POPW() const
{
    Transform::wordFromStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) += 2; //increment stack pointer by 2
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPD $R
// pop dword off stack and store in $R
// BB
//
void InstructionSet::POPD() const
{
    Transform::dwordFromStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) += 4; //increment stack pointer by 4
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPQ $R
// pop qword off stack and store in $R
// BB
//
void InstructionSet::POPQ() const
{
    Transform::qwordFromStack
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) += 8; //increment stack pointer by 8
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPF1 $F
// pop float off stack and store in $F
// BB
//
void InstructionSet::POPF1() const
{
    Transform::floatFromStack
    (
        vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) += 4; //increment stack pointer by 4
    vm->registers.R($IP) += 2; //set next instruction
}

//
// POPF2 $D
// pop double off stack and store in $D
// BB
//
void InstructionSet::POPF2() const
{
    Transform::doubleFromStack
    (
        vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) += 8; //increment stack pointer by 8
    vm->registers.R($IP) += 2; //set next instruction
}

} //namespace Logi
