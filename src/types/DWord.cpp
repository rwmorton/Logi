//Logi includes
#include "DWord.h"

namespace Logi
{

/////////////////////////// signed dword ///////////////////////////

DWord::DWord()
{
    this->value.S4 = 0;
    this->tag = TypeTag::S4_TAG;
}

DWord::DWord(const S4 value)
{
    this->value.S4 = value;
    this->tag = TypeTag::S4_TAG;
}

std::ostream& operator<<(std::ostream& out,DWord& dword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(dword.value.S4);
    out << std::dec;
    return out;
}

/////////////////////////// unsigned dword ///////////////////////////

UDWord::UDWord()
{
    this->value.U4 = 0;
    this->tag = TypeTag::U4_TAG;
}

UDWord::UDWord(const U4 value)
{
    this->value.U4 = value;
    this->tag = TypeTag::U4_TAG;
}

std::ostream& operator<<(std::ostream& out,const UDWord& dword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(dword.value.U4);
    out << std::dec;
    return out;
}

} //namespace Logi
