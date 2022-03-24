//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

#include <iostream>

namespace Logi
{

//
// JMP $R
// jump to address in $R
// BB
//
void InstructionSet::JMP() const
{
    vm->registers.R($IP) = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1));
}

//
// JE $R1, $R2, $R3
// jump to address in $R3 if $R1 == $R2
// BBBB
//
void InstructionSet::JE() const
{
    if(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) == vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    {
        vm->registers.R($IP) = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));
    }
}

//
// JNE $R1, $R2, $R3
// jump to address in $R3 if $R1 != $R2
// BBBB
//
void InstructionSet::JNE() const
{
    if(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) != vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    {
        vm->registers.R($IP) = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));
    }
}

//
// SLT $R1, $R2, $R3
// set $R1 = 1 if $R2 < $R3, else $R1 = 0
// BBBB
//
void InstructionSet::SLT() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)) < vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3)) ? 1 : 0;

    vm->registers.R($IP) += 4; //set next instruction
}

//
// INT byte
// execute interrupt specified by byte
// BB
//
// the byte operand is known as an interrupt vector.
// interrupt routines are indexed by a vector number.
//
void InstructionSet::INT() const
{
    handleInterrupt((U1)vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 2; //set next instruction
}

//
// DI
// disable interrupt processing
// B
//
void InstructionSet::DI()
{
    interruptOn = false;
    vm->registers.R($IP) += 1; //set next instruction
}

//
// EI
// enable interrrupt processing
// B
//
void InstructionSet::EI()
{
    interruptOn = true;
    vm->registers.R($IP) += 1; //set next instruction
}

//
// HALT
// shutdown the virtual machine
// B
//
void InstructionSet::HALT() const
{
    //no implementation required
}

//
// NOP
// does nothing - no operation
// B
//
void InstructionSet::NOP() const
{
    vm->registers.R($IP) += 1; //set next instruction
}

} //namespace Logi
