//Logi includes
#include "InstructionSet.h"

namespace Logi
{

InstructionSet::InstructionSet() {}
InstructionSet::~InstructionSet() {}

const std::string& InstructionSet::I_str(unsigned int i) const
{
    if(i >= 73) throw std::exception(); //out of bounds
    return _InstructionSetStrings.at(i);
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
    "DADD","DSUB","DMULT","DDIV","DSLT"
    //not an instruction
    "BAD"
};

} //namespace Logi
