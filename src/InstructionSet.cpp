//Logi includes
#include "InstructionSet.h"
#include "VirtualMachine.h"

//std includes
#include <cmath>
#include <float.h>

// TEMP INCL
//Logi includes
//#include "../Stream.h" //for debugging in instructions
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::setfill;

namespace Logi
{

const F4 InstructionSet::F4_EPSILON {FLT_EPSILON};
const F8 InstructionSet::F8_EPSILON {DBL_EPSILON};

const OpCode InstructionSet::FIRST_OPCODE {OpCode::LBI};

InstructionSet::InstructionSet(VirtualMachine* vm) : vm{vm} {}

void InstructionSet::setVM(VirtualMachine* vm)
{
    this->vm = vm;
}

const std::string& InstructionSet::operator()(OpCode code) const
{
    if(code >= NUM_INSTRUCTIONS) throw std::out_of_range("INSTRUCTION_SET: out of range");
    return _InstructionSetStrings.at(code);
}

//
// Get string version of opcode
//
const OpCode InstructionSet::operator()(const std::string& str) const
{
    return InstructionSet::OpCode_fromStr(str);
}

//
// static version of above
//
const OpCode InstructionSet::OpCode_fromStr(const std::string& str)
{
    std::vector<std::string>::const_iterator i = _InstructionSetStrings.begin();
    int index = FIRST_OPCODE;
    while(i != _InstructionSetStrings.end())
    {
        if(*i == str) return (OpCode)index;
        ++i;
        index++;
    }

    return OpCode::BAD;
}

const bool InstructionSet::isZero(const F4 A,const F4 B)
{
    return fabsf(A-B) < F4_EPSILON;
}

const bool InstructionSet::isZero(const F8 A,const F8 B)
{
    return fabs(A-B) < F8_EPSILON;
}

void InstructionSet::debug_pre() const
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

void InstructionSet::debug_post() const
{
    cout << setw(20) << setfill('-') << '\n';
    //cout << "BYTECODE: " << (*vm->ram) << endl;
    cout << "REGISTERS:\n" << vm->registers;
    //cout << setw(20) << setfill('*') << '\n';
    cout << setw(20) << setfill('-') << '\n';
    cout << _InstructionSetStrings.at((*vm->ram)($IP)) << " instr. end.\n";
    //cout << setw(20) << setfill('*') << '\n';
}

const std::vector<std::string> InstructionSet::_InstructionSetStrings
{
    //data transfer
    "LBI","LWI","LDI","LQI","LF1I","LF2I",
    "LAD","LAI",
    "LB","LW","LD","LQ","LF1","LF2",
    "SB","SW","SD","SQ","SF1","SF2",
    "PUSHB","PUSHW","PUSHD","PUSHQ","PUSHF1","PUSHF2",
    "POPB","POPW","POPD","POPQ","POPF1","POPF2",
    "MOV","MOVF","MOVD",
    //program control flow
    "JMP","JE","JNE",
    "SLT",
    "INT","DI","EI",
    "HALT",
    "NOP",
    //bitwise
    "AND","OR","XOR","NOT",
    "BT","BS",
    //shift
    "SRA","SRL","SL",
    //integer arithmetic
    "ADD","SUB","MULT","DIV",
    //conversion
    "CAST_IF","CAST_ID","CAST_FI","CAST_FD","CAST_DI","CAST_DF",
    //floating point math
    "FADD","FSUB","FMULT","FDIV","FSLT",
    "DADD","DSUB","DMULT","DDIV","DSLT",
    //not an instruction
    "BAD"
};

} //namespace Logi
