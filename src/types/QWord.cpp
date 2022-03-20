//Logi includes
#include "QWord.h"

namespace Logi
{

/////////////////////////// signed qword ///////////////////////////

QWord::QWord()
{
    this->value.S8 = 0;
    this->tag = TypeTag::S8_TAG;
}

QWord::QWord(const S8 value)
{
    this->value.S8 = value;
    this->tag = TypeTag::S8_TAG;
}

std::ostream& operator<<(std::ostream& out,QWord& qword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(qword.value.S8);
    out << std::dec;
    return out;
}

/////////////////////////// unsigned qword ///////////////////////////

UQWord::UQWord()
{
    this->value.U8 = 0;
    this->tag = TypeTag::U8_TAG;
}

UQWord::UQWord(const U8 value)
{
    this->value.U8 = value;
    this->tag = TypeTag::U8_TAG;
}

std::ostream& operator<<(std::ostream& out,const UQWord& qword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(qword.value.U8);
    out << std::dec;
    return out;
}

} //namespace Logi
