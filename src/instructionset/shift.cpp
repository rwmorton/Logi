//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// SRA $R1, $R2, $R3
// $R1 = $R2 shifted $R3 bits right, sign bit enters left
// BBBB
//
// SRA (shift right arithmetic) takes the second register operand
// and shifts its contents to the right. The number of bits shifted
// is determined by the third register operand. the shifting is
// arithmetic, such that the sign bit of the value being shifted
// enters in on the left as bits are shifted right.
//
// 1000011110000 => SRA: shift right (3 bits) arithmetic => 1111000011110
//
void InstructionSet::SRA() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2))) >>
        (S8)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+3)));

    vm->registers.R($IP) += 4; //set next instruction
}

//
// SRL $R1, $R2, $R3
// $R1 = $R2 shifted $R3 bits right, zero enters left
// BBBB
//
// SRL (shift right logical) takes the second register operand
// and shifts its contents to the right. the number of bits shifted
// is determined by the third register operand. the shifting is
// logical, so the 0 bit enters in on the left as the bits are
// shifted right.
//
// 1000011110000 => SRL: shift right (3 bits) logical => 0001000011110
//
void InstructionSet::SRL() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) >>
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+3));

    vm->registers.R($IP) += 4; //set next instruction
}

//
// SL $R1, $R2, $R3
// $R1 = $R2 shifted $R3 bits left, zero enters right
// BBBB
//
// SL (shift left) takes the second register operand
// and shifts its contents to the left. the number of
// bits shifted is determined by the third register
// operand.
//
// 1000011110000 => SL: shift left (3 bits) => 0011110000000
//
void InstructionSet::SL() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) <<
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+3));

    vm->registers.R($IP) += 4; //set next instruction
}

} //namespace Logi
