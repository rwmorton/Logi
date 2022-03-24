//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// MOV $R1, $R2
// copy contents of $R2 into $R1
// BBB
//
void InstructionSet::MOV() const
{
    vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)) = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// MOVF $F1, $F2
// copy contents of $F2 into $F1
// BBB
//
void InstructionSet::MOVF() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// MOVD $D1, $D2
// copy contents of $D2 into $D1
// BBB
//
void InstructionSet::MOVD() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

} //namespace Logi
