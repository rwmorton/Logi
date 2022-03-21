//Logi includes
#include "../InstructionSet.h"

// TEMP INCL
//Logi includes
#include "../Stream.h" //for debugging in instructions
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::setfill;

namespace Logi
{

void InstructionSet::debug_store_pre() const
{
    cout << setw(20) << setfill('*') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)(vm->registers.R($IP))) << " instr. beg:\n";
    cout << setw(20) << setfill('*') << '\n';

    cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;// << endl;

    cout << "R[$IP] = " << vm->registers.R($IP) << endl;
    cout << "RAM[$IP] = " << static_cast<int>(*(vm->ram->at(vm->registers.R($IP)))) << endl;
    cout << "RAM[opcode index]: RAM[" << vm->registers.R($IP) << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP))) << '\n';
    cout << "RAM[operand index]: RAM[" << vm->registers.R($IP) + 1 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+1)) << '\n';
    cout << "RAM[byte index]: RAM[" << vm->registers.R($IP) + 2 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+2)) << '\n';
    cout << setw(20) << setfill('-') << '\n';
}

void InstructionSet::debug_store_post() const
{
    cout << setw(20) << setfill('-') << '\n';
    cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;
    //cout << setw(20) << setfill('*') << '\n';
    cout << setw(20) << setfill('-') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)($IP)) << " instr. end.\n";
    //cout << setw(20) << setfill('*') << '\n';
}

//
// SB $R1, $R2
// place byte in $R1 at address in $R2
// BBB
//
void InstructionSet::SB() const
{
    debug_store_pre();

    cout << endl;
    U8 byteAtR1 = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1));
    cout << "byte at $R1 = " << byteAtR1 << endl;
    U8 addrAtR2 = vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2));
    cout << "addr at $R2 = " << addrAtR2 << endl;
    cout << endl;

    (*vm->ram)(addrAtR2) = byteAtR1;

    //set register at byte 2 to byte 3
    //Transform::byteToRegister((*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

//
// SW $R1, $R2
// place word in $R1 at address in $R2
// BBB
//
void InstructionSet::SW() const
{
    //
}

//
// SD $R1, $R2
// place dword in $R1 at address in $R2
// BBB
//
void InstructionSet::SD() const
{
    //
}

//
// SQ $R1, $R2
// place qword in $R1 at address in $R2
// BBB
//
void InstructionSet::SQ() const
{
    //
}

//
// SF1 $F, $R2
// place float in $F at address in $R2
// BBB
//
void InstructionSet::SF1() const
{
    //
}

//
// SD $D, $R2
// place double in $D at address in $R2
// BBB
//
void InstructionSet::SF2() const
{
    //
}

} //namespace Logi
