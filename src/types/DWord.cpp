//Logi includes
#include "DWord.h"

namespace Logi
{

/////////////////////////// signed dword ///////////////////////////

DWord::DWord(signed int value) : Type(std::any_cast<signed int>(value)) {}

std::ostream& operator<<(std::ostream& out,DWord& dword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<signed int>(dword.value));
    out << std::dec;
    return out;
}

/////////////////////////// unsigned dword ///////////////////////////

UDWord::UDWord(unsigned int value) : Type(std::any_cast<unsigned int>(value)) {}

std::ostream& operator<<(std::ostream& out,UDWord& dword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<unsigned int>(dword.value));
    out << std::dec;
    return out;
}

} //namespace Logi
