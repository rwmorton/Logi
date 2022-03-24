//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// AND $R1, $R2, $R3
// set $R1 to the bitwise AND of $R2 and $R3
// BBBB
//
void InstructionSet::AND() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)) & vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));
    vm->registers.R($IP) += 4; //set next instruction
}

//
// OR $R1, $R2, $R3
// set $R1 to the bitwise OR of $R2 and $R3
// BBBB
//
void InstructionSet::OR() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)) | vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));
    vm->registers.R($IP) += 4; //set next instruction
}

//
// XOR $R1, $R2, $R3
// set $R1 to the bitwise XOR of $R2 and $R3
// BBBB
//
void InstructionSet::XOR() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) =
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)) ^ vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));
    vm->registers.R($IP) += 4; //set next instruction
}

//
// NOT $R1, $R2
// set $R1 to the bitwise NOT of $R2
// BBB
//
void InstructionSet::NOT() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) = ~vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// BT $R1, $R2, $R3
// set $R1 to 1 if the $R3 bit in
// $R2 is on otherwise set $R1 to 0.
// BBBB
//
void InstructionSet::BT() const
{
    U8 bit = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+3));

    if(bit > 63) throw std::runtime_error("INSTRUCTION_SET: bit index is out of range.");
    
    U8 mask = (U8)0x1;
    for(int index = 0; index<bit; index++)
    {
        mask = mask*2;
    }
    mask = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)) & mask;

    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) = mask > 0 ? 0x1 : 0x0;
    vm->registers.R($IP) += 4; //set next instruction
}

//
// BS $R1, $R2
// set the $R2'nd bit in $R1
// BBB
//
void InstructionSet::BS() const
{
    U8 bit = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2));

    if(bit > 63) throw std::runtime_error("INSTRUCTION_SET: bit index is out of range.");
    
    U8 mask = (U8)0x1;
    for(int index = 0; index<bit; index++)
    {
        mask = mask*2;
    }

    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) | mask;
    vm->registers.R($IP) += 3; //set next instruction
}

} //namespace Logi
