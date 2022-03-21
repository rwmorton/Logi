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

void InstructionSet::LBI() const
{
    const Stream* stream = Stream::getInstance();
    cout << setw(20) << setfill('*') << '\n';
    stream->string("LBI instruction:\n");
    cout << setw(20) << setfill('*') << '\n';

    RAM& ram = *vm->ram;
    Registers& reg = vm->registers;

    cout << "RAM: " << ram << endl;
    cout << "REG: " << reg << endl;

    stream->string("$IP = ").U1($IP).endl();
    stream->string("$IP+1 = ").U1($IP+1).endl();
    stream->string("$IP+2 = ").U1($IP+2).endl();
    cout << setw(20) << setfill('-') << '\n';
    cout << "modifying registers..." << endl;
    cout << setw(20) << setfill('-') << '\n';

    cout << reg << endl;

    cout << "R[$IP+1]: = R[" << $IP+1 << "] = " << reg.R($IP+1) << endl;
    cout << "R[$IP]: = R[" << $IP << "] = " << reg.R($IP) << endl;
    cout << "R[$IP] + 3: = R[" << $IP << "] + 3 = " << reg.R($IP) + 3 << endl;
    cout << setw(20) << setfill('-') << '\n';

    cout << "RAM[opcode] = " << reg.R($IP) << endl;
    cout << "RAM[operand] = " << static_cast<int>(ram(reg.R($IP)+1)) << endl;
    cout << "RAM[byte constant] = " << static_cast<int>(ram(reg.R($IP)+2)) << endl;
    cout << setw(20) << setfill('-') << '\n';

    cout << "RAM[R[$IP+1]]: RAM[" << static_cast<int>(ram(reg.R($IP)+1)) << "] = " << static_cast<int>(ram(reg.R($IP)+2)) << endl;
    ram(reg.R($IP)+1) = ram(reg.R($IP)+2); //put 3rd byte into 2nd byte

    cout << setw(20) << setfill('-') << '\n';

    reg.R($IP) = reg.R($IP) + 3;
    cout << reg << endl;

    cout << "RAM: " << ram << endl;
    cout << setw(20) << setfill('*') << '\n';
    stream->string("LBI instr. end.\n");
    cout << setw(20) << setfill('*') << '\n';
}

void InstructionSet::LWI() const
{
    //
}

void InstructionSet::LDI() const
{
    //
}

void InstructionSet::LQI() const
{
    //
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
