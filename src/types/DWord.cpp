//Logi includes
#include "DWord.h"

namespace Logi
{

/////////////////////////// signed dword ///////////////////////////

DWord::DWord()
{
    this->value.S4 = 0;
    this->tag = TypeUnionTag::S4_TAG;
}

DWord::DWord(const signed int value)
{
    this->value.S4 = value;
    this->tag = TypeUnionTag::S4_TAG;
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
    this->tag = TypeUnionTag::U4_TAG;
}

UDWord::UDWord(const unsigned int value)
{
    this->value.U4 = value;
    this->tag = TypeUnionTag::U4_TAG;
}

std::ostream& operator<<(std::ostream& out,const UDWord& dword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(dword.value.U4);
    out << std::dec;
    return out;
}

} //namespace Logi
