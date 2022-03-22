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

    Transform::byteToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );

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
    debug_store_pre();

    Transform::wordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

//
// SD $R1, $R2
// place dword in $R1 at address in $R2
// BBB
//
void InstructionSet::SD() const
{
    debug_store_pre();

    Transform::dwordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

//
// SQ $R1, $R2
// place qword in $R1 at address in $R2
// BBB
//
void InstructionSet::SQ() const
{
    debug_store_pre();

    Transform::qwordToBytecode
    (
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)),
        &(*vm->ram)(vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+2)))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

//
// SF1 $F, $R2
// place float in $F at address in $R2
// BBB
//
void InstructionSet::SF1() const
{
    debug_store_pre();

    Transform::floatToBytecode
    (
        vm->registers.RF((FloatRegisterCodes)((*vm->ram)(vm->registers.RF((FloatRegisterCodes)$IP)+1))),
        &(*vm->ram)(vm->registers.R1_24(($IP+2)))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

//
// SD $D, $R2
// place double in $D at address in $R2
// BBB
//
void InstructionSet::SF2() const
{
    debug_store_pre();

    Transform::doubleToBytecode
    (
        vm->registers.RD((DoubleRegisterCodes)((*vm->ram)(vm->registers.RD((DoubleRegisterCodes)$IP)+1))),
        &(*vm->ram)(vm->registers.R1_24(($IP+2)))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_store_post();
}

} //namespace Logi
