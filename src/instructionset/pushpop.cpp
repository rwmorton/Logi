//Logi includes
#include "../InstructionSet.h"
#include "../Transform.h"

// TEMP INCL
//Logi includes
#include "../Stream.h" //for debugging in instructions
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::setfill;

namespace Logi
{

void InstructionSet::debug_pushpop_pre() const
{
    cout << setw(20) << setfill('*') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)(vm->registers.R($IP))) << " instr. beg:\n";
    cout << setw(20) << setfill('*') << '\n';

    cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;// << endl;

    cout << "R[$IP] = " << vm->registers.R($IP) << endl;
    cout << "RAM[$IP] = " << static_cast<int>(*(vm->ram->at(vm->registers.R($IP)))) << endl;
    cout << "RAM[opcode index]: RAM[" << vm->registers.R($IP) << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP))) << '\n';
    cout << "RAM[operand index]: RAM[" << vm->registers.R($IP) + 1 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+1)) << '\n';
    cout << "RAM[byte index]: RAM[" << vm->registers.R($IP) + 2 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+2)) << '\n';
    cout << setw(20) << setfill('-') << '\n';
}

void InstructionSet::debug_pushpop_post() const
{
    cout << setw(20) << setfill('-') << '\n';
    cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;
    //cout << setw(20) << setfill('*') << '\n';
    cout << setw(20) << setfill('-') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)($IP)) << " instr. end.\n";
    //cout << setw(20) << setfill('*') << '\n';
}

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
    debug_pushpop_pre();

    Transform::byteToStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP)--; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// PUSHW $R
// push word in $R onto the stack
// BB
//
void InstructionSet::PUSHW() const
{
    debug_pushpop_pre();

    Transform::wordToStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 2; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// PUSHD $R
// push dword in $R onto the stack
// BB
//
void InstructionSet::PUSHD() const
{
    debug_pushpop_pre();

    Transform::dwordToStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 4; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// PUSHQ $R
// push qword in $R onto the stack
// BB
//
void InstructionSet::PUSHQ() const
{
    debug_pushpop_pre();

    Transform::qwordToStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 8; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// PUSHF1 $R
// push float in $R onto the stack
// BB
//
void InstructionSet::PUSHF1() const
{
    debug_pushpop_pre();

    Transform::floatToStack
    (
        vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 4; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// PUSHF2 $R
// push double in $R onto the stack
// BB
//
void InstructionSet::PUSHF2() const
{
    debug_pushpop_pre();

    Transform::floatToStack
    (
        vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($SP))
    );
    vm->registers.R($SP) -= 4; //decrement stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// POPB $R
// pop byte off stack and store in $R
// BB
//
void InstructionSet::POPB() const
{
    debug_pushpop_pre();

    Transform::byteFromStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($TOP))
    );

    vm->registers.R($TOP)--; //decrement top-of-stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// POPW $R
// pop word off stack and store in $R
// BB
//
void InstructionSet::POPW() const
{
    debug_pushpop_pre();

    Transform::wordFromStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($TOP))
    );

    vm->registers.R($TOP) -= 2; //decrement top-of-stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// POPD $R
// pop dword off stack and store in $R
// BB
//
void InstructionSet::POPD() const
{
    debug_pushpop_pre();

    Transform::dwordFromStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($TOP))
    );

    vm->registers.R($TOP) -= 4; //decrement top-of-stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// POPQ $R
// pop qword off stack and store in $R
// BB
//
void InstructionSet::POPQ() const
{
    debug_pushpop_pre();

    Transform::qwordFromStack
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R($TOP))
    );

    vm->registers.R($TOP) -= 8; //decrement top-of-stack pointer

    vm->registers.R($IP) = vm->registers.R($IP) + 2; //set next instruction

    debug_pushpop_post();
}

//
// POPF1 $F
// pop float off stack and store in $F
// BB
//
void InstructionSet::POPF1() const
{
    throw std::runtime_error("InstructionSet::POPF1() unimplemented.");
}

//
// POPF2 $D
// pop double off stack and store in $D
// BB
//
void InstructionSet::POPF2() const
{
    throw std::runtime_error("InstructionSet::POPF2() unimplemented.");
}

} //namespace Logi
