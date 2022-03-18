//Logi includes
#include "Registers.h"
#include "Stream.h"

namespace Logi
{

const std::string REG_CODE_OUT_OF_BOUNDS {"register code out of bounds"};

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

//dump register information to stream
void Registers::dump() const
{
    const Stream* stream = Stream::getInstance();

    const std::string& hdr {"-----------------"};
    const std::string& dmp {"REGISTER DUMP"};
    const std::string& bsc {"BASIC"};
    const std::string& gnl {"GENERAL"};
    const std::string& flt {"FLOAT"};
    const std::string& dbl {"DOUBLE"};

    stream->string(hdr).endl().string(dmp).endl().string(hdr).endl();

    stream->string(bsc).endl().string(hdr).endl();
    int i{0};
    for(i=0; i<8; i++)
    {
        stream->U_REG(R_str(i),R(i)).endl();
    }

    stream->string(hdr).endl().string(gnl).endl().string(hdr).endl();
    for(; i<NUM_REGISTERS; i++)
    {
        stream->S_REG(R_str(i),R(i)).endl();
    }

    stream->string(hdr).endl().string(flt).endl().string(hdr).endl();
    for(i=0; i<NUM_FLOAT_REGISTERS; i++)
    {
        stream->F_REG(RF_str(i),RF(i)).endl();
    }

    stream->string(hdr).endl().string(dbl).endl().string(hdr).endl();
    for(i=0; i<NUM_DOUBLE_REGISTERS; i++)
    {
        stream->D_REG(RD_str(i),RD(i)).endl();
    }

    stream->string(hdr).endl();
}

} //namespace Logi
