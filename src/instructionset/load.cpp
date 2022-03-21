//Logi includes
#include "../InstructionSet.h"
#include "../Transform.h"

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

    cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;// << endl;

    cout << "R[$IP] = " << vm->registers.R($IP) << endl;
    cout << "RAM[$IP] = " << static_cast<int>(*(vm->ram->at(vm->registers.R($IP)))) << endl;
    cout << "RAM[opcode index]: RAM[" << vm->registers.R($IP) << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP))) << '\n';
    cout << "RAM[operand index]: RAM[" << vm->registers.R($IP) + 1 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+1)) << '\n';
    cout << "RAM[byte index]: RAM[" << vm->registers.R($IP) + 2 << "] = " << static_cast<int>((*vm->ram)(vm->registers.R($IP)+2)) << '\n';
    cout << setw(20) << setfill('-') << '\n';
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

//
// LBI $R, BYTE
// store BYTE constant into $R
// BBB
//
void InstructionSet::LBI() const
{
    debug_load_pre();

    //set register at byte 2 to byte 3
    Transform::byteToRegister((*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// LQI $R, WORD
// store WORD constant into $R
// BBW
//
void InstructionSet::LWI() const
{
    debug_load_pre();

    //set register at byte 2 to word starting at byte 3
    Transform::wordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 4; //set next instruction

    debug_load_post();
}

//
// LDI $R, DWORD
// store DWORD constant into $R
// BBD
//
void InstructionSet::LDI() const
{
    debug_load_pre();

    //set register at byte 2 to dword starting at byte 3
    Transform::dwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 6; //set next instruction

    debug_load_post();
}

//
// LQI $R, QWORD
// store QWORD constant into $R
// BBQ
//
void InstructionSet::LQI() const
{
    debug_load_pre();

    //set register at byte 2 to qword starting at byte 3
    Transform::qwordToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 10; //set next instruction

    debug_load_post();
}

//
// LF1I $F, float (DWORD)
// store float constant into $F
// BBD
//
void InstructionSet::LF1I() const
{
    debug_load_pre();

    //set register at byte 2 to float starting at byte 3
    Transform::floatToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 6; //set next instruction

    debug_load_post();
}

//
// LF2I $D, double (QWORD)
// store double constant into $D
// BBQ
//
void InstructionSet::LF2I() const
{
    debug_load_pre();

    //set register at byte 2 to double starting at byte 3
    Transform::doubleToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 10; //set next instruction

    debug_load_post();
}

//
// LAD $R, address (QWORD)
// store address constant into $R
// BBQ
//
void InstructionSet::LAD() const
{
    debug_load_pre();

    //set register at byte 2 to address starting at byte 3
    Transform::addressToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));

    vm->registers.R($IP) = vm->registers.R($IP) + 10; //set next instruction

    debug_load_post();
}

//
// LAI $R1, $R2, QWORD
// store sum of QWORD and $R2 in $R1
// BBBQ
//
void InstructionSet::LAI() const
{
    debug_load_pre();

    //set register at byte 2 to address starting at byte given by the value of $R2
    //Transform::addressToRegister(&(*vm->ram)(vm->registers.R($IP)+2),vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1)));
    
    cout << endl << "R" << static_cast<int>((*vm->ram)(vm->registers.R($IP)+2)) << endl << endl;

    U8 whichRegister = ((*vm->ram)(vm->registers.R($IP)+2));
    cout << "the register of interest is R" << whichRegister << endl;

    U8 registerValue = vm->registers.R1_24(whichRegister);
    cout << "the value at register R" << whichRegister << " is " << registerValue << endl;

    //static void addressToRegister(U1 bytes[],U8& reg);

    Transform::addressToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        //&(*vm->ram)(registerValue),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// LB $R1, $R2
// take byte at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LB() const
{
    debug_load_pre();

    Transform::byteToRegister
    (
        (*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// LW $R1, $R2
// take word at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LW() const
{
    debug_load_pre();

    Transform::wordToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// DW $R1, $R2
// take dword at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LD() const
{
    debug_load_pre();

    Transform::dwordToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// QW $R1, $R2
// take qword at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LQ() const
{
    debug_load_pre();

    Transform::qwordToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// LF1 $R1, $R2
// take float at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LF1() const
{
    debug_load_pre();

    Transform::floatToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

//
// LF2 $R1, $R2
// take double at address in $R2 and store in $R1
// BBB
//
void InstructionSet::LF2() const
{
    debug_load_pre();

    Transform::doubleToRegister
    (
        &(*vm->ram)(vm->registers.R1_24(((*vm->ram)(vm->registers.R($IP)+2)))),
        vm->registers.R1_24((*vm->ram)(vm->registers.R($IP)+1))
    );

    vm->registers.R($IP) = vm->registers.R($IP) + 3; //set next instruction

    debug_load_post();
}

} //namespace Logi
