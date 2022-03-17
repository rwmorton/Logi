#ifndef __LOGI_REGISTERS_H__
#define __LOGI_REGISTERS_H__

//logi includes
#include "Types.h"
#include "InstructionSet.h"

//std includes
#include <vector>
#include <string>

namespace Logi
{

class Registers
{
    public:
    private:
        U8 R[32];        //integer registers - 64 bit in size
        F4 RF[10];       //single-precision float registers - 32 bit in size
        F8 RD[10];       //double-precision float registers - 64 bit in size
        static const std::vector<std::string> _RegisterStrings;
        static const std::vector<std::string> _FloatRegisterStrings;
        static const std::vector<std::string> _DoubleRegisterStrings;
};

enum RegisterCodes
{
    $IP = 0,     //address of next instruction to execute
    $SP,         //address of most recent value pushed on stack
    $FP,         //stack frame pointer
    $BE,         //address of last byte of bytecode section
    $HS,         //address of first (lowest) byte of heap
    $HE,         //address of last (highest) byte used by heap
    $SS,         //address of bottom of stack (lowest)
    $TOP,        //address of top-of-stack (highest)
    //general purpose registers
    $R1,
    $R2,
    $R3,
    $R4,
    $R5,
    $R6,
    $R7,
    $R8,
    $R9,
    $R10,
    $R11,
    $R12,
    $R13,
    $R14,
    $R15,
    $R16,
    $R17,
    $R18,
    $R19,
    $R20,
    $R21,
    $R22,
    $R23,
    $R24,
};

enum FloatRegisterCodes
{
    $F1 = 0,
    $F2,
    $F3,
    $F4,
    $F5,
    $F6,
    $F7,
    $F8,
    $F9,
    $F10
};

enum DoubleRegisterCodes
{
    $D1 = 0,
    $D2,
    $D3,
    $D4,
    $D5,
    $D6,
    $D7,
    $D8,
    $D9,
    $D10
};

} //namespace Logi

#endif //__LOGI_REGISTERS_H__
