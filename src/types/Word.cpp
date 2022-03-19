//Logi includes
#include "Word.h"

namespace Logi
{

/////////////////////////// signed word ///////////////////////////

Word::Word(signed short value) : Type(std::any_cast<signed short>(value)) {}

std::ostream& operator<<(std::ostream& out,Word& word)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<signed short>(word.value));
    out << std::dec;
    return out;
}

/////////////////////////// unsigned word ///////////////////////////

UWord::UWord(unsigned short value) : Type(std::any_cast<unsigned short>(value)) {}

std::ostream& operator<<(std::ostream& out,UWord& word)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<unsigned short>(word.value));
    out << std::dec;
    return out;
}

} //namespace Logi
