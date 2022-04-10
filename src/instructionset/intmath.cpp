//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// ADD $R1, $R2, $R3
// $R1 = $R2 + $R3
// BBBB
//
void InstructionSet::ADD() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        (vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2))) +
        (vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+3)));

    vm->registers.R($IP) += 4; //set next instruction
}

//
// SUB $R1, $R2, $R3
// $R1 = $R2 - $R3
// BBBB
//
void InstructionSet::SUB() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2))) -
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3)));

    vm->registers.R($IP) += 4; //set next instruction
}

//
// MULT $R1, $R2, $R3
// $R1 = $R2 * $R3
// BBBB
//
void InstructionSet::MULT() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2))) *
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3)));

    vm->registers.R($IP) += 4; //set next instruction
}

//
// DIV $R1, $R2, $R3
// $R1 = $R2 / $R3
// BBBB
//
void InstructionSet::DIV() const
{
    if(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3)) == 0) throw std::runtime_error("INSTRUCTION_SET: division by zero.");

    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2))) /
        (S8)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3)));

    vm->registers.R($IP) += 4; //set next instruction
}

} //namespace Logi
