//Logi includes
#include "Byte.h"

namespace Logi
{

/////////////////////////// signed byte ///////////////////////////

Byte::Byte(signed char value) : Type(std::any_cast<signed char>(value)) {}

std::ostream& operator<<(std::ostream& out,Byte& byte)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<signed char>(byte.value));
    out << std::dec;
    return out;
}

 /////////////////////////// unsigned byte ///////////////////////////

UByte::UByte(unsigned char value) : Type(std::any_cast<unsigned char>(value)) {}

std::ostream& operator<<(std::ostream& out,UByte& byte)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<unsigned char>(byte.value));
    out << std::dec;
    return out;
}

} //namespace Logi
