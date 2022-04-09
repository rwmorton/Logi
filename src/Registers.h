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

class Registers
{
    public:
        //Registers
        Registers();
        //set registers
        U8& R(const RegisterCodes code);
        U8& R1_24(unsigned int code); //set registers from R1 - R24
        F4& RF(const FloatRegisterCodes code);
        F8& RD(const DoubleRegisterCodes code);
        //get registers
        const U8 R(const RegisterCodes code) const;
        const U8 R1_24(unsigned int code) const; //get registers from R1 - R24
        const F4 RF(const FloatRegisterCodes code) const;
        const F8 RD(const DoubleRegisterCodes code) const;
        //get register as string
        const std::string& R_str(const RegisterCodes code) const;
        const std::string& R1_24_str(unsigned int code) const;
        const std::string& RF_str(const FloatRegisterCodes code) const;
        const std::string& RD_str(const DoubleRegisterCodes code) const;
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const Registers& registers);//register sizes
        //get register from string
        static const RegisterCodes R_fromStr(const std::string& str);
        static const FloatRegisterCodes RF_fromStr(const std::string& str);
        static const DoubleRegisterCodes RD_fromStr(const std::string& str);
        //
        //static const U1 NUM_REGISTERS {32};
        static const U1 NUM_REGISTERS {8};
        static const U1 NUM_INTEGER_REGISTERS {24};
        static const U1 NUM_FLOAT_REGISTERS {10};
        static const U1 NUM_DOUBLE_REGISTERS {10};
    private:
        U8 _R[NUM_REGISTERS];               //integer registers - 64 bit in size
        F4 _RF[NUM_FLOAT_REGISTERS];        //single-precision float registers - 32 bit in size
        F8 _RD[NUM_DOUBLE_REGISTERS];       //double-precision float registers - 64 bit in size
        static const std::vector<std::string> _RegisterStrings;
        static const std::vector<std::string> _FloatRegisterStrings;
        static const std::vector<std::string> _DoubleRegisterStrings;
        static const RegisterCodes FIRST_REGISTER;
        static const RegisterCodes FIRST_INTEGER_REGISTER;
        static const FloatRegisterCodes FIRST_FLOAT_REGISTER;
        static const DoubleRegisterCodes FIRST_DOUBLE_REGISTER;
};

} //namespace Logi

#endif //__LOGI_REGISTERS_H__
