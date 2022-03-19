//Logi includes
#include "QWord.h"

namespace Logi
{

/////////////////////////// signed qword ///////////////////////////

QWord::QWord(signed long long value) : Type(std::any_cast<signed long long>(value)) {}

std::ostream& operator<<(std::ostream& out,QWord& qword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<signed long long>(qword.value));
    out << std::dec;
    return out;
}

/////////////////////////// unsigned qword ///////////////////////////

UQWord::UQWord(unsigned long long value) : Type(std::any_cast<unsigned long long>(value)) {}

std::ostream& operator<<(std::ostream& out,UQWord& qword)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<unsigned long long>(qword.value));
    out << std::dec;
    return out;
}

} //namespace Logi
