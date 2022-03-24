//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// DADD $D1, $D2, $D3
// $D1 = $D2 + $D3
// BBBB
//
void InstructionSet::DADD() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2))
        + vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// DSUB $D1, $D2, $D3
// $D1 = $D2 - $D3
// BBBB
//
void InstructionSet::DSUB() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2))
        - vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// DMULT $D1, $D2, $D3
// $D1 = $D2 * $D3
// BBBB
//
void InstructionSet::DMULT() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2))
        * vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// DDIV $D1, $D2, $D3
// $D1 = $D2 / $D3
// BBBB
//
void InstructionSet::DDIV() const
{
    if(InstructionSet::isZero(vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3)),0.0))
    {
        throw std::runtime_error("INSTRUCTION_SET: division by zero.");
    }

    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2))
        / vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// DSLT $D1, $D2, $D3
// $D1 = 1 if $D2 < $D3, else $D1 = 0
// BBBB
//
void InstructionSet::DSLT() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1)) =
        vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2))
        < vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+3))
        ? 1 : 0;
    
    vm->registers.R($IP) += 4; //set next instruction
}

} //namespace Logi
