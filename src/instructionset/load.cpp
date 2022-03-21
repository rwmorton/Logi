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

void InstructionSet::debug_load_pre() const
{
    cout << setw(20) << setfill('*') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)(vm->registers.R($IP))) << " instr. beg:\n";
    cout << setw(20) << setfill('*') << '\n';

    cout << "EXE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;// << endl;

    //cout << "R[$IP] = " << vm->registers.R($IP) << endl;
    //cout << "RAM[$IP] = " << static_cast<int>(*(vm->ram->at(vm->registers.R($IP)))) << endl;
    //cout << "RAM[opcode index]: RAM[" << vm->registers.R($IP) << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP))) << '\n';
    //cout << "RAM[operand index]: RAM[" << vm->registers.R($IP) + 1 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+1)) << '\n';
    //cout << "RAM[byte index]: RAM[" << vm->registers.R($IP) + 2 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+2)) << '\n';
    //cout << setw(20) << setfill('-') << '\n';
}

void InstructionSet::debug_load_post() const
{
    cout << setw(20) << setfill('-') << '\n';
    //cout << "EXE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;
    //cout << setw(20) << setfill('*') << '\n';
    cout << setw(20) << setfill('-') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)($IP)) << " instr. end.\n";
    //cout << setw(20) << setfill('*') << '\n';
}

void InstructionSet::LBI() const
{
    debug_load_pre();

    //set register at byte 2 to byte 3
    Transform::byteToRegister((*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

void InstructionSet::LWI() const
{
    debug_load_pre();

    //set register at byte 2 to word starting at byte 3
    Transform::wordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 4; //set next instruction

    debug_load_post();
}

void InstructionSet::LDI() const
{
    debug_load_pre();

    //set register at byte 2 to dword starting at byte 3
    Transform::dwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 6; //set next instruction

    debug_load_post();
}

void InstructionSet::LQI() const
{
    debug_load_pre();

    //set register at byte 2 to qword starting at byte 3
    Transform::qwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 10; //set next instruction

    debug_load_post();
}

void InstructionSet::LF1I() const
{
    //
}

void InstructionSet::LF2I() const
{
    //
}

void InstructionSet::LAD() const
{
    //
}

void InstructionSet::LAI() const
{
    //
}

void InstructionSet::LB() const
{
    //
}

void InstructionSet::LW() const
{
    //
}

void InstructionSet::LD() const
{
    //
}

void InstructionSet::LQ() const
{
    //
}

void InstructionSet::LF1() const
{
    //
}

void InstructionSet::LF2() const
{
    //
}

} //namespace Logi
