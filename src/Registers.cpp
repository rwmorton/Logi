//Logi includes
#include "Registers.h"
#include "Stream.h"

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

U8& Registers::R(unsigned int code)
{
    if(code >= NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _R[code];
}

U8& Registers::R1_24(unsigned int code)
{
    if(code < 1 || code > NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _R[(code-1) + 8];
}

F4& Registers::RF(unsigned int code)
{
    if(code >= NUM_FLOAT_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RF[code];
}

F8& Registers::RD(unsigned int code)
{
    if(code >= NUM_DOUBLE_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RD[code];
}

const U8 Registers::R(unsigned int code) const
{
    if(code >= NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _R[code];
}

const U8 Registers::R1_24(unsigned int code) const
{
    if(code < 1 || code > NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _R[(code-1) + 8];
}

const F4 Registers::RF(unsigned int code) const
{
    if(code >= NUM_FLOAT_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RF[code];
}

const F8 Registers::RD(unsigned int code) const
{
    if(code >= NUM_DOUBLE_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RD[code];
}

const std::string& Registers::R_str(unsigned int code) const
{
    if(code >= NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RegisterStrings.at(code);
}

const std::string& Registers::R1_24_str(unsigned int code) const
{
    if(code < 1 || code > NUM_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _RegisterStrings.at((code-1) + 8);
}

const std::string& Registers::RF_str(unsigned int code) const
{
    if(code >= NUM_FLOAT_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _FloatRegisterStrings.at(code);
}

const std::string& Registers::RD_str(unsigned int code) const
{
    if(code >= NUM_DOUBLE_REGISTERS) throw std::out_of_range(REG_CODE_OUT_OF_BOUNDS); //out of bounds
    return _DoubleRegisterStrings.at(code);
}

std::ostream& operator<<(std::ostream& out,const Registers& registers)
{
    out << std::showbase << std::hex;

    ////////////////////////
    /// TREMP! FOR DEBUGGING
    const Stream* s = Stream::getInstance();
    out << registers.R_str(0) << "= "; s->U8(registers.R(0)); out << std::endl; // $IP
    out << registers.R_str(3) << "= "; s->U8(registers.R(3)); out << std::endl; // $BE
    out << registers.R_str(7) << "= "; s->U8(registers.R(7)); out << std::endl; // $$TOP
    out << registers.R_str(8) << "= "; s->U8(registers.R(8)); out << std::endl; // $R1
    out << registers.R_str(9) << "= "; s->U8(registers.R(9)); out << std::endl; // $R2
    out << registers.R_str(10) << "= "; s->U8(registers.R(10)); out << std::endl; // $R3
    out << registers.R_str(11) << "= "; s->U8(registers.R(11)); out << std::endl; // $R4
    out << registers.R_str(12) << "= "; s->U8(registers.R(12)); out << std::endl; // $R5
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

} //namespace Logi
