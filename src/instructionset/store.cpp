//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// SB $R1, $R2
// place byte in $R1 at address in $R2
// BBB
//
void InstructionSet::SB() const
{
    Transform::byteToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

//
// SW $R1, $R2
// place word in $R1 at address in $R2
// BBB
//
void InstructionSet::SW() const
{
    Transform::wordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

//
// SD $R1, $R2
// place dword in $R1 at address in $R2
// BBB
//
void InstructionSet::SD() const
{
    Transform::dwordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

//
// SQ $R1, $R2
// place qword in $R1 at address in $R2
// BBB
//
void InstructionSet::SQ() const
{
    Transform::qwordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

//
// SF1 $F, $R2
// place float in $F at address in $R2
// BBB
//
void InstructionSet::SF1() const
{
    Transform::floatToBytecode
    (
        vm->registers.RF((FloatRegisterCodes)((*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))),
        &(*vm->ram)(vm->registers.R1_24(($IP+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

//
// SD $D, $R2
// place double in $D at address in $R2
// BBB
//
void InstructionSet::SF2() const
{
    Transform::doubleToBytecode
    (
        vm->registers.RD((DoubleRegisterCodes)((*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))),
        &(*vm->ram)(vm->registers.R1_24(($IP+2)))
    );
    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction
}

} //namespace Logi
