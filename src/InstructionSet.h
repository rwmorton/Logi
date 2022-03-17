#ifndef __LOGI_INSTRUCTION_SET_H__
#define __LOGI_INSTRUCTION_SET_H__

//std includes
#include <vector>
#include <string>
#include <ostream>

namespace Logi
{

class InstructionSet
{
    public:
        InstructionSet();
        ~InstructionSet();
    private:
        static const std::vector<std::string> _InstructionSetStrings;
};

enum OpCodes
{
    //data transfer
    LBI = 0,    //load byte immediate
    LWI,        //load word immediate
    LDI,        //load double word immediate
    LQI,        //load quad word immediate
    LF1I,       //load single-precision float immediate
    LF2I,       //load double precision float immediate
    LAD,        //load address direct
    LAI,        //load address indirect
    LB,         //load byte
    LW,         //load word
    LD,         //load double word
    LQ,         //load quad word
    LF1,        //load single-precision float
    LF2,        //load double-precision float
    SB,         //store byte
    SW,         //store word
    SD,         //store double word
    SQ,         //store quad word
    SF1,        //store single-precision float
    SF2,        //store double-precision float
    PUSHB,      //push byte on stack
    PUSHW,      //push word on stack
    PUSHD,      //push double word on stack
    PUSHQ,      //push quad word on stack
    PUSHF1,     //push single-precision float on stack
    PUSHF2,     //push double-precision float on stack
    POPB,       //pop byte off stack
    POPW,       //pop word off stack
    POPD,       //pop double word off stack
    POPQ,       //pop quad word off stack
    POPF1,      //pop single-precision float off stack
    POPF2,      //pop double-precision float off stack
    MOV,        //move an integer value
    MOVF,       //move a single-precision float value
    MOVD,       //move a double-precision float value
    //program control flow
    JMP,        //unconditional jump
    JE,         //jump if equal
    JNE,        //jump if not equal
    SLT,        //set if less than
    INT,        //perform interrupt
    DI,         //disable interrupts
    EI,         //enable interrupts
    HALT,       //stop the virtual machine
    NOP,        //no-op
    //bitwise
    AND,        //bitwise AND
    OR,         //bitwise OR
    XOR,        //bitwise XOR
    NOT,        //bitwise NOT
    BT,         //bitwise test
    BS,         //bitwise set
    //shift
    SRA,        //shift airthmetic right
    SRL,        //shift logical right
    SL,         //shift left
    //integer arithmetic
    ADD,        //integer addition
    SUB,        //integer subtraction
    MULT,       //integer multiplication
    DIV,        //integer division
    //conversion
    CAST_IF,    //convert a single-precision float to an integer
    CAST_ID,    //convert a double-precision float to an integer
    CAST_FI,    //convert an integer to a single-precision float
    CAST_FD,    //double-precision float to single-precision
    CAST_DI,    //integer to double-precision float
    CAST_DF,    //single-precision float to double-precision
    //floating point math
    FADD,       //single-precision float addition
    FSUB,       //single-precision float subtraction
    FMULT,      //single-precision float multiplication
    FDIV,       //single-precision float division
    FSLT,       //single-precision float set if less than
    DADD,       //double-precision float addition
    DSUB,       //double-precision float subtraction
    DMULT,      //double-precision float multiplication
    DDIV,       //double-precision float division
    DSLT,       //double-precision float set if less than
    BAD = -1,   //not an instruction
};

} //namespace Logi

#endif //__LOGI_INSTRUCTION_SET_H__
