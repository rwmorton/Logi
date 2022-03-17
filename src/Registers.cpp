//Logi includes
#include "Registers.h"

namespace Logi
{

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

const std::string& Registers::R_str(unsigned int i) const
{
    if(i >= 24) throw std::exception();
    return _RegisterStrings.at(i);
}

const std::string& Registers::RF_str(unsigned int i) const
{
    if(i >= 10) throw std::exception();
    return _FloatRegisterStrings.at(i);
}

const std::string& Registers::RD_str(unsigned int i) const
{
    if(i >= 10) throw std::exception();
    return _DoubleRegisterStrings.at(i);
}

} //namespace Logi
