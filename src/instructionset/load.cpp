//Logi includes
#include "../InstructionSet.h"
#include "../Transform.h"
#include "../VirtualMachine.h"

namespace Logi
{

//
// LBI $R, BYTE
// store BYTE constant into $R
// BBB
//
void InstructionSet::LBI() const
{
    //set register at byte 2 to byte 3
    Transform::byteToRegister((*vm->ram)(vm->registers.R($IP)+2),vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// LWI $R, WORD
// store WORD constant into $R
// BBW
//
void InstructionSet::LWI() const
{
    //set register at byte 2 to word starting at byte 3
    Transform::wordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 4; //set next instruction
}

//
// LDI $R, DWORD
// store DWORD constant into $R
// BBD
//
void InstructionSet::LDI() const
{
    //set register at byte 2 to dword starting at byte 3
    Transform::dwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 6; //set next instruction
}

//
// LQI $R, QWORD
// store QWORD constant into $R
// BBQ
//
void InstructionSet::LQI() const
{
    //set register at byte 2 to qword starting at byte 3
    Transform::qwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 10; //set next instruction
}

//
// LF1I $F, float (DWORD)
// store float constant into $F
// BBD
//
void InstructionSet::LF1I() const
{
    //set register at byte 2 to float starting at byte 3
    Transform::floatToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 6; //set next instruction
}

//
// LF2I $D, double (QWORD)
// store double constant into $D
// BBQ
//
void InstructionSet::LF2I() const
{
    //set register at byte 2 to double starting at byte 3
    Transform::doubleToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 10; //set next instruction
}

//
// LAD $R, address (QWORD)
// store address constant into $R
// BBQ
//
void InstructionSet::LAD() const
{
    //set register at byte 2 to address starting at byte 3
    Transform::addressToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 10; //set next instruction
}

//
// LAI $R1, $R2, QWORD
// store sum of QWORD and $R2 in $R1
// BBBQ
//
void InstructionSet::LAI() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (S8)
    (
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) +
        (S8)Transform::bytecodeToQWord(&(*vm->ram)(vm->registers.R($IP)+3))
    );
    vm->registers.R($IP) += 11; //set next instruction
}

//
// LB $R1, $R2
// take byte at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LB() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (S1)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// LW $R1, $R2
// take word at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LW() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (S2)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// DW $R1, $R2
// take dword at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LD() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (S4)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// QW $R1, $R2
// take qword at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LQ() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (S8)vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// LF1 $R1, $R2
// take float at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LF1() const
{
    Stream::getInstance()->string("WARNING: INSTRUCTION_SET: LF1 verified yet.\n");

    vm->registers.RF((FloatRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (F4)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// LF2 $R1, $R2
// take double at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LF2() const
{
    Stream::getInstance()->string("WARNING: INSTRUCTION_SET: LF2 not verified.\n");

    vm->registers.RD((DoubleRegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)) = (F8)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)));
    vm->registers.R($IP) += 3; //set next instruction
}

} //namespace Logi
