//Logi includes
#include "Byte.h"

namespace Logi
{

/////////////////////////// signed byte ///////////////////////////

Byte::Byte()
{
    this->value.S1 = 0;
    this->tag = TypeTag::S1_TAG;
}

Byte::Byte(const S1 value)
{
    this->value.S1 = value;
    this->tag = TypeTag::S1_TAG;
}

std::ostream& operator<<(std::ostream& out,Byte& byte)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(byte.value.S1);
    out << std::dec;
    return out;
}

/////////////////////////// unsigned byte ///////////////////////////

UByte::UByte()
{
    this->value.U1 = 0;
    this->tag = TypeTag::U1_TAG;
}

UByte::UByte(const U1 value)
{
    this->value.U1 = value;
    this->tag = TypeTag::U1_TAG;
}

std::ostream& operator<<(std::ostream& out,const UByte& byte)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(byte.value.U1);
    out << std::dec;
    return out;
}

} //namespace Logi
