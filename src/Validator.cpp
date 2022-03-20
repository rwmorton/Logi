//Logi includes
#include "Validator.h"

namespace Logi
{

Validator* Validator::instance {nullptr};

const Validator* Validator::getInstance()
{
    if(Validator::instance == nullptr)
    {
        Validator::instance = new Validator();
    }
    return Validator::instance;
}

void Validator::integerRegister(U1 arg,U8 currentByte) const
{
    if(arg > RegisterCodes::$R24) throw std::runtime_error("invalid integer register code.");
}

void Validator::floatRegister(U1 arg,U8 currentByte) const
{
    if(arg > FloatRegisterCodes::$F10) throw std::runtime_error("invalid float register code.");
}

void Validator::doubleRegister(U1 arg,U8 currentByte) const
{
    if(arg > DoubleRegisterCodes::$D10) throw std::runtime_error("invalid double register code.");
}

//
// make sure that the bytecode address literals do not
// reference memory beyond the end of the address space.
//
void Validator::address_(U1* array,U8 currentByte,const Registers& registers) const
{
    U8* address = (U8*)&array[currentByte];
    if(*address > registers.R(RegisterCodes::$TOP)) throw std::runtime_error("address is out of bounds.");
}

//
// safeguard against incomplete instructions.
//
void Validator::currentByte(U8 currentByte,U8 end) const
{
    if(currentByte >= end) throw std::runtime_error("incomplete instruction at address.");
}

//
// the last byte of an instruction is allowed to be at the end of the bytecode.
// this function checks for that.
//
void Validator::endCurrentByte(U8 currentByte,U8 end) const
{
    if(currentByte > end) throw std::runtime_error("incomplete instruction: passed end of bytecode.");
}

Validator::Validator() {}

} //namespace Logi
