//Logi includes
#include "Registers.h"
#include "Stream.h"

//// TEMP
#include <iostream>
#include <iomanip>
using namespace std;

namespace Logi
{

const std::string REG_CODE_OUT_OF_BOUNDS {"REGISTERS: register code out of bounds"};

const std::vector<std::string> Registers::_RegisterStrings
{
    "$IP","$SP","$FP","$BE","$HS","$HE","$SS","$TOP",
    "$R1","$R2","$R3","$R4","$R5","$R6","$R7","$R8","$R9","$R10",
    "$R11","$R12","$R13","$R14","$R15","$R16","$R17","$R18","$R19","$R20",
    "$R21","$R22","$R23","$R24"
};

const std::vector<std::string> Registers::_FloatRegisterStrings
{
    "$F1","$F2","$F3","$F4","$F5",
    "$F6","$F7","$F8","$F9","$F10"
};

const std::vector<std::string> Registers::_DoubleRegisterStrings
{
    "$D1","$D2","$D3","$D4","$D5",
    "$D6","$D7","$D8","$D9","$D10"
};

const RegisterCodes Registers::FIRST_REGISTER {RegisterCodes::$IP};
const RegisterCodes Registers::FIRST_INTEGER_REGISTER {RegisterCodes::$R1};
const FloatRegisterCodes Registers::FIRST_FLOAT_REGISTER {FloatRegisterCodes::$F1};
const DoubleRegisterCodes Registers::FIRST_DOUBLE_REGISTER {DoubleRegisterCodes::$D1};

U8& Registers::R(const RegisterCodes code)
{
    if(code < RegisterCodes::$IP || code > (NUM_REGISTERS + NUM_INTEGER_REGISTERS + RegisterCodes::$R24)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _R[code];
}

U8& Registers::R1_24(unsigned int code)
{
    if(code < 1 || code > 24) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _R[(code-1) + NUM_REGISTERS];
}

F4& Registers::RF(const FloatRegisterCodes code)
{
    if(code < FloatRegisterCodes::$F1 || code >= (NUM_FLOAT_REGISTERS + FloatRegisterCodes::$F1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RF[code-1];
}

F8& Registers::RD(const DoubleRegisterCodes code)
{
    if(code < DoubleRegisterCodes::$D1 || code >= (NUM_DOUBLE_REGISTERS + DoubleRegisterCodes::$D1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RD[code-1];
}

const U8 Registers::R(const RegisterCodes code) const
{
    if(code < RegisterCodes::$IP || code > (NUM_REGISTERS + NUM_INTEGER_REGISTERS + RegisterCodes::$R24)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _R[code];
}

const U8 Registers::R1_24(unsigned int code) const
{
    if(code < 1 || code > 24) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _R[(code-1) + NUM_REGISTERS];
}

const F4 Registers::RF(const FloatRegisterCodes code) const
{
    if(code < FloatRegisterCodes::$F1 || code >= (NUM_FLOAT_REGISTERS + FloatRegisterCodes::$F1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RF[code-1];
}

const F8 Registers::RD(const DoubleRegisterCodes code) const
{
    if(code < DoubleRegisterCodes::$D1 || code >= (NUM_DOUBLE_REGISTERS + DoubleRegisterCodes::$D1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RD[code-1];
}

const std::string& Registers::R_str(const RegisterCodes code) const
{
    if(code < RegisterCodes::$IP || code > (NUM_REGISTERS + NUM_INTEGER_REGISTERS + RegisterCodes::$R24)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RegisterStrings.at(code);
}

const std::string& Registers::R1_24_str(unsigned int code) const
{
    if(code < 1 || code > 24) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _RegisterStrings.at((code-1) + NUM_REGISTERS);
}

const std::string& Registers::RF_str(const FloatRegisterCodes code) const
{
    if(code < FloatRegisterCodes::$F1 || code >= (NUM_FLOAT_REGISTERS + FloatRegisterCodes::$F1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _FloatRegisterStrings.at(code-1);
}

const std::string& Registers::RD_str(const DoubleRegisterCodes code) const
{
    if(code < DoubleRegisterCodes::$D1 || code >= (NUM_DOUBLE_REGISTERS + DoubleRegisterCodes::$D1)) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS);
    return _DoubleRegisterStrings.at(code-1);
}

std::ostream& operator<<(std::ostream& out,const Registers& registers)
{
    out << std::showbase << std::hex;

    ////////////////////////
    /// TREMP! FOR DEBUGGING
    const int LEN = 50;
    const Stream* s = Stream::getInstance();
    out << setw(LEN) << setfill('-') << '\n';
    out << registers.R_str($IP) << "= "; s->U8(registers.R($IP)); out << std::endl; // $IP
    out << registers.R_str($SP) << "= "; s->U8(registers.R($SP)); out << std::endl; // $SP
    out << registers.R_str($BE) << "= "; s->U8(registers.R($BE)); out << std::endl; // $BE
    out << registers.R_str($HS) << "= "; s->U8(registers.R($HS)); out << std::endl; // $HS
    out << registers.R_str($HE) << "= "; s->U8(registers.R($HE)); out << std::endl; // $HE
    out << registers.R_str($SS) << "= "; s->U8(registers.R($SS)); out << std::endl; // $SS
    out << registers.R_str($TOP) << "= "; s->U8(registers.R($TOP)); out << std::endl; // $$TOP
    out << setw(LEN) << setfill('-') << '\n';
    out << registers.R_str($R1) << "= "; s->U8(registers.R($R1)); out << std::endl; // $R1
    out << registers.R_str($R2) << "= "; s->U8(registers.R($R2)); out << std::endl; // $R2
    out << registers.R_str($R3) << "= "; s->U8(registers.R($R3)); out << std::endl; // $R3
    out << registers.R_str($R4) << "= "; s->U8(registers.R($R4)); out << std::endl; // $R4
    out << registers.R_str($R5) << "= "; s->U8(registers.R($R5)); out << std::endl; // $R5
    out << setw(LEN) << setfill('-') << '\n';
    out << registers.RF_str($F1) << "= "; s->U8(registers.RF($F1)); out << std::endl; // $F1
    out << registers.RF_str($F2) << "= "; s->U8(registers.RF($F2)); out << std::endl; // $F2
    out << registers.RF_str($F3) << "= "; s->U8(registers.RF($F3)); out << std::endl; // $F3
    out << setw(LEN) << setfill('-') << '\n';
    out << registers.RD_str($D1) << "= "; s->U8(registers.RD($D1)); out << std::endl; // $F1
    out << registers.RD_str($D2) << "= "; s->U8(registers.RD($D2)); out << std::endl; // $F2
    out << registers.RD_str($D3) << "= "; s->U8(registers.RD($D3)); out << std::endl; // $F3
    /////////////////////


    /*int i{0};
    for(i=0; i<8; i++)
    {
        out << registers.R_str(i) << " = " << static_cast<int>(registers.R(i)) << std::endl;
    }

    for(; i<NUM_REGISTERS; i++)
    {
        out << registers.R_str(i) << " = " << static_cast<int>(registers.R(i)) << std::endl;
    }

    for(i=0; i<NUM_FLOAT_REGISTERS; i++)
    {
        out << registers.RF_str(i) << " = " << static_cast<int>(registers.RF(i)) << std::endl;
    }

    for(i=0; i<NUM_DOUBLE_REGISTERS; i++)
    {
        out << registers.RD_str(i) << " = " << static_cast<int>(registers.RD(i)) << std::endl;
    }*/

    out << std::dec;
    return out;
}

const RegisterCodes Registers::R_fromStr(const std::string& str)
{
    std::vector<std::string>::const_iterator i = _RegisterStrings.begin();
    int index = FIRST_REGISTER;
    while(i != _RegisterStrings.end())
    {
        if(*i == str) return (RegisterCodes)index;
        ++i;
        index++;
    }
    
    throw std::runtime_error("REGISTERS: bad register string.");
}

const FloatRegisterCodes Registers::RF_fromStr(const std::string& str)
{
    std::vector<std::string>::const_iterator i = _FloatRegisterStrings.begin();
    int index = FIRST_FLOAT_REGISTER;
    while(i != _FloatRegisterStrings.end())
    {
        if(*i == str) return (FloatRegisterCodes)index;
        ++i;
        index++;
    }
    
    throw std::runtime_error("REGISTERS: bad float register string.");
}

const DoubleRegisterCodes Registers::RD_fromStr(const std::string& str)
{
    std::vector<std::string>::const_iterator i = _DoubleRegisterStrings.begin();
    int index = FIRST_DOUBLE_REGISTER;
    while(i != _DoubleRegisterStrings.end())
    {
        if(*i == str) return (DoubleRegisterCodes)index;
        ++i;
        index++;
    }
    
    throw std::runtime_error("REGISTERS: bad double register string.");
}

} //namespace Logi
