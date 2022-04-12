//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// CAST_IF $R, $F
// cast the float in $F to an integer in $R
// BBB
//
void InstructionSet::CAST_IF() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2)));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// CAST_ID $R, $D
// cast the double in $D to an integer in $R
// BBB
//
void InstructionSet::CAST_ID() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) =
        (S8)(vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2)));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// CAST_FI $F, $R
// cast the integer in $R to a float in $F
// BBB
//
void InstructionSet::CAST_FI() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = (F4)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// CAST_FD $F, $D
// cast the double in $D to a float in $F
// BBB
//
void InstructionSet::CAST_FD() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = (F4)vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+2));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// CAST_DI $D, $R
// cast the integer in $R to a double in $D
// BBB
//
void InstructionSet::CAST_DI() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = (F8)((S8)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// CAST_DF $D, $F
// cast the float in $F to a double in $D
// BBB
//
void InstructionSet::CAST_DF() const
{
    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))
        = (F8)vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2));

    vm->registers.R($IP) += 3; //set next instruction
}

//
// FADD $F1, $F2, $F3
// $F1 = $F2 + $F3
// BBBB
//
void InstructionSet::FADD() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2))
        + vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// FSUB $F1, $F2, $F3
// $F1 = $F2 - $F3
// BBBB
//
void InstructionSet::FSUB() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2))
        - vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// FMULT $F1, $F2, $F3
// $F1 = $F2 * $F3
// BBBB
//
void InstructionSet::FMULT() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2))
        * vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// FDIV $F1, $F2, $F3
// $F1 = $F2 / $F3
// BBBB
//
void InstructionSet::FDIV() const
{
    if(InstructionSet::isZero(vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3)),0.0f))
    {
        throw std::runtime_error("INSTRUCTION_SET: division by zero.");
    }

    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))
        = vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2))
        / vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3));
    
    vm->registers.R($IP) += 4; //set next instruction
}

//
// FSLT $F1, $F2, $F3
// $F1 = 1 if $F2 < $F3, else $F1 = 0
// BBBB
//
void InstructionSet::FSLT() const
{
    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1)) =
        vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+2))
        < vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+3))
        ? 1 : 0;
    
    vm->registers.R($IP) += 4; //set next instruction
}

} //namespace Logi
