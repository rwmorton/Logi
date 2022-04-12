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
    cout << "R($IP) = " << vm->registers.R($IP) << endl;
    U8 R1 = vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1));
    U8 R2 = vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2));

    cout << "R1 = " << R1 << endl;
    cout << "R2 = " << R2 << endl;

    (*vm->ram)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2))) = (S1)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// SW $R1, $R2
// place word in $R1 at address in $R2
// BBB
//
void InstructionSet::SW() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) = (S2)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// SD $R1, $R2
// place dword in $R1 at address in $R2
// BBB
//
void InstructionSet::SD() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) = (S4)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// SQ $R1, $R2
// place qword in $R1 at address in $R2
// BBB
//
void InstructionSet::SQ() const
{
    vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2)) = (S8)(vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+1)));
    vm->registers.R($IP) += 3; //set next instruction
}

//
// SF1 $F, $R2
// place float in $F at address in $R2
// BBB
//
void InstructionSet::SF1() const
{
    Stream::getInstance()->string("WARNING: INSTRUCTION_SET: SF1 not verified yet.\n");

    Transform::floatToRegister
    (
        &(*vm->ram)(vm->registers.R($IP)+1),
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2))
    );
    vm->registers.R($IP) += 3; //set next instruction
}

//
// SD $D, $R2
// place double in $D at address in $R2
// BBB
//
void InstructionSet::SF2() const
{
    Stream::getInstance()->string("WARNING: INSTRUCTION_SET: SF2 not verified yet.\n");

    Transform::doubleToRegister
    (
        &((*vm->ram)(vm->registers.R($IP)+1)),
        vm->registers.R((RegisterCodes)(*vm->ram)(vm->registers.R($IP)+2))
    );
    vm->registers.R($IP) += 3; //set next instruction
}

} //namespace Logi
